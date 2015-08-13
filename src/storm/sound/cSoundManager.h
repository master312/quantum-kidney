//Created by Petar Ostojic
//Tue Mar 3 04:39:29 2015
#include "cMusic.h"
#include "cSound.h"
#ifndef CSOUNDMANAGER_H
#define CSOUNDMANAGER_H

class cSoundManager{
public:
	//Sound volume
	uint soundVolume;
	//Music volume
	uint musicVolume;
	
	//ID of music that is currently playing
	uint musicPlaying;

	cSoundManager();
	virtual ~cSoundManager();

	//Initialize sound subsystems
	//Return true if everything is OK, or false if there was an error
	virtual bool Initialize(int frenquency = 44100);
	//Unloads all loaded files, and shutdown all sound subsystems
	virtual void Shutdown();

	//Loads sound from file, return sound ID
	virtual uint LoadSound(std::string filename);
	//Unloads specified sound
	virtual void DeleteSound(uint soundId);
	//Unloads all loaded sound
	virtual void DeleteAllSounds();
	//Change sound volume, form 0 to 128
	virtual void SetSoundVolume(int volume);
	//Play specified sound
	virtual void PlaySound(uint soundId, int _repeat = 0);
	//Stop sound
	virtual void StopSound(uint soundId);
	//Returns pointer to actual sound object, of NULL if object is not found
	virtual cSound *GetSound(uint soundId);
	//Returns current sound volume
	int GetSoundVolume() { return soundVolume; }

	//Loads music file, return music ID 
	virtual uint LoadMusic(std::string filename);
	//Unloads specified music 
	virtual void DeleteMusic(uint musicId);
	//Unloads all loaded music
	virtual void DeleteAllMusic();
	//Stop music
	virtual void StopMusic();
	//Pause music
	virtual void PauseMusic();
	//Resume music (if any paused)
	virtual void ResumeMusic();
	//Change music volume, from 0 to 128
	virtual void SetMusicVolume(int volume);
	//Play 'musicId'; If some music is already playing, it will be halted
	virtual void PlayMusic(uint musicId, int _repeat = -1);
	//IsMusicPlaying() should be called before this function
	//Return true if music is playing
	virtual bool IsMusicPlaying();
	//Returns pointer to actual music object, of NULL if object is not found
	virtual cMusic *GetMusic(uint musicId);
	//Returns ID of music that is currently playing
	uint GetMusicPlaying() { return musicPlaying; }
	//Returns current music volume
	int GetMusicVolume() { return musicVolume; }
};

#endif