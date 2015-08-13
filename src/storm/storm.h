//Created by Petar Ostojic;
//Mon Feb 16 20:47:17 2015
//Main engine class for controlling every other class;
#include "fLogs.h"
#include "graphics/cGraphicsOpenGL.h"
#include "graphics/cGraphicsSDL2.h"
#include "graphics/cTextureManagerOpenGL.h"
#include "graphics/cTextureManagerSDL2.h"
#include "graphics/cAnimationManager.h"
#include "graphics/cFontManagerOpenGL.h"
#include "graphics/cFontManagerSDL2.h"
#include "sound/cSoundManagerSDL2.h"
#include "events/cEventManager.h"
#include "cStateManager.h"
#include "cTimedCallbackManager.h"
#include <map>
#ifndef STORM_H
#define STORM_H
//WARNING: If texture height is bigger then hardware supports, it will be split into chunks
//	But it texture width is bigger then hardware supports, it will be dropped!

//TODO: Fix GUI event handling. Do not handle keyboard events on gui, if not needed
//	-'Eat' mouse event if clicked on gui
//DONE: Create separated class for Timed Function Callbacks
//	-TODO: Add option for timed callback function, on separated thread
//TODO: Resource loading on separated threads
//TODO: Multiple animations in one file
//TODO: Finish TODO lists from all classes ...
//TODO Someday: Add one more logic thread
//TODO Someday: Borderless window


//DONE: Texture usage. Do not free textures unless thay are not used anymore
//..... Same texture now can not be loaded multiple times

//DONE: Binary file reader ... (.readInt()  .readFloat() ....)
//DONE: Create Function callback on interval system 
//DONE: Input handling from storm class
//DONE: Sound manager
//DONE: States(process) manager
//DONE: Load/save animations to/from binary config files; 
//Next: Configuration files parser (sFile.h, sFileParser.h) |20 min to optimize old one
//Next: Network manager (layer on top of ENet library) ...this can take a while

//DONE: Event handling system
// -There is no 'handle events' in state.
// 	Every object that needs to access events have HandleEvent function
// 	that is added as callback to event handled. This way event 'eating' function
//	will be possible
class cGuiManager;

class storm{
public:
	storm();
	~storm();
	//Initialize all subsystems of framework
	//and create new window based on previously set window arguments.
	//Return true, if everything is initialized ok
	//@Api = What rendering api to use; STORM_API_SDL, STORM_API_OPENGL etc...
	bool Initialize(int _api);
	//De-initialize all subsystems and free all memory
	void Quit();
	//Main tick function. Must be continually in 'infinite' loop
	//to handle all engine stuff. Should be called before anything else in main loop
	void Tick();
	//This function redraws the window
	//MUST! Always be called at the end of rendering (loop)function
	void FlipScreen();
	//Clears screen
	void ClearScreen();

	//Return true while engine is running
	bool IsRunning() { return isRunning; }
	//Stop engine
	void Stop() { isRunning = false; }
	//Return true if graphics should be rendered
	bool IsGraphicsTick();

	void SetWindowSize(int width, int height) {wWidth = width; wHeight = height;}
	void SetWindowBpp(int bpp) { wBpp = bpp; }
	void SetWindowTitle(std::string title) { wTitle = title; }
	void SetWindowType(int type) { wType = type; }
	void ResizeWindow(int width, int height);

	//Should draw debug info on screen
	void SetDebug(bool d) { isDebug = d; }

	//Return pointer to graphics manager
	cGraphics *GetGraphicsManager() { return mGraphics; }
	//Returns pointer to texture manager
	cTextureManager *GetTextureManager() { return mTexture; }
	//Returns pointer to animation manager
	cAnimationManager *GetAnimationManager() { return mAnimation; }
	//Returns pointer to font manager
	cFontManager *GetFontManager() { return mFont; }
	//Returns pointer to events manager
	cEventManager *GetEventManager() { return mEvents; }
	//Returns pointer to raw input manager
	cInput *GetInputManager() { return mEvents->GetInputManager(); }
	//Returns pointer to sound manager
	cSoundManager *GetSoundManager() { return mSound; }
	//Returns pointer to state manager
	cStateManager *GetStateManager() { return mState; }
	//Returns pointer to GuiManager object
	cGuiManager *GetGuiManager() { return guiManager; }
	//Returns pointer to TimedCallbacke manager
	cTimedCallbackManager *GetCallbackManager() { return tCallbackManager; }
	//Returns delta time
	int GetDelta() { return delta; }
private:
	//What graphics api is currently in use
	int api;
	//Is program running
	bool isRunning;

	//Pointer to graphics manager
	cGraphics *mGraphics;
	//Window parameters
	int wWidth, wHeight, wBpp, wType;
	std::string wTitle;

	//Should draw debug info on screen
	bool isDebug;

	//Time of last graphics tick
	Uint32 lastGraphTick;
	//Time of last logic tick
	Uint32 lastLogicTick;
	//Target(maximum) graphics FPS
	int targetGraphics;
	//Target logic ticks pre sec
	int targetLogic;
	//How much time has passed since last logic tick (ms)
	int delta;

	// //Pointer to input manager
	cEventManager *mEvents;
	//Pointer to texture manager
	cTextureManager *mTexture;
	//Pointer to animation manager
	cAnimationManager *mAnimation;
	//Pointer to font manager
	cFontManager *mFont;
	//Default glyphs to be generated. Contains all ASCII characters
	std::string defFontGlyphs;
	//Pointer to sound manager
	cSoundManager *mSound;
	//Pointer to state manager
	cStateManager *mState;	//TODO someday: This class can be deleted, and merged into storm class
	//Pointer to GUI manager object
	cGuiManager *guiManager;
	//Timed Callback manager
	cTimedCallbackManager *tCallbackManager; 
};

#endif