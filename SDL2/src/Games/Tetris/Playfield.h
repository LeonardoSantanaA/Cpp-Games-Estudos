#pragma once

#include "../../Shapes/AARectangle.h"
#include "Blocks.h"
#include "Collider.h"

#define BLOCKS_WIDTH 10
#define BLOCKS_HEIGHT 20

class Screen;

class Playfield {
public:
	Playfield();

	static Blocks grid[BLOCKS_WIDTH][BLOCKS_HEIGHT];
	static const int GRID_BLOCK_SIZE;

	void Init();
	void Update(uint32_t dt);
	void Draw(Screen& screen);

	static inline Blocks GetGridPosition(int x, int y) { return grid[x][y]; }
	
};