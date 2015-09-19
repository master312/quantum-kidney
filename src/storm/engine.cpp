#include "engine.h"
#include "gui/cGuiManager.h"
storm *sEngine = NULL;	//Pointer to storm engine class

bool S_InitEngine(int api){
	if(sEngine == NULL){
		sEngine = new storm();
		return sEngine->Initialize(api);
	}
	return false;
}
void S_Quit(){
	delete sEngine;
}
void S_Tick(){
	sEngine->Tick();
}
void S_FlipScreen(){
	sEngine->FlipScreen();
}
void S_ClearScreen(){
	sEngine->ClearScreen();
}
bool S_IsRunning(){
	return sEngine->IsRunning();
}
void S_Stop(){
	sEngine->Stop();
 }
bool S_IsGraphicsTick(){
	return sEngine->IsGraphicsTick();
}
int S_GetDelta(){
	return sEngine->GetDelta();
}
void S_SetDebugMode(bool b){
	sEngine->SetDebug(b);
}

void S_SetWindowSize(int width, int height){
	sEngine->SetWindowSize(width, height);
}
void S_SetWindowBpp(int bpp){
	sEngine->SetWindowBpp(bpp);
}
void S_SetWindowTitle(std::string title){
	sEngine->SetWindowTitle(title);
}
void S_SetWindowType(int type){
	sEngine->SetWindowType(type);
}
sRect S_GetWindowSize(){
	cGraphics *gr = sEngine->GetGraphicsManager();
	return sRect(0, 0, gr->GetWidth(), gr->GetHeight());
}
std::string S_GetWindowTitle(){
	return sEngine->GetGraphicsManager()->GetTitle();
}
bool S_IsWindowFullscreen(){
	return sEngine->GetGraphicsManager()->IsFullscreen();
}
void S_ResizeWindow(int width, int height){
	sEngine->ResizeWindow(width, height);
}
void S_SetMaxFps(int _fps){
	sEngine->SetMaxFps(_fps);
}
void S_SetMaxLogicTicks(int _mlt){
	sEngine->SetMaxLogicTicks(_mlt);
}


void S_DrawRect(int x, int y, int width, int height, float red, float green, float blue, float alpha){
	sEngine->GetGraphicsManager()->DrawRectangle(x, y, width, height, red, green, blue, alpha);
}
void S_DrawRect(sRect *rect, float red, float green, float blue, float alpha){
	sEngine->GetGraphicsManager()->DrawRectangle(rect->x, rect->y, rect->w, rect->h, red, green, blue, alpha);
}
void S_DrawFillRect(int x, int y, int width, int height, float red, float green, float blue, float alpha){
	sEngine->GetGraphicsManager()->DrawFilledRectangle(x, y, width, height, red, green, blue, alpha);
}
void S_DrawFillRect(sRect *rect, float red, float green, float blue, float alpha){
	sEngine->GetGraphicsManager()->DrawFilledRectangle(rect->x, rect->y, rect->w, rect->h, red, green, blue, alpha);
}
void DrawLine(int x, int y, int x2, int y2, int red, int green, int blue, int alpha){
	sEngine->GetGraphicsManager()->DrawLine(x, y, x2, y2, red, green, blue, alpha);
}
cGraphics *S_GetGraphicsManager(){
	return sEngine->GetGraphicsManager();
}

void S_ConsoleAddHandler(std::string name, cStormCallbacker cb) {
	sEngine->GetConsole()->AddCommand(name, cb);
}
void S_ConsolePrintLine(std::string text, ...) {
        int count = 0;
        for(uint i = 0; i < text.size(); i++){
            if(text[i] == '%'){
                count ++;
            }
        }
        if(count > 0) {
                va_list ap;
                va_start(ap, count);
                sEngine->GetConsole()->PushLogLine(StormParseArgs(text, count, ap));
                va_end(ap);
        }else{
                sEngine->GetConsole()->PushLogLine(text);
        }
}
cStormConsole *S_GetConsole() {
        return sEngine->GetConsole();
}

uint S_LoadTexture(std::string filename){
	return sEngine->GetTextureManager()->LoadTexture(filename);
}
uint S_CreateSection(uint textureId, int x, int y, int w, int h){
	return sEngine->GetTextureManager()->CreateSection(textureId, x, y, w, h);
}
uint S_CreateSection(uint textureId, sRect& rect){
	return sEngine->GetTextureManager()->CreateSection(textureId, rect.x, rect.y, rect.w, rect.h);
}
void S_DrawTexture(uint textureId, int x, int y, float scale, float rot){
	sEngine->GetTextureManager()->DrawTexture(textureId, x, y, scale, rot);
}
void S_DrawTextureScaled(uint textureId, sRect *rect, float rot){
	sEngine->GetTextureManager()->DrawTextureScaled(textureId, rect, rot);
}
void S_DrawTextureCropped(uint textureId, sRect *rect, int x, int y, float rot){
	sEngine->GetTextureManager()->DrawTextureCropped(textureId, rect, x, y, rot);
}
void S_DrawSection(uint sectionId, int x, int y, float scale, float rot){
	sEngine->GetTextureManager()->DrawSection(sectionId, x, y, scale, rot);
}
void S_DrawSectionScaled(uint sectionId, sRect *rect, float rot){
	sEngine->GetTextureManager()->DrawSectionScaled(sectionId, rect, rot);
}
void S_DrawSectionCropped(uint sectionId, sRect *crop, int x, int y, float rot){
	sEngine->GetTextureManager()->DrawSectionCropped(sectionId, crop, x, y, rot);
}
void S_ReloadTexture(uint textureId){
	sEngine->GetTextureManager()->ReloadTexture(textureId);
}
void S_ReloadTextures(){
	sEngine->GetTextureManager()->ReloadTextures();
}
void S_UnloadTexture(uint textureId){
	sEngine->GetTextureManager()->UnloadTexture(textureId);
}
void S_RemoveSection(uint sectionId){
	sEngine->GetTextureManager()->RemoveSection(sectionId);
}
sTexture *S_GetTexture(uint textureId){
	return sEngine->GetTextureManager()->GetTexture(textureId);
}
sTextureSection *S_GetSection(uint sectionId){
	return sEngine->GetTextureManager()->GetSection(sectionId);
}
cTextureManager *S_GetTextureManager(){
	return sEngine->GetTextureManager();
}

uint S_CreateAnimation(std::vector<uint> &frames, int fps, bool useTextures){
	return sEngine->GetAnimationManager()->CreateAnimation(frames, fps, useTextures);
}
uint S_LoadAnimation(std::string filename){
	return sEngine->GetAnimationManager()->LoadAnimation(filename);
}
void S_SaveAnimation(uint animationId, std::string filename){
	sEngine->GetAnimationManager()->SaveAnimation(filename, animationId);
}
void S_RemoveAnimation(uint animationId){
	sEngine->GetAnimationManager()->Remove(animationId);
}
void S_PauseAnimation(uint animationId){
	sEngine->GetAnimationManager()->Pause(animationId);
}
void S_PauseAnimations(){
	sEngine->GetAnimationManager()->PauseAll();
}
void S_ResumeAnimation(uint animationId){
	sEngine->GetAnimationManager()->Resume(animationId);
}
void S_ResumeAnimations(){
	sEngine->GetAnimationManager()->ResumeAll();
}
uint S_CloneAnimation(uint animationId){
	return sEngine->GetAnimationManager()->CloneAnimation(animationId);
}
void S_DrawAnimation(uint animationId, int x, int y, float scale, float rotation){
	sEngine->GetAnimationManager()->DrawAnimation(animationId, x, y, scale, rotation);
}
cAnimation *S_GetAnimation(uint animationId){
	return sEngine->GetAnimationManager()->GetAnimation(animationId);
}
cAnimationManager *S_GetAnimationManager(){
	return sEngine->GetAnimationManager();
}

void S_SetGlyphs(std::string glyphs){
	return sEngine->GetFontManager()->SetChars(glyphs);
}
bool S_LoadFont(std::string filename, std::string fontName, int size){
	return sEngine->GetFontManager()->LoadFont(filename, fontName, size);
}
void S_UnloadFont(std::string fontName){
	sEngine->GetFontManager()->UnloadFont(fontName);
}
void S_UnloadFonts(){
	sEngine->GetFontManager()->UnloadAll();
}
void S_RenderText(std::string text, int x, int y, std::string font, 
		float r, float g, float b, float scale, float rotation){
	sEngine->GetFontManager()->DrawText(font, text, x, y, r, g, b, scale, rotation);
}
sRect S_GetTextSize(std::string text, std::string font){
	return sEngine->GetFontManager()->GetTextSize(text, font);
}
sFont *S_GetFont(std::string font){
	return sEngine->GetFontManager()->GetFont(font);
}
cFontManager *S_GetFontManager(){
	return sEngine->GetFontManager();
}


void S_AddEventHandler(cStormCallbacker *cb, std::string name){
	sEngine->GetEventManager()->AddHandler(cb, name);
}
void S_RemoveEventHandler(std::string name){
	sEngine->GetEventManager()->RemoveHandler(name);
}
void S_EatEvent(std::string name){
	sEngine->GetEventManager()->Eat(name);
}
bool S_IsKeyDown(eKey key){
	return sEngine->GetInputManager()->IsKeyDown(key);
}
bool S_IsKeyUp(eKey key){
	return sEngine->GetInputManager()->IsKeyUp(key);
}
int S_GetMouseX(){
	return sEngine->GetInputManager()->GetMouseX();
}
int S_GetMouseY(){
	return sEngine->GetInputManager()->GetMouseY();
}
int S_GetMouseScroll(){
	return sEngine->GetInputManager()->GetMouseScroll();
}
bool S_IsMouseLeft(){
	return sEngine->GetInputManager()->IsMouseLeft();
}
bool S_IsMouseRight(){
	return sEngine->GetInputManager()->IsMouseRight();
}
bool S_IsMouseMiddle(){
	return sEngine->GetInputManager()->IsMouseMiddle();
}
void S_StartTextInput(){
	sEngine->GetInputManager()->StartTextInput();
}
void S_StopTextInput(){
	sEngine->GetInputManager()->StopTextInput();
}
bool S_IsTextInput(){
	return sEngine->GetInputManager()->textScan;
}
std::string S_GetTextInput(){
	return sEngine->GetInputManager()->GetText();
}
cInput *S_GetInputManager(){
	return sEngine->GetInputManager();
}

uint S_LoadSound(std::string filename){
	return sEngine->GetSoundManager()->LoadSound(filename);
}
void S_DeleteSound(uint soundId){
	sEngine->GetSoundManager()->DeleteSound(soundId);
}
void S_DeleteAllSounds(){
	sEngine->GetSoundManager()->DeleteAllSounds();
}
void S_SetSoundVolume(int volume){
	sEngine->GetSoundManager()->SetSoundVolume(volume);
}
void S_PlaySound(uint soundId, int _repeat){
	sEngine->GetSoundManager()->PlaySound(soundId, _repeat);
}
void S_StopSound(uint soundId){
	sEngine->GetSoundManager()->StopSound(soundId);
}
cSound *S_GetSound(uint soundId){
	return sEngine->GetSoundManager()->GetSound(soundId);
}
uint S_LoadMusic(std::string filename){
	return sEngine->GetSoundManager()->LoadMusic(filename);
}
void S_DeleteMusic(uint musicId){
	sEngine->GetSoundManager()->DeleteMusic(musicId);
}
void S_DeleteAllMusic(){
	sEngine->GetSoundManager()->DeleteAllMusic();
}
void S_StopMusic(){
	sEngine->GetSoundManager()->StopMusic();
}
void S_PauseMusic(){
	sEngine->GetSoundManager()->PauseMusic();
}
void S_ResumeMusic(){
	sEngine->GetSoundManager()->ResumeMusic();
}
void S_SetMusicVolume(int volume){
	sEngine->GetSoundManager()->SetMusicVolume(volume);
}
void S_PlayMusic(uint musicId, int _repeat){
	sEngine->GetSoundManager()->PlayMusic(musicId, _repeat);
}
bool S_IsMusicPlaying(){
	return sEngine->GetSoundManager()->IsMusicPlaying();
}
cMusic *S_GetMusic(uint musicId){
	return sEngine->GetSoundManager()->GetMusic(musicId);
}
cSoundManager *S_GetSoundManager(){
	return sEngine->GetSoundManager();
}
uint S_AddTimedCallback(cStormCallbacker *cb){
	return sEngine->GetCallbackManager()->Add(cb);
}
void S_RemoveTimedCallback(uint id){
	sEngine->GetCallbackManager()->Remove(id);
}
cStormCallbacker *S_GetTimedCallback(uint id){
	return sEngine->GetCallbackManager()->Get(id);
}
uint S_GuiAddWidget(cGuiWidget *widget, cGuiSkin *skin){
	return sEngine->GetGuiManager()->AddWidget(widget, skin);
}
void S_GuiRemoveWidget(uint id){
	sEngine->GetGuiManager()->Remove(id);
}
cGuiWidget *S_GuiGetWidgetById(uint id){
	return sEngine->GetGuiManager()->GetWidget(id);
}
cGuiWidget *S_GuiGetWidgetByName(std::string _name){
	return sEngine->GetGuiManager()->GetWidget(_name);
}
void S_GuiHideWidgetById(uint id){
	sEngine->GetGuiManager()->HideWidget(id);
}
void S_GuiHideWidgetByName(std::string _name){
	sEngine->GetGuiManager()->HideWidget(_name);
}
void S_GuiShowWidgetById(uint id){
	sEngine->GetGuiManager()->ShowWidget(id);
}
void S_GuiShowWidgetByName(std::string _name){
	sEngine->GetGuiManager()->ShowWidget(_name);
}
cGuiManager *S_GuiGetManager(){
	return sEngine->GetGuiManager();
}
void S_AddMainState(cStormState *_state){
	sEngine->GetStateManager()->PushState(_state);
}
Uint32 S_GetTime(){
    return SDL_GetTicks();
}