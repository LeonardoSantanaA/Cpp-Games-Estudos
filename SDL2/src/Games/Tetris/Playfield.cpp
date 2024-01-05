#include "Playfield.h"
#include "../../Utils/Vec2D.h"
#include "../../Graphics/Screen.h"
#include "Tetromino.h"

Blocks Playfield::grid[BLOCKS_WIDTH][BLOCKS_HEIGHT];

const int Playfield::GRID_BLOCK_SIZE = 12;

Blocks* Playfield::nextTetrominoRect = new Blocks(Vec2D(0, 0), GRID_BLOCK_SIZE * 5, GRID_BLOCK_SIZE * 4);

Playfield::Playfield() {
	std::cout << "Playfield Started." << std::endl;
	Playfield::Init();
}

Playfield::~Playfield() {
	Playfield::liberarRecursos();
	delete backgroundRectBounds;
	backgroundRectBounds = nullptr;
}

void Playfield::Init() {
	int startX = (App::Singleton().Width() - (BLOCKS_WIDTH * GRID_BLOCK_SIZE)) / 5;

	for (int xx = 0; xx < BLOCKS_WIDTH; xx++) {
		for (int yy = 0; yy < BLOCKS_HEIGHT; yy++) {
			grid[xx][yy] = Blocks(Vec2D(xx * GRID_BLOCK_SIZE, yy * GRID_BLOCK_SIZE), 
				Vec2D((xx * GRID_BLOCK_SIZE) + GRID_BLOCK_SIZE, (yy * GRID_BLOCK_SIZE) + GRID_BLOCK_SIZE));
			grid[xx][yy].MoveBy(Vec2D(startX, 0));
			grid[xx][yy].SetColor(Color(63, 172, 149, 255));
			grid[xx][yy].SetFillColor(Color(161, 239, 140, 255));
		}
	}
	
	nextTetrominoRect->MoveTo(Vec2D(GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX() + (GRID_BLOCK_SIZE * 2), GetGridPosition(0, 2).GetTopLeftPoint().GetY()));
	nextTetrominoRect->SetColor(Color(164, 20, 136, 255));
	nextTetrominoRect->SetFillColor(Color(121, 2, 98, 255));


	backgroundRectBounds->MoveTo(Vec2D(GetGridPosition(0, 0).GetTopLeftPoint().GetX(), GetGridPosition(0, 0).GetTopLeftPoint().GetY()));
	backgroundRectBounds->SetColor(Color(44, 33, 55, 255));
	backgroundRectBounds->SetFillColor(Color(19, 19, 19, 255));

	scoreRectBounds.MoveTo(Vec2D(Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2),
		Playfield::GetGridPosition(0, 12).GetTopLeftPoint().GetY()));
	scoreRectBounds.SetColor(Color(164, 20, 136, 255));
	scoreRectBounds.SetFillColor(Color(121, 2, 98, 255));
}

void Playfield::Update(uint32_t dt) {

}

void Playfield::Draw(Screen& screen) {
	AARectangle background = { Vec2D::Zero, screen.Width(), screen.Height() };
	screen.Draw(background, Color(78, 2, 146, 255), true, Color(78, 2, 146, 255));

	for (int xx = 0; xx < BLOCKS_WIDTH; xx++) {
		for (int yy = 0; yy < BLOCKS_HEIGHT; yy++) {
			Playfield::grid[xx][yy].Draw(screen);
		}
	}
	nextTetrominoRect->Draw(screen);
	backgroundRectBounds->Draw(screen);
	scoreRectBounds.Draw(screen);
}

void Playfield::liberarRecursos() {
	if (nextTetrominoRect) {
		delete nextTetrominoRect;
		nextTetrominoRect = nullptr;
	}
}