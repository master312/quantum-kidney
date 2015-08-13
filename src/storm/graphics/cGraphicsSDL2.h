//Created by Petar Ostojic
//Thu jun 10 05:40:46 2015
//This class contains SDL2 accelerated rendering code
#include "cGraphics.h"
#ifndef CGRAPHICSSDL2_H
#define CGRAPHICSSDL2_H

class cGraphicsSDL2 : public cGraphics{
public:
	cGraphicsSDL2();
	~cGraphicsSDL2();

	bool Initialize(int Width = 800, int Height = 600, int Bpp = 32, 
					std::string WindowTitle = "Storm engine");
	//Kills all graphic subsystems
	void Shutdown();

	//Clears the screen with a grey color
	void ClearScreen();
	//Flips backbuffer to the screen
	void SwapBuffers();

	//Creates actual window, and initialize openGl
	bool MakeWindow();
	//Resizes the window
	void ResizeWindow(int _width, int _height);
	//Changes window type
	//type can be STORM_WINDOW_WINDOWED, STORM_WINDOW_FULLSCREEN or STORM_WINDOW_BORDERLESS
	void SetWindowType(int type);

    //Draws an empty Rectangle
	void DrawRectangle(int x, int y, int width, int height, float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0);
	//Draws an filled rectangle
	void DrawFilledRectangle(int x, int y, int width, int height, float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0);
	//Draws a line
	void DrawLine(int x, int y, int x2, int y2, int red = 0, int green = 0, int blue = 0, int alpha = 1);

	//Returns the width of the drawing area (window)
	int GetWidth() { return width; }
	//Returns the height of the drawing area (window)
	int GetHeight() { return height; }
	//Return true if window is fullscreen
	bool IsFullscreen() { return fullscreen; }
	//Retrun window title
	std::string GetTitle() { return title; }
	//Return opengl version
	void GetApiVersion(int &api, int &major, int &minor, int &shMajor, int &shMinor);
	//Print graphics driver info
	void PrintDriverInfo();
	SDL_Renderer *GetRenderer() { return gRenderer; }
private:
	SDL_Window *gWindow;
	SDL_Renderer *gRenderer;
};

#endif