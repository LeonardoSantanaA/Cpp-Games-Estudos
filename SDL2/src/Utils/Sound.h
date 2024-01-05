#pragma once

#include <vector>
#include <string>
#include "SDL_mixer.h"

class Sound {
private:
	static int mVolumeSound;
	static int mVolumeMusic;
	std::string mPath;

	static std::vector<Mix_Chunk*> sounds;
	static std::vector<Mix_Music*> musics;

public:
	//Sound(std::string path, bool music = false);
	Sound() {};

	int LoadMusic(std::string filename);
	int LoadSound(std::string filename);

	static void SetVolumeSound(int v);
	static void SetVolumeMusic(int v);

	int PlayMusic(int m);
	int PlaySound(int s);

	static int InitMixer();
	static void QuitMixer();

	void TogglePlay();

};