#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#ifndef DEFINES_H_
#define DEFINES_H_

#ifdef _WIN32
#define OS_WINDOWS 1
typedef unsigned int uint;
#endif

#ifdef __linux
#define OS_LINUX 1
#endif
//TODO: Mac compatibility

//IF this is set to 0, OPENGL mode will not be build
#define BUILD_OPENGL 0

#if BUILD_OPENGL
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#endif

//Version 0.14.3
#define STORM_VERSION_MAJOR 0
#define STORM_VERSION_MINOR 14
#define STORM_VERSION_FIX 3
//Rendering apis
#define STORM_API_OPENGL 1
#define STORM_API_SDL 2
#define STORM_API_SDL2 3
//Window types
#define STORM_WINDOW_WINDOWED 0
#define STORM_WINDOW_FULLSCREEN 1
#define STORM_WINDOW_BORDERLESS 2	//TODO: DOSE NOT WORK YET!
//Logging types
#define STORM_LOG_NOTSPECIFIED 0        //Default terminal text color. Visible in debug and release
#define STORM_LOG_INFO 1                //Green text color. Visible in debug mode
#define STORM_LOG_WARNING 2             //Yellow text color. Visible in debug mode
#define STORM_LOG_ERROR 3               //Red text color. Visible in debug and release mode. Logged to file
//State statuses
#define STORM_STATE_CREATED 0		//State has just been created
#define STORM_STATE_INITED 1		//State has been initialized; Ready to tick
#define STORM_STATE_PAUSED 2		//State is paused; State object will not be deleted by state manager, and it must be resumed, or deleted manually!!!
#define STORM_STATE_END 3			//State has been ended; State object will be deleted by state manager
//Currently used animation file version
#define STORM_ANIM_FILEVER 100		//1.0.0
//Interval for handling timed callback functions (ms)
#define STORM_TIMED_CALLBACK_INTERVAL 10
//Delay between GUI manager logic ticks (ms)
#define STORM_GUI_LOGIC_INTERVAL 250
//Default directory structure
#define STORM_DIR_DATA "data/"				//Location of default data directory
#define STORM_DIR_GRAPHICS "data/graphics/"	//Location of directory that contains graphics (sprites and images)
#define STORM_DIR_ANIMS "data/animations/"	//Location of directory that contains animation config files
#define STORM_DIR_MUSIC "data/music/"		//Location of directory that contains music
#define STORM_DIR_SOUND "data/sound/"		//Location of directory that contains sound effects
#define STORM_DIR_FONT "data/fonts/"		//Location of directory that contains fonts
#define STORM_FILE_CONFIG "data/config.conf"//Location of engine configuration file

#endif
