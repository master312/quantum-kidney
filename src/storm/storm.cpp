#include "storm.h"
#include "gui/cGuiManager.h"
#include "cStormConsole.h"
#include "cStormConsoleCommands.h"

storm::storm(){
	api = 0;
	isRunning = false;
	mGraphics = NULL;
	wWidth = 800;
	wHeight = 600;
	wBpp = 32;
	wType = STORM_WINDOW_WINDOWED;
	wTitle = "Storm engine default window";
	lastGraphTick = 0;
	lastLogicTick = 0;
	delta = 0;
	targetGraphics = 60;
	targetLogic = 30;
	mTexture = NULL;
	mAnimation = NULL;
	mEvents = NULL;
	mFont = NULL;
	defFontGlyphs = "`1234567890-=qwertyuiop[]asdfghjkl;'\\<zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}ASDFGHJKL:\"|>ZXCVBNM<>?";
	mSound = NULL;
	mState = NULL;
	tCallbackManager = NULL;
        mConsole = NULL;
        hConsoleCommands = NULL;
	isDebug = true;
        frames = framesCount = fps = 0;
        toCalculateFps.SetInterval(STORM_AVERAGE_FPS_TIME);
}
storm::~storm(){
	Quit();
}
bool storm::Initialize(int _api){
	api = _api;
	switch(api){
		#if BUILD_OPENGL > 0
		case STORM_API_OPENGL:
			mGraphics = new cGraphicsOpenGL();
			mTexture = new cTextureManagerOpenGL();
			mFont = new cFontManagerOpenGL(mTexture);
			mSound = new cSoundManagerSDL2();
			break;
		#endif
		case STORM_API_SDL:
			break;
		case STORM_API_SDL2:
			mGraphics = new cGraphicsSDL2();
			mTexture = new cTextureManagerSDL2();
			mFont = new cFontManagerSDL2(mTexture);
			mSound = new cSoundManagerSDL2();
			break;
		default:
			StormPrintLog(STORM_LOG_ERROR, "Storm", "Invalid api");
			return false;
	}
	if(!mGraphics->Initialize(wWidth, wHeight, wBpp, wTitle)){
		return false;
	}
	mState = new cStateManager();
	mGraphics->MakeWindow();	//Creates new window
	mGraphics->SetWindowType(wType);
	mTexture->SetGraphics(mGraphics);
	if(!mTexture->Initialize()){
		StormPrintLog(STORM_LOG_ERROR, "Storm", "Default texture is missing");
		return false;
	}
	mAnimation = new cAnimationManager(mTexture);	//Creates animation manager
	mEvents = new cEventManager(api, mGraphics);	//Initialize events manager
	mSound->Initialize();	//Initialize sound maanger
	mFont->Initialize();	//Initialize font manager
	mFont->SetChars(defFontGlyphs);
	if(!mFont->LoadFont("default.ttf", "default", 18)){
		StormPrintLog(STORM_LOG_ERROR, "Storm", "Could not load default font!");
		return false;
	}
        mConsole = new cStormConsole();
        mConsole->Init();
        hConsoleCommands = new cStormConsoleCommands(mConsole);
	guiManager = new cGuiManager();
	if(!guiManager->Initialize()){
		StormPrintLog(STORM_LOG_ERROR, "Storm", "Could not initialize GUI manager!");
		return false;
	}
	mEvents->AddHandler(
		new cStormCallbacker(guiManager, &cGuiManager::HandleEvents), "cGuiManager");
	tCallbackManager = new cTimedCallbackManager();
	ClearScreen();
	isRunning = true;
	lastLogicTick = SDL_GetTicks();
        toCalculateFps.Reset();
	StormPrintLog(STORM_LOG_INFO, "Storm", "Engine initialized");
	return true;
}
void storm::Quit(){
	if(mState != NULL){
		delete mState;
		mState = NULL;
	}
	if(mEvents != NULL){
		delete mEvents;
		mEvents = NULL;
	}
	if(mSound != NULL){
		delete mSound;
		mSound = NULL;
	}
	if(mFont != NULL){
		delete mFont;
		mFont = NULL;
	}
	if(mAnimation != NULL){
		delete mAnimation;
		mAnimation = NULL;
	}
	if(mTexture != NULL){
		delete mTexture;
		mTexture = NULL;
	}
	if(mGraphics != NULL){
		delete mGraphics;
		mGraphics = NULL;
	}
	if(tCallbackManager != NULL){
		delete tCallbackManager;
		tCallbackManager = NULL;
	}
        if(mConsole != NULL){
            delete mConsole;
            mConsole = NULL;
        }
        if(hConsoleCommands != NULL){
            delete hConsoleCommands;
            hConsoleCommands = NULL;
        }
	StormPrintLog(STORM_LOG_INFO, "Storm", "Program ended");
}
bool b = false;
void storm::Tick(){
	mEvents->Tick();

	delta = SDL_GetTicks() - lastLogicTick;
	if(delta >= 1000 / targetLogic){
		mState->LogicTick();
		lastLogicTick = SDL_GetTicks();
	}

	mAnimation->UpdateAll();
	if(IsGraphicsTick()){
		mState->GraphicsTick();
		guiManager->GraphicsTick();
                mConsole->Draw();
                
                frames += 1000 / (SDL_GetTicks() - lastGraphTick);
                framesCount++;
		if(isDebug && mFont != NULL){
                    char mousePos[40];
                    cInput *tmpI = mEvents->GetInputManager();
                    
                    if(tmpI->textScan) {
                        sprintf(mousePos, "FPS:%d Mouse X:%d Y:%d Text input mode", 
                                fps, tmpI->mouseX, tmpI->mouseY);                        
                    } else {
                        sprintf(mousePos, "FPS:%d Mouse X:%d Y:%d", 
                                fps, tmpI->mouseX, tmpI->mouseY);
                    }
                    
                    mFont->DrawText("default", mousePos, 2, mGraphics->height - 28);
		}
                
		FlipScreen();
	}

	guiManager->LogicTick();	//TODO: Maybe move this somewhere else. INFO:Interval is set in cGuiManager class
	tCallbackManager->Tick();	//Call timed callback functions

	if(mEvents->ToQuit()){
		StormPrintLog(STORM_LOG_INFO, "Storm", 
				"Quit signal received from event manager");
		isRunning = false;
	}
	if(mState->GetCurState() == NULL){
		StormPrintLog(STORM_LOG_INFO, "Storm", 
			"State manager returned NULL for current state. Quiting program...");
		isRunning = false;
	}
        if(toCalculateFps.IsTimeUp()){
            fps = frames / framesCount;
            frames = framesCount = 0;
            toCalculateFps.Reset();
        }
}
void storm::FlipScreen(){
	mGraphics->SwapBuffers();
	lastGraphTick = SDL_GetTicks();
}
void storm::ClearScreen(){
	mGraphics->ClearScreen();
}
bool storm::IsGraphicsTick(){
	return SDL_GetTicks() - lastGraphTick > (uint)1000 / targetGraphics;
}
void storm::ResizeWindow(int width, int height){
	wWidth = width;
	wHeight = height;
	mGraphics->ResizeWindow(width, height);
}