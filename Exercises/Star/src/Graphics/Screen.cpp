#include "Screen.h"
#include "../Utils/Utils.h"
#include "../Utils/Vec2D.h"
#include "../Shapes/Line2D.h"
#include <cmath>
#include <SDL.h>
#include <iostream>
#include <cassert>
#include <random>
#include <math.h>

Screen::Screen(): mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrWindowSurface(nullptr) {

}

Screen::~Screen() {
	vecStars.clear();

	if (moptrWindow) {
		SDL_DestroyWindow(moptrWindow);
		moptrWindow = nullptr;
	}
	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Error SDL_Init Failed" << std::endl;
		return nullptr;
	}

	mWidth = w;
	mHeight = h;

	moptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

	if (moptrWindow) {
		mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);

		SDL_PixelFormat* pixelFormat = mnoptrWindowSurface->format;

		Color::InitColorFormat(pixelFormat);

		mClearColor = Color::Black();
		mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
		mBackBuffer.Clear(mClearColor);
	}

}

void Screen::SwapScreens() {
	assert(moptrWindow);
	if (moptrWindow) {
		ClearScreen();
		SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrWindowSurface, nullptr);
		SDL_UpdateWindowSurface(moptrWindow);
		mBackBuffer.Clear(mClearColor);
	}
}

void Screen::Draw(int x, int y, const Color& color) {
	assert(moptrWindow);
	if (moptrWindow) {
		mBackBuffer.SetPixel(color, x, y);
	}
}

void Screen::Draw(const Vec2D& point, const Color& color) {
	assert(moptrWindow);
	if (moptrWindow) {
		mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
	}
}

void Screen::Draw(const Line2D& line, const Color& color) {
	assert(moptrWindow);
	if (moptrWindow) {
		int dx, dy;

		int x0 = roundf(line.GetP0().GetX());
		int y0 = roundf(line.GetP0().GetY());
		int x1 = roundf(line.GetP1().GetX());
		int y1 = roundf(line.GetP1().GetY());

		dx = x1 - x0;
		dy = y1 - y0;

		signed const char ix((dx > 0) - (dx < 0)); //1 or -1
		signed const char iy((dy > 0) - (dy < 0)); //1 or -1

		dx = abs(dx) * 2;
		dy = abs(dy) * 2;

		Draw(x0, y0, color);

		if (dx >= dy) {
			//go along in the x
			int d = dy - dx / 2;
			while (x0 != x1) {
				if (d >= 0) {
					d -= dx;
					y0 += iy;
				}
				d += dy;
				x0 += ix;
				Draw(x0, y0, color);
			}
		}
		else {
			//go along in y
			int d = dx - dy / 2;
			while (y0 != y1) {
				if (d >= 0) {
					d -= dy;
					x0 += ix;
				}
				d += dx;
				y0 += iy;
				Draw(x0, y0, color);
			}
		}
	}
}

void Screen::Draw(Star& star, const Color& color) {
	for (int i = 0; i < 6; i++) {
		Draw(star.GetVertice(i), color);
	}
}

void  Screen::Rotate(Line2D& line, float radian, const Color& color) {
	Vec2D newVec = line.GetP1();
	
	newVec.Rotate(radian, line.GetP0());
	line.SetP1(newVec);
	Draw(line, color);
}

void Screen::Rotate(Star& star, float radian, const Color& color) {
	for (int i = 0; i < 6; i++) {
		Vec2D starVertice0 = star.GetVertice(i).GetP0();
		Vec2D starVertice1 = star.GetVertice(i).GetP1();
		starVertice0.Rotate(radian, star.MidPoint());
		starVertice1.Rotate(radian, star.MidPoint());
		Line2D starLine(starVertice0, starVertice1);
		Draw(starLine, color);
	}
}

//This metod will change the parameters to the random values
void Screen::RandomizeSpawnScreen(int& width, int& height) {
	std::random_device rW;
	std::default_random_engine eW(rW());
	std::uniform_int_distribution<int> uniform_dist_width(10, (Width() - 100));
	width = uniform_dist_width(eW);

	std::random_device rH;
	std::default_random_engine eH(rH());
	std::uniform_int_distribution<int> uniform_dist_height(10, (Height() - 100));
	height = uniform_dist_height(eH);
}

void Screen::RandomRotateStar(const int qtd, const Color& color) {
	for (size_t i = 0; i < qtd; i++) {
		std::random_device rA;
		std::default_random_engine eA(rA());
		std::uniform_real_distribution<float> uniform_real_speed(0, TWO_PI);
		float randSpeed = uniform_real_speed(eA);
		vecStars[i].SetRotationSpeed(randSpeed);

		Rotate(vecStars[i], vecStars[i].GetRotationSpeed(), color);
	}
}

void Screen::GenerateStars(const int qtd, const Color& color) {
	int widthRand = 0;
	int heightRand = 0;
	for (size_t i = 0; i < qtd; i++) {
		RandomizeSpawnScreen(widthRand, heightRand);
		vecStars.push_back(Star(widthRand, heightRand));
	}
	RandomRotateStar(qtd, color);
}

void Screen::ClearScreen() {
	assert(moptrWindow);
	if (moptrWindow) {
		SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor());
	}
}