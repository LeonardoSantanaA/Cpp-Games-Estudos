#pragma once

#include "../../Shapes/AARectangle.h"

#define BLOCKS_WIDTH 10
#define BLOCKS_HEIGHT 20

class Screen;

class Playfield {
public:
	void Init();
	void Update(uint32_t dt);
	void Draw(Screen& screen);

	inline AARectangle GetGridPosition(int x, int y) { return grid[x][y]; }


private:
	const int GRID_BLOCK_SIZE = 12;
	AARectangle grid[BLOCKS_WIDTH][BLOCKS_HEIGHT];
};