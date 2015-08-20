//Created by Petar Ostojic
//Mon Feb 16 20:48:40 2015
//This class is used for controlling all subsystems of framework
//This is ONLY class you should be accessing from you program
#include "storm.h"
#ifndef ENGINE_H
#define ENGINE_H

class cGuiManager;
class cGuiWidget;
class cGuiSkin;

//TODO: Render text in square or something ...used for nice input boxes
//Render text in rectangle with given width and height, and crop everything that is not in it.

//Initialize all subsystems of framework
//and create new window based on previously set window arguments.
//Return true, if everything is initialized ok
//@Api = What rendering api to use; STORM_API_SDL, STORM_API_OPENGL etc...
bool S_InitEngine(int api);
//De-initialize all subsystems and free all memory
//Call this method ONLY when program ends. To quit engine call S_Stop() !
void S_Quit();
//Tick engine logic, and handle events
void S_Tick();
//MUST! Always be called at the end of rendering (loop) function to refresh screen
//and update timing
void S_FlipScreen();
//Clear screen
void S_ClearScreen();
//Return true while engine is running
bool S_IsRunning();
//Stop engine
void S_Stop();
//Return true if graphics should be rendered
bool S_IsGraphicsTick();
//Return delta time
int S_GetDelta();

//Set window size; DO NOT USE THIS FOR RESIZE! Use S_ResizeWindow
//TODO: Check this. This crashes program
void S_SetWindowSize(int width, int height);
//Set window bbp;
void S_SetWindowBpp(int bpp);
//Set windows title
void S_SetWindowTitle(std::string title);
//Set window type
void S_SetWindowType(int type);
//Returns window size
sRect S_GetWindowSize();
//Return window title
std::string S_GetWindowTitle();
//Return true if window is fullscreen
bool S_IsWindowFullscreen();
//Resize window
void S_ResizeWindow(int width, int height);
//Draws rectangle on screen
void S_DrawRect(int x, int y, int width, int height, float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0);
void S_DrawRect(sRect *rect, float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0);
//Draws rectangle filled with color
void S_DrawFillRect(int x, int y, int width, int height, float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0);
void S_DrawFillRect(sRect *rect, float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0);
//Draws line on screen
void DrawLine(int x, int y, int x2, int y2, int red = 0, int green = 0, int blue = 0, int alpha = 1);
//Return pointer to graphics manager
cGraphics *S_GetGraphicsManager();

//Loads texture from file
uint S_LoadTexture(std::string filename);
//Creates new texture sections
uint S_CreateSection(uint textureId, int x, int y, int w, int h);
//Draws texture to screen
void S_DrawTexture(uint textureId, int x, int y, float scale = 1, float rot = 0);
//Draws scaled texture to screen
void S_DrawTextureScaled(uint textureId, sRect *rect, float rot = 0);
//Draw cropped texture, cropped from 'rect', and drawn to X:Y coordinates
void S_DrawTextureCropped(uint textureId, sRect *rect, int x, int y, float rot = 0);
//Draws texture section to screen
void S_DrawSection(uint sectionId, int x, int y, float scale = 1, float rot = 0);
//Draw scaled texture section
void S_DrawSectionScaled(uint sectionId, sRect *rect, float rot = 0);
//Draw copped section. Section will be cropped to 'crop' rect
void S_DrawSectionCropped(uint sectionId, sRect *crop, int x, int y, float rot = 0);
//Reloads specified texture
void S_ReloadTexture(uint textureId);
//Reloads all textures
void S_ReloadTextures();
//Unloads specified texture
void S_UnloadTexture(uint textureId);
//Remove texture section
void S_RemoveSection(uint sectionId);
//Returns pointer to texture
sTexture *S_GetTexture(uint textureId);
//Returns pointer to section
sTextureSection *S_GetSection(uint sectionId);
//Returns pointer to texture manager
cTextureManager *S_GetTextureManager();

//Creates new animation; Returns animation id
uint S_CreateAnimation(std::vector<uint> &frames, int fps, bool useTextures);
//Loads animation from file
uint S_LoadAnimation(std::string filename);
//Saves animation to file
void S_SaveAnimation(uint animationId, std::string filename);
//Removes animation; This function will unload all frames
void S_RemoveAnimation(uint animationId);
//Pauses animation
void S_PauseAnimation(uint animationId);
//Pause all animations
void S_PauseAnimations();
//Resume animation
void S_ResumeAnimation(uint animationId);
//Resume all animations
void S_ResumeAnimations();
//Clone animation
uint S_CloneAnimation(uint animationId);
//Draws animation on screen
void S_DrawAnimation(uint animationId, int x, int y, float scale = 1.0, float rotation = 0);
//Returns pointer to specific animation
cAnimation *S_GetAnimation(uint animationId);
//Returns pointer to animation manager
cAnimationManager *S_GetAnimationManager();

//Set glyphs to be generated on font load
void S_SetGlyphs(std::string glyphs);
//Loads font
bool S_LoadFont(std::string filename, std::string fontName, int size);
//Unload font
void S_UnloadFont(std::string fontName);
//Unload all fonts
void S_UnloadFonts();
//Renders text on screen
void S_RenderText(std::string text, int x, int y, std::string font = "default", 
		float r = 0, float g = 0, float b = 0, float scale = 1.0, float rotation = 0.0);
//TODO: Render text in square or something ...used for nice input boxes
//Render text in rectangle with given width and height, and crop everything that is not in it.
sRect S_GetTextSize(std::string text, std::string font = "default");
//Returns pointer to sFont object
sFont *S_GetFont(std::string font);
//Returns pointer to font manager
cFontManager *S_GetFontManager();

//Adds new handler function callback to events manager
void S_AddEventHandler(cStormCallbacker *cb, std::string name);
//Removes handler function from event manager
void S_RemoveEventHandler(std::string name);
//Eats current event
void S_EatEvent(std::string name);
//Return true if key is pressed
bool S_IsKeyDown(eKey key);
//Return true if key is not pressed
bool S_IsKeyUp(eKey key);
//Return mouse X coordinate	
int S_GetMouseX();
//Return mouse Y coordinate
int S_GetMouseY();
//Return amount of mouse scroll.
int S_GetMouseScroll();
//Return mouse buttons states
bool S_IsMouseLeft();
bool S_IsMouseRight();
bool S_IsMouseMiddle();
//Start scanning for text input
void S_StartTextInput();
//Stop scanning for text input
void S_StopTextInput();
//Return true if text input is enabled
bool S_IsTextInput();
//End text input. Returns inputed string;
std::string S_GetTextInput();
//Returns pointer to input manager class
cInput *S_GetInputManager();

//Load sound form file; Returns sound ID
uint S_LoadSound(std::string filename);
//Unloads specified sound
void S_DeleteSound(uint soundId);
//Unloads all loaded sounds
void S_DeleteAllSounds();
//Change sound volume; From 0 to 128
void S_SetSoundVolume(int volume);
//Plays specified sound
void S_PlaySound(uint soundId, int _repeat = 0);
//Stops specified sound
void S_StopSound(uint soundId);
//Returns pointer to actual sound object, or NULL if object is not found
cSound *S_GetSound(uint soundId);
//Loads music from file; Returns music ID
uint S_LoadMusic(std::string filename);
//Unloads specified music 
void S_DeleteMusic(uint musicId);
//Unloads all loaded music
void S_DeleteAllMusic();
//Stop music// TODO: Test if this functions halts paused music
void S_StopMusic();
//Pause music; Music can ONLY be resumed using S_ResumeMusic()
void S_PauseMusic();
//Resume music (if any paused)
void S_ResumeMusic();
//Change music volume, from 0 to 128
void S_SetMusicVolume(int volume);
//Play 'musicId'; If some music is already playing, it will be halted
void S_PlayMusic(uint musicId, int _repeat = -1);
//Return true if music is playing
bool S_IsMusicPlaying();
//Returns pointer to actual music object, of NULL if object is not found
cMusic *S_GetMusic(uint musicId);
//Returns pointer to sound manager
cSoundManager *S_GetSoundManager();

//Adds function to 'Automatic callback on timer' system
//Returns entry ID
uint S_AddTimedCallback(cStormCallbacker *cb);
//Removes callback from system
void S_RemoveTimedCallback(uint id);
//Return pointer to 'cStormCallbacker' with entry @id
cStormCallbacker *S_GetTimedCallback(uint id);

//Adds widget to GUI manager. Returns widget ID
uint S_GuiAddWidget(cGuiWidget *widget, cGuiSkin *skin = NULL);
//Deletes widget object with matching ID
void S_GuiRemoveWidget(uint id);
//Returns pointer to widget matching ID, or NULL if not found
cGuiWidget *S_GuiGetWidgetById(uint id);
//Returns pointer to widget matching NAME, or NULL if not found
cGuiWidget *S_GuiGetWidgetByName(std::string _name);
//Hide gui widget by Id
void S_GuiHideWidgetById(uint id);
//Hide gui widget by name
void S_GuiHideWidgetByName(std::string _name);
//Show gui widget by ID
void S_GuiShowWidgetById(uint id);
//Show gui widget by name
void S_GuiShowWidgetByName(std::string _name);
//Returns pointer to GUI manager
cGuiManager *S_GuiGetManager();

//Adds main state to engine. This is class that will basically contain main game class; 
//Should be called ONLY one time at the beginning of the program
//If main state ends, program will close
void S_AddMainState(cStormState *_state);

//Returns how much time has passed form start of the program
Uint32 S_GetTime();

#endif