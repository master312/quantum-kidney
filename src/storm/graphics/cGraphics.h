//Created by Petar Ostojic
//Tue Feb 17 19:50:32 2015
//This class is baseclass for all rendering modes
#include "../defines.h"
#include <iostream>
#include "../fLogs.h"
#ifndef GRAPHICS_H
#define GRAPHICS_H

class cGraphics{
public:
	int width, height, bpp;
	std::string title;
	bool fullscreen;
	int maxTextureWidth;
	int maxTextureHeight;

	cGraphics();
	virtual ~cGraphics();
	//Intializes libraryes
	//Including SDL and OpenGL
	virtual bool Initialize(int Width = 800, int Height = 600, int Bpp = 32, 
					std::string WindowTitle = "Storm engine");
	//Kills all graphic subsystems
	virtual void Shutdown();

	//Clears the screen with a grey color
	virtual void ClearScreen();
	//Flips backbuffer to the screen
	virtual void SwapBuffers();

	//Creates actual window, and initialize openGl
	virtual bool MakeWindow();
	//Resizes the window
	virtual void ResizeWindow(int _width, int _height);
	//Changes window type
	//type can be STORM_WINDOW_WINDOWED, STORM_WINDOW_FULLSCREEN or STORM_WINDOW_BORDERLESS
	virtual void SetWindowType(int type);

    //Draws an empty Rectangle
	virtual void DrawRectangle(int x, int y, int width, int height, float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0);
	//Draws an filled rectangle
	virtual void DrawFilledRectangle(int x, int y, int width, int height, float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0);
	//Draws a line
	virtual void DrawLine(int x, int y, int x2, int y2, int red = 0, int green = 0, int blue = 0, int alpha = 1);

	//Returns the width of the drawing area (window)
	virtual int GetWidth() { return width; }
	//Returns the height of the drawing area (window)
	virtual int GetHeight() { return height; }
	//Return true if window is fullscreen
	virtual bool IsFullscreen() { return fullscreen; }
	//Retrun window title
	virtual std::string GetTitle() { return title; }
	//Return opengl version
	virtual void GetApiVersion(int &api, int &major, int &minor, int &shMajor, int &shMinor);
	//Print graphics driver info
	virtual void PrintDriverInfo();

	int GetTextureMaxWidth() { return maxTextureWidth; }
	int GetTextureMaxHeight() { return maxTextureHeight; }
};

#endif