//Created by Petar Ostojic
//Tue Mar 3 04:58:37 2015
#include "cSoundManager.h"
#include "cSoundSDL2.h"
#include "cMusicSDL2.h"
#include <map>
#ifndef CSOUNDMANAGERSDL2_H
#define CSOUNDMANAGERSDL2_H

class cSoundManagerSDL2 : public cSoundManager{
public:
	cSoundManagerSDL2();
	~cSoundManagerSDL2();

	//Initialize sound subsystems
	//Return true if everything is OK, or false if there was an error
	bool Initialize(int frenquency = 44100);
	//Unloads all loaded files, and shutdown all sound subsystems
	void Shutdown();

	//Loads sound from file, return sound ID
	uint LoadSound(std::string filename);
	//Unloads specified sound
	void DeleteSound(uint soundId);
	//Unloads all loaded sound
	void DeleteAllSounds();
	//Change sound volume, form 0 to 128
	void SetSoundVolume(int volume);
	//Play specified sound
	void PlaySound(uint soundId, int _repeat = 0);
	//Stop sound
	void StopSound(uint soundId);
	//Returns pointer to actual sound object, of NULL if object is not found
	cSound *GetSound(uint soundId);

	//Loads music file, return music ID 
	uint LoadMusic(std::string filename);
	//Unloads specified music 
	void DeleteMusic(uint musicId);
	//Unloads all loaded music
	void DeleteAllMusic();
	//Stop music
	void StopMusic();
	//Pause music
	void PauseMusic();
	//Resume music (if any paused)
	void ResumeMusic();
	//Change music volume, from 0 to 128
	void SetMusicVolume(int volume);
	//Play 'musicId'; If some music is already playing, it will be halted
	void PlayMusic(uint musicId, int _repeat = -1);
	//Return true if music is playing
	bool IsMusicPlaying();
	//Returns pointer to actual music object, of NULL if object is not found
	cMusic *GetMusic(uint musicId);
private:
	static const int DEFAULT_FADE_TIME = 250;	//How long will music face
	std::map<uint, cSoundSDL2*> sounds;			//All loaded sounds
	std::map<uint, cMusicSDL2*> musics;			//All loaded sounds
	bool isMusicPaused;
};

#endif