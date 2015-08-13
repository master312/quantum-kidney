//Created by Petar Ostojic
//Mon Feb 16 20:50:59 2015
#include "../defines.h"
#include <iostream>
#include <math.h>
#ifndef STEXTURE_H
#define STEXTURE_H
//TODO: Created sRect in sTextureSection!

struct sRect{
	int x, y;
	int w, h;
	sRect(){
		x = y = 0;
		w = h = 0;
	}
	sRect(int _x, int _y){
		x = _y;
		y = _y;
	}
	sRect(int _x, int _y, int _width, int _height){
		x = _x;
		y = _y;
		w = _width;
		h = _height;
	}
	bool IsCollision(int _x, int _y){
		return _x > x && _x < x + w && _y > y && _y < y + h;
	}
};

struct sRectFloat{
	float x, y;
	int w, h;
	sRectFloat(){
		x = y = 0.0f;
		w = h = 0;
	}
	sRectFloat(float _x, float _y){
		x = _y;
		y = _y;
	}
	sRectFloat(float _x, float _y, int _width, int _height){
		x = _x;
		y = _y;
		w = _width;
		h = _height;
	}
	bool IsCollision(float _x, float _y){
		return _x > x && _x < x + w && _y > y && _y < y + h;
	}
};

struct sPoint{
	int x;
	int y;
	sPoint(){
		x = 0;
		y = 0;
	}
	sPoint(int _x, int _y){
		x = _x;
		y = _y;
	}
	double Distance(sPoint p){
		//x^2 + y^2 = dist^2
		int distX = (p.x + x) * (p.x + x);
		int distY = (p.y + y) * (p.y + y);
		std::cout << "WARNING!: sTexture.h CHECK Distance funcition in struct point. It may not work properly" << std::endl;
		double dist = sqrt(distX - distY);
		return dist;
	}
	sPoint operator* (float _x){
		sPoint tmpP(x, y);
		tmpP.x *= _x;
		tmpP.y *= _x;
		return tmpP;
	}
	void operator*= (float _x){
		x *= _x;
		y *= _x;
	}
};

struct sTexture{
	//Represents texture part
	unsigned int glTexture;		//ID of GL texture (Used in OPENGL rendering)
	SDL_Texture *sdlTexture;	//Pointer to SDL_Texture (Used in SDL2 rendering)
	std::string filename;		//Filename of texture
	int width;					//Texture width
	int height;					//Texture height
	int memory;					//Memory usage in kilobytes
	int usage;					//Number of objects using this texture; Texture CAN NOT be deleted if this is greater then zero
	sTexture(){
		glTexture = 0;
		sdlTexture = NULL;
		filename = "";
		width = height = memory = usage = 0;
	}
	sTexture(uint _texture, std::string _filename, int w, int h, int _memory){
		sdlTexture = NULL;
		glTexture = _texture;
		filename = _filename;
		width = w;
		height = h;
		memory = _memory;
		usage = 0;
	}
	sTexture(SDL_Texture *_texture, std::string _filename, int w, int h, int _memory){
		sdlTexture = _texture;
		glTexture = 0;
		filename = _filename;
		width = w;
		height = h;
		memory = _memory;
		usage = 0;
	}
};

struct sTextureSection{
	uint texture;				//ID of sTexture
	//TODO: Created sRect here!
	int x;						//Start X location of selected texture part
	int y;						//Start Y location of selected texture part
	int width;					//Width of selected part
	int height;					//Height of selected part
	sTextureSection() { 
		texture = 0;
		x = y = width = height = 0;
	}
	sTextureSection(uint _textureId, int _x, int _y, int _width, int _height){
		texture = _textureId;
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}
};

#endif