#include "App.h"
#include <iostream>
#include "../Shapes/Line2D.h"
#include "../Shapes/AARectangle.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/Circle.h"
#include "../Graphics/Color.h"

App& App::Singleton() {
	static App theApp;
	return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag) {
	mnoptrWindow = mScreen.Init(width, height, mag);
	return mnoptrWindow != nullptr;
}

void App::Run() {
	if (mnoptrWindow) {
		Line2D line = { Vec2D(0, 0), Vec2D(mScreen.Width(), mScreen.Height()) };
		AARectangle rect = { Vec2D(mScreen.Width() / 2 - 25, mScreen.Height() / 2 - 25), 50, 50 };
		Triangle triangle = { Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110) };
		Circle circle = { Vec2D(float(mScreen.Width() / 2 + 50), float(mScreen.Height() / 2 + 50)), 50 };

		//triangle.MoveTo(Vec2D(110, 110));
		//rect.MoveTo(Vec2D(85, 23));
		//circle.MoveTo(Vec2D(110, 128));

	

		SDL_Event sdlEvent;
		bool running = true;

		uint32_t lastTick = SDL_GetTicks();
		uint32_t currentTick = lastTick;

		uint32_t dt = 10;
		uint32_t accumulator = 0;

		while (running) {
			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick;

			if (frameTime > 300) {
				frameTime = 300;
			}

			lastTick = currentTick;

			accumulator += frameTime;

			//input
			while (SDL_PollEvent(&sdlEvent)) {
				switch (sdlEvent.type) {
				case SDL_QUIT:
					running = false;
					break;
				}
			}

			while (accumulator >= dt) {
				//update current scene by dt
				std::cout << "Delta time step: " << dt << std::endl;
				accumulator -= dt;
			}

			//Render.
			mScreen.Draw(triangle, Color::Red(), true, Color::Red());
			mScreen.Draw(circle, Color(0, 255, 0, 50), true, Color::Green());
			mScreen.Draw(rect, Color(0, 0, 255, 150), true, Color(0, 0, 255, 50));
			

			mScreen.SwapScreens();
		}
	}
}