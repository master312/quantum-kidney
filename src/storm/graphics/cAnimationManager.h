//Created by Petar Ostojic
//Fri Feb 20 00:31:57 2015
#include "../defines.h"
#include "cAnimation.h"
#include "cTextureManager.h"
#include "../cBinaryFile.h"
#ifndef CANIMATIONMANAGER_H
#define CANIMATIONMANAGER_H

class cAnimationManager{
public:
	cAnimationManager(cTextureManager *_textureManager);
	~cAnimationManager();

	//Create new animation; Return animation id
	//if @useTextures is true, then @frames should be list of texture ID's
	//else, @frames should be list of texture section id's
	//WARNING! If animation is made from texture sections, all texture sections
	//		   must be on same texture, or else it will cause memory leak! 
	uint CreateAnimation(std::vector<uint> frames, int fps, bool _useTextures);
	//Load animation from file
	//This function also loads textures (frames)
	//Return animation ID
	uint LoadAnimation(std::string _filename);
	//Save this animation to file
	//@_filename is filename and location of animation file
	//@animName is name of animation. Used for animation recognition
	void SaveAnimation(std::string _filename, uint animationId);
	//Save animation to file
	//Tick all animations
	void UpdateAll();

	//Remove specified animation
	void Remove(uint animationId);
	//Remove all animations
	void RemoveAll();

	//Pause animation
	void Pause(uint animationId);
	//Pause all animations
	void PauseAll();

	//Resume animation
	void Resume(uint animationId);
	//Resume all animations
	void ResumeAll();

	//Clone animation, and returns its id
	uint CloneAnimation(uint animationId);

	//Set number of repetations for animation 
	void SetRepetitions(uint animationId, int reps);
	//Reset specified animation
	void Reset(uint animationId);
	//Reset all animations
	void ResetAll();
	//Jump animation to frame
	void JumpToFrame(uint animationId, int frame);

	//Draw animation to screen
	void DrawAnimation(uint animationId, int x, int y, float scale = 1.0, float rotation = 0);
	//Returns pointer to animations class
	cAnimation *GetAnimation(uint animationId);
	//Return number of animations
	int GetAnimationCount() { return animations.size(); }
private:
	std::map<uint, cAnimation> animations;
	cTextureManager *tManager;
};

#endif