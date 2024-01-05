#include <iostream>
#include "Sound.h"
#include "../App/App.h"

int Sound::mVolumeSound = 148;
int Sound::mVolumeMusic = 15;
std::vector<Mix_Chunk*> Sound::sounds;
std::vector<Mix_Music*> Sound::musics;


int Sound::LoadMusic(std::string filename) {
	Mix_Music* m = nullptr;
	std::string path = App::Singleton().GetBasePath() + std::string("Assets/") + filename;
	m = Mix_LoadMUS(path.c_str());

	if (m == nullptr) {
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
	}

	musics.push_back(m);
	return musics.size() - 1;
}

int Sound::LoadSound(std::string filename) {
	Mix_Chunk* s = nullptr;

	std::string path = App::Singleton().GetBasePath() + std::string("Assets/") + filename;
	s = Mix_LoadWAV(path.c_str());

	if (s == nullptr) {
		std::cout << "Failed to load sound. Error: " << Mix_GetError() << std::endl;
	}

	sounds.push_back(s);
	return sounds.size() - 1;
}

void Sound::SetVolumeSound(int v) {
	mVolumeSound = (MIX_MAX_VOLUME * v) / 100;
}

void Sound::SetVolumeMusic(int v) {
	mVolumeMusic = (MIX_MAX_VOLUME * v) / 100;
}


int Sound::PlayMusic(int m) {
	if (Mix_PlayingMusic() == 0) {
		Mix_VolumeMusic(mVolumeMusic);
		Mix_PlayMusic(musics[m], -1);
	}

	return 0;
}

int Sound::PlaySound(int s) {
	//if (Mix_PlayingMusic() == 0) {
		Mix_Volume(-1, mVolumeSound);
		Mix_PlayChannel(-1, sounds[s], 0);
	//}

	return 0;
}

int Sound::InitMixer() {
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_Mixer couldn't init. Error: " << Mix_GetError() << std::endl;
		return -1;
	}
	std::cout << "mixer started." << std::endl;
	return 0;
}

void Sound::QuitMixer() {
	for (int s = 0; s < sounds.size(); s++) {
		Mix_FreeChunk(sounds[s]);
		sounds[s] = nullptr;
	}
	for (int m = 0; m < musics.size(); m++) {
		Mix_FreeMusic(musics[m]);
		musics[m] = nullptr;
	}
	Mix_Quit();
}

void Sound::TogglePlay() {
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}