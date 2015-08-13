#include "cGraphicsOpenGL.h"
#if BUILD_OPENGL > 0

cGraphicsOpenGL::cGraphicsOpenGL(){
	width = height = bpp = 0;
	title = "";
	fullscreen = false;
}
cGraphicsOpenGL::~cGraphicsOpenGL(){
	Shutdown();
}
bool cGraphicsOpenGL::Initialize(int Width, int Height, int Bpp, 
		std::string WindowTitle){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); 
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	width = Width;
	height = Height;
	bpp = Bpp;
	title = WindowTitle;
	return true;
}
void cGraphicsOpenGL::Shutdown(){
	SDL_GL_DeleteContext(gContext); 
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

void cGraphicsOpenGL::ClearScreen(){
	glClear(GL_COLOR_BUFFER_BIT);
}
void cGraphicsOpenGL::SwapBuffers(){
	SDL_GL_SwapWindow(gWindow);
}
bool cGraphicsOpenGL::MakeWindow(){
	int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	gWindow = SDL_CreateWindow(title.c_str(), 
								SDL_WINDOWPOS_CENTERED, 
								SDL_WINDOWPOS_CENTERED, 
								width, height, flags);
	if(gWindow == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cGraphicsOpenGL", "Could not create window");
		return false;
	}
	gContext = SDL_GL_CreateContext(gWindow);
	//glewExperimental = GL_TRUE; 
	GLenum glewError = glewInit();

	int maxTextureSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
	maxTextureWidth = maxTextureSize;
	maxTextureHeight = maxTextureSize;

	PrintDriverInfo();	//Prints Driver info
	if(glewError != GLEW_OK){
		StormPrintLog(STORM_LOG_ERROR, "cGraphicsOpenGL",
			" %s \nMinimum OpenGL version must be 2\n Minimum shader version 1.30", 
			glewGetErrorString(glewError));
		return false;
	}
	SDL_GL_SetSwapInterval(1);
	glClearColor(0.6, 0.6, 0.6, 255);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 1, -1);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	//glShadeModel(GL_SMOOTH);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_SCISSOR_TEST);
	return true;
}
void cGraphicsOpenGL::ResizeWindow(int _width, int _height){
	width = _width;
	height = _height;
	SDL_SetWindowSize(gWindow, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 1, -1);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
    ClearScreen();
    StormPrintLog(STORM_LOG_INFO, "cGraphicsOpenGL", 
					"New window size: %dx%d", width, height);
}
void cGraphicsOpenGL::SetWindowType(int type){
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
			StormPrintLog(STORM_LOG_WARNING, "cGraphicsOpenGL", 
				"Borderless window not supported yet");
			break;
	}
}

void cGraphicsOpenGL::DrawRectangle(int x, int y, int width, int height, 
							float red, float green, float blue, float alpha){
	glColor4f(red, green, blue, alpha);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y + height);
		glVertex2f(x + width, y + height);
		glVertex2f(x + width, y);
        glVertex2f(x, y);
    glEnd();
}
void cGraphicsOpenGL::DrawFilledRectangle(int x, int y, int width, int height, 
							float red, float green, float blue, float alpha){
    glColor4f(red, green, blue, alpha);
    glBegin(GL_QUADS);
        glVertex2f(x, y + height);
		glVertex2f(x + width, y + height);
		glVertex2f(x + width, y);
        glVertex2f(x, y);
    glEnd();
}
void cGraphicsOpenGL::DrawLine(int x, int y, int x2, int y2, 
									int red, int green, int blue, int alpha){
	glLineWidth(1.5);
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
		glVertex2f(x, y);
		glVertex2f(x2, y2);
	glEnd();
}
void cGraphicsOpenGL::GetApiVersion(int &api, int &major, int &minor, 
												int &shMajor, int &shMinor){
	api = STORM_API_OPENGL;
	char *str = (char*)glGetString(GL_VERSION);
	sscanf(str, "%d.%d", &major, &minor);
	char *str2 = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	sscanf(str2, "%d.%d", &shMajor, &shMinor);
}
void cGraphicsOpenGL::PrintDriverInfo(){
	std::cout << "OpenGL Info:" << std::endl;
	std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "   Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << " Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "  Shading: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Max width: " << maxTextureWidth << std::endl;
	std::cout << "Max height: " << maxTextureHeight << std::endl;
}

#endif