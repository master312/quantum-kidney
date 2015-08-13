#include "cGraphics.h"

cGraphics::cGraphics(){
	width = height = bpp = 0;
	title = "";
	fullscreen = false;
}
cGraphics::~cGraphics(){
	//Shutdown();
}
bool cGraphics::Initialize(int Width, int Height, int Bpp, std::string WindowTitle){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
	return false;
}
void cGraphics::Shutdown(){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
void cGraphics::ClearScreen(){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
void cGraphics::SwapBuffers(){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
bool cGraphics::MakeWindow(){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
	return false;
}
void cGraphics::ResizeWindow(int _width, int _height){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
void cGraphics::SetWindowType(int type){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
void cGraphics::DrawRectangle(int x, int y, int width, int height, float red, float green, float blue, float alpha){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
void cGraphics::DrawFilledRectangle(int x, int y, int width, int height, float red, float green, float blue, float alpha){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
void cGraphics::DrawLine(int x, int y, int x2, int y2, int red, int green, int blue, int alpha){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
void cGraphics::GetApiVersion(int &api, int &major, int &minor, int &shMajor, int &shMinor){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}
void cGraphics::PrintDriverInfo(){
	std::cout << "cGraphics ERROR: Template class called" << std::endl;
}