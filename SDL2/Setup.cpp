#include <iostream>
#include <SDL.h>

#include "Graphics/Color.h"
#include "Graphics/ScreenBuffer.h"
#include "Graphics/Screen.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFCATION = 3;

int main(int argc, char* argv[]) {
	Screen theScreen;

	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFCATION);
	theScreen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Yellow());
	theScreen.SwapScreens();

	//std::cout << "The window pixel format is: " << SDL_GetPixelFormatName(pixelFormat->format);

	SDL_Event sdlEvent;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}

	return 0;
}

