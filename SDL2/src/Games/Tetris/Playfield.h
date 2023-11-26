#pragma once

#include "../../Shapes/AARectangle.h"

#define BLOCKS_WIDTH 10
#define BLOCKS_HEIGHT 20

class Screen;

class Playfield {
public:
	static AARectangle grid[BLOCKS_WIDTH][BLOCKS_HEIGHT];
	static const int GRID_BLOCK_SIZE;

	void Init();
	void Update(uint32_t dt);
	void Draw(Screen& screen);

	static inline AARectangle GetGridPosition(int x, int y) { return grid[x][y]; }


private:
	
	
};