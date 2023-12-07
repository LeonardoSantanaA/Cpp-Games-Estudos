#include "Playfield.h"
#include "../../Utils/Vec2D.h"
#include "../../App/App.h"
#include "../../Graphics/Screen.h"

AARectangle Playfield::grid[BLOCKS_WIDTH][BLOCKS_HEIGHT];

const int Playfield::GRID_BLOCK_SIZE = 12;

void Playfield::Init() {
	int startX = (App::Singleton().Width() - (BLOCKS_WIDTH * GRID_BLOCK_SIZE)) / 2;

	for (int xx = 0; xx < BLOCKS_WIDTH; xx++) {
		for (int yy = 0; yy < BLOCKS_HEIGHT; yy++) {
			grid[xx][yy] = AARectangle(Vec2D(xx * GRID_BLOCK_SIZE, yy * GRID_BLOCK_SIZE), 
				Vec2D((xx * GRID_BLOCK_SIZE) + GRID_BLOCK_SIZE, (yy * GRID_BLOCK_SIZE) + GRID_BLOCK_SIZE));
			grid[xx][yy].MoveBy(Vec2D(startX, 0));
		}
	}

}

void Playfield::Update(uint32_t dt) {

}

void Playfield::Draw(Screen& screen) {
	for (int xx = 0; xx < BLOCKS_WIDTH; xx++) {
		for (int yy = 0; yy < BLOCKS_HEIGHT; yy++) {
			screen.Draw(grid[xx][yy], Color::White(), true, Color::Black());
		}
	}
}