//Created by Petar Ostojic
//Thu Feb 19 23:45:17 2015
//TODO Someday: Error checks on set functions
#include <vector>
#include <fstream>
#include "../defines.h"
#include "../fLogs.h"
#include "../cData.h"
#ifndef CANIMATION_H
#define CANIMATION_H

class cAnimation{
public:
	cAnimation();
	~cAnimation();
	//Tick animation
	void Update();
	//Pause animation
	void Pause() { isPaused = true; }
	//Pause animation, and reset it to first frame
	void Stop() { Pause(); Reset(); }
	//Resume animation
	void Resume() { isPaused = false; }
	//Reset animation to first frame
	void Reset() { curFrame = firstFrame; }
	//Jump to frame
	void JumpToFrame(int frame) { curFrame = frame; }

	void AddFrame(uint _texture) { textures.push_back(_texture); }
	//Set texture for frame
	void SetTexture(uint _texture, int frame);
	//Set delay for frame
	void SetFps(int _fps) { fps = _fps; };
	//Set how many times will animation be repeated
	void SetRepetitions(int _repetations) { repetations = _repetations; }
	void SetIsLoadedFromFile(bool b) { isFile = b; }
	void SetFirstFrame(int f) { firstFrame = f; }
	void SetLastFrame(int f) { lastFrame = f; }
	void SetFilename(std::string _filename) { filename = _filename; }

	//On what frame animation starts
	int GetFirstFrame() { return firstFrame; }
	//On what frame animation ends
	int GetLastFrame() { return lastFrame; }
	//Current animation frame
	int GetCurFrame() { return curFrame; }
	//Is animation paused
	bool IsPaused() { return isPaused; }
	//How many times will this animation be repeated before it ends (stop drawing)
	int GetRepetations() { return repetations; }
	//Return texture id for given frame; This will cause error if out 'frame' is out of range
	uint GetTexture(int frame) { return textures[frame]; }
	//Return number of textures(frames) in this animation
	int GetTextureCount() { return (int)textures.size(); }
	//Return FPS of this animation
	int GetFps() { return fps; }
	//Returns animation filename;
	//This will return empty string if animation is not loaded from file 
	std::string GetFilename() { return filename; }
	//Returns texture for current frame
	uint GetCurTexture() { return textures[curFrame]; }
	//Return true if animation is done and not drawing anymore
	bool IsDone() { return isDone; }
	//Return true if animations was loaded from file
	bool IsLoadedFromFile() { return isFile; }
	//Returns weather this animation is made from multiple textures (true)
	//or sprite sheet (false)
	bool IsUseTextures() { return useTextures; }
	void SetUseTextures(bool b) { useTextures = b; }
private:
	//Vector of textures used in this animation
	//every element is one frame
	std::vector<uint> textures;
	
	//Frames pre secound for this animation
	int fps;
	//On what frame animation starts
	int firstFrame;
	//On what frame animation ends
	int lastFrame;
	//Current animation frame
	int curFrame;
	
	//Is animation paused
	bool isPaused;
	//Number of times animations should be repeated
	int repetations;
	//Time when animation was ticked last time
	Uint32 lastTick;
	//Is animation completed
	bool isDone;
	
	//Is animation loaded from file
	bool isFile;
	//Filename of animation; Used only if animation is loaded from file
	std::string filename;
	//It true, @textures is vector of texture ID's, else its list of
	//texture section ID's
	bool useTextures;
};

#endif