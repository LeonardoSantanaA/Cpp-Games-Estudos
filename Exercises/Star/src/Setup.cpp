#include <iostream>
#include <SDL.h>

#include "Graphics/Color.h"
#include "Graphics/ScreenBuffer.h"
#include "Graphics/Screen.h"
#include "Shapes/Line2D.h"
#include "Shapes/Star.h"
#include "Utils/Utils.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAGNIFICATION = 1;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Screen theScreen;

	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

	Line2D line = { Vec2D(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), Vec2D(SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2) };
	float size = 120;
	//Star star(SCREEN_WIDTH/2 - (size/2), SCREEN_HEIGHT / 2 - (size/2));
	theScreen.GenerateStars(10, Color::Yellow());

	/*
	float radian = 0;
	while (true) {
		SDL_Delay(100);
		radian -= 0.01f;
		theScreen.Rotate(line, radian, Color::Blue());
		theScreen.SwapScreens();
	}
	*/
	/*
	float radian = 0;
	while (true) {
		SDL_Delay(100);
		radian += 0.1f;
		theScreen.Rotate(star, radian, Color::Yellow());
		theScreen.SwapScreens();
	}
	*/

	//theScreen.Draw(line, Color::White());
	//theScreen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Yellow());
	//theScreen.Draw(star, Color::Yellow());
	//theScreen.SwapScreens();

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

		for (Star& star : theScreen.GetStars()) {
			SDL_Delay(10);
			theScreen.Rotate(star, GetRandomNumberFloat(0, TWO_PI), Color::Yellow());
		}
		
		theScreen.SwapScreens();
	}

	return 0;
}

