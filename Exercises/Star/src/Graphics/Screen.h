#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_

#include <stdint.h>
#include "ScreenBuffer.h"
#include "Color.h"
#include "../Shapes/Star.h"
#include <vector>

class Vec2D;
class Line2D;
class Star;
struct SDL_Window;
struct SDL_Surface;

class Screen {
public:
	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
	void SwapScreens();

	inline void SetClearColor(const Color& clearColor) {
		mClearColor = clearColor;
	}

	inline uint32_t Width() const { return mWidth; }
	inline uint32_t Height() const { return mHeight; }
	inline std::vector<Star> GetStars() const { return vecStars; }

	//Draw Methods
	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);
	void Draw(const Line2D& line, const Color& color);
	void Draw(Star& star, const Color& color);
	void Rotate(Line2D& line, float radian, const Color& color);
	void Rotate(Star& star, float radian, const Color& color);

	void GenerateStars(const int qtd, const Color& color);

private:
	Screen(const Screen& screen);
	//Screen& operator=(const Screen& screen);

	std::vector<Star> vecStars;

	void RandomizeSpawnScreen(int& width, int& height);
	void RandomRotateStar(const int qtd, const Color& color);
	void ClearScreen();

	uint32_t mWidth;
	uint32_t mHeight;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* moptrWindow;
	SDL_Surface* mnoptrWindowSurface;
};

#endif