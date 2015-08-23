//Created by Petar Ostojic
//Thu Feb 19 23:45:17 2015
//TODO Someday: Error checks on set functions
#include <vector>
#include <fstream>
#include <map>
#include "../defines.h"
#include "../fLogs.h"
#include "../cData.h"
#include "sAnimFrameGroup.h"
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
	//Sets how many frames of this animation should be displayed
        //pre one second
	void SetFps(int _fps) { fps = _fps; };
	//Set how many times will animation be repeated
	void SetRepetitions(int _repetations) { repetations = _repetations; }
	void SetIsLoadedFromFile(bool b) { isFile = b; }
	void SetFirstFrame(int f) { firstFrame = f; }
	void SetLastFrame(int f) { lastFrame = f; }
	void SetFilename(std::string _filename) { filename = _filename; }
        
        //Return 'sAnimFrameGroup' object with @_name
        sAnimFrameGroup *GetGroup(std::string _name) { return &groups[_name]; }
        //Creates new frame group named @_name, that starts at @start
        //and ends at @end.
        //If group with same @_name already exists, it will be overwritten
        void AddFrameGroup(std::string _name, int start, int end);
        //Returns pointer to std::map that contains all 
        //frame groups of this animation
        std::map<std::string, sAnimFrameGroup>
            *GetFrameGroups() { return &groups; }
        //Makes start and end frames of this animation equal to
        //group named @name
        void SetFrameGroup(std::string name);
        
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
	//If animaiton is made up of multiple textures
        //this function will return texture ID for @frame
        //but if animation is made up of texture sections, it will return
        //section ID for @frame
        //This will cause error if out 'frame' is out of range
	uint GetFrame(int frame) { return textures[frame]; }
	//Return number of textures(frames) in this animation
	int GetFramesCount() { return (int)textures.size(); }
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
	//Names of frame groups
        std::map<std::string, sAnimFrameGroup> groups;
        //Name of the group that is currently being displayed
        std::string curGroup;
        
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