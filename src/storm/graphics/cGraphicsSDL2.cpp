#include "cGraphicsSDL2.h"

cGraphicsSDL2::cGraphicsSDL2(){
	width = height = bpp = 0;
	title = "";
	fullscreen = false;
}
cGraphicsSDL2::~cGraphicsSDL2(){
	Shutdown();
}

bool cGraphicsSDL2::Initialize(int Width, int Height, int Bpp, std::string WindowTitle){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		return false;
	}
	width = Width;
	height = Height;
	bpp = Bpp;
	title = WindowTitle;
	return true;
}
void cGraphicsSDL2::Shutdown(){
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

void cGraphicsSDL2::ClearScreen(){
	SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 200);
	SDL_RenderClear(gRenderer);
}
void cGraphicsSDL2::SwapBuffers(){
	SDL_RenderPresent(gRenderer);
}

bool cGraphicsSDL2::MakeWindow(){
	int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 
												SDL_WINDOWPOS_CENTERED, 
												width, height, flags);
	if(gWindow == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cGraphicsSDL2", "Could not create window");
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gRenderer == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cGraphicsSDL2", "Could not create SDL renderer");
		return false;
	}
        SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_RendererInfo info;
	SDL_GetRendererInfo(gRenderer, &info);
	maxTextureWidth = info.max_texture_width;
	maxTextureHeight = info.max_texture_height;
	PrintDriverInfo();
	return true;
}
void cGraphicsSDL2::ResizeWindow(int _width, int _height){
	width = _width;
	height = _height;
	SDL_SetWindowSize(gWindow, width, height);
	StormPrintLog(STORM_LOG_INFO, "cGraphicsSDL2", "New window size: %dx%d", width, height);
}
void cGraphicsSDL2::SetWindowType(int type){
	fullscreen = false;
	switch(type){
		case STORM_WINDOW_WINDOWED:
			SDL_SetWindowFullscreen(gWindow, 0);
			break;
		case STORM_WINDOW_FULLSCREEN:
			SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
			fullscreen = true;
			break;
		case STORM_WINDOW_BORDERLESS:
			StormPrintLog(STORM_LOG_WARNING, "cGraphicsSDL2", 
				"Borderless window not supported yet");
			break;
	}
}

void cGraphicsSDL2::DrawRectangle(int x, int y, int width, int height, 
							float red, float green, float blue, float alpha){
	SDL_Rect tmpRect = {x, y, width, height};
	SDL_SetRenderDrawColor(gRenderer, red * 255, green * 255, blue * 255, alpha * 255);
	SDL_RenderDrawRect(gRenderer, &tmpRect);
}
void cGraphicsSDL2::DrawFilledRectangle(int x, int y, int width, int height, 
							float red, float green, float blue, float alpha){
	SDL_Rect tmpRect = {x, y, width, height};
	SDL_SetRenderDrawColor(gRenderer, red * 255, green * 255, blue * 255, alpha * 255);
	SDL_RenderFillRect(gRenderer, &tmpRect);
}
void cGraphicsSDL2::DrawLine(int x, int y, int x2, int y2, 
									int red, int green, int blue, int alpha){
	SDL_SetRenderDrawColor(gRenderer, red * 255, green * 255, blue * 255, alpha * 255);
	SDL_RenderDrawLine(gRenderer, x, y, x2, y2);
}

void cGraphicsSDL2::GetApiVersion(int &api, int &major, int &minor, 
												int &shMajor, int &shMinor){
	api = STORM_API_SDL2;
	SDL_version ver;
	SDL_GetVersion(&ver);
	major = ver.major;
	minor = ver.minor;
	shMinor = 0;
	shMinor = 0;
}
void cGraphicsSDL2::PrintDriverInfo(){
	SDL_RendererInfo info;
	SDL_GetRendererInfo(gRenderer, &info);
	std::cout << "SDL2 Info:" << std::endl;
	std::cout << "  Version: 2" << std::endl;
	std::cout << "   Vendor: UNKNOWN" << std::endl;
	std::cout << " Renderer: " << info.name << std::endl;
	std::cout << "  Shading: NONE" << std::endl;
	std::cout << "Max width: " << maxTextureWidth << std::endl;
	std::cout << "Max height: " << maxTextureHeight << std::endl;
}