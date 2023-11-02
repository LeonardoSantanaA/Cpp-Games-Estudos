#include <iostream>
#include <SDL.h>

#include "src/Graphics/Color.h"
#include "src/Graphics/ScreenBuffer.h"
#include "src/Graphics/Screen.h"
#include "src/Shapes/Line2D.h"
#include "src/Shapes/Triangle.h"
#include "src/Shapes/AARectangle.h"
#include "src/Shapes/Circle.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main(int argc, char* argv[]) {
	Screen theScreen;

	theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

	AARectangle rect = { Vec2D(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25), 50, 50 };
	Triangle triangle = { Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110) };
	Circle circle = { Vec2D(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 50), 50 };

	theScreen.Draw(triangle, Color::Red());
	theScreen.Draw(rect, Color::Blue());
	theScreen.Draw(circle, Color::Pink());

	/*
	//ROTATION LINE EXERCISE
	Line2D line = { Vec2D(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), Vec2D(SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2) };

	float radian = 0;
	while (true) {
		SDL_Delay(100);
		radian -= 0.0001f;
		theScreen.RotateLine(line, radian, Color::Blue());
		theScreen.SwapScreens();
	}
	*/

	//theScreen.Draw(line, Color::White());
	//theScreen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Yellow());

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

