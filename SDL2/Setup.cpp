#include <locale>

#include <iostream>
#include "src/App/App.h"
#include "src/Games/Tetris/Playfield.h"
#include "src/Utils/Sound.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");

	if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION)) {
		App::Singleton().Run();
	}

	Playfield::liberarRecursos();
	Sound::QuitMixer();

	return 0;
}