#include <iostream>
#include <SDL.h>

#include "Graphics/Color.h"
#include "Graphics/ScreenBuffer.h"
#include "Graphics/Screen.h"
#include "Shapes/Line2D.h"
#include "/C++/Exercises/Star/Star/Star.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main(int argc, char* argv[]) {
	Screen theScreen;

	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

	Line2D line = { Vec2D(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), Vec2D(SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2) };
	float size = 120;
	Star star(SCREEN_WIDTH/2 - (size/2), SCREEN_HEIGHT / 2 - (size/2), size);


	/*
	float radian = 0;
	while (true) {
		SDL_Delay(100);
		radian -= 0.01f;
		theScreen.Rotate(line, radian, Color::Blue());
		theScreen.SwapScreens();
	}
	*/
	float radian = 0;
	while (true) {
		SDL_Delay(100);
		radian -= 0.1f;
		theScreen.Rotate(star, radian, Color::Yellow());
		theScreen.SwapScreens();
		theScreen.Draw(star.MidPoint(), Color::Red());
	}
	
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
	}

	return 0;
}

