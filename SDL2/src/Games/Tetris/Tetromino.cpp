#include "Tetromino.h"
#include "Playfield.h"
#include "../../Graphics/Screen.h"


void Tetromino::Init() {
	AARectangle tetroBlock1 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	//std::cout << playfield.GetGridPosition(5, 5).GetTopLeftPoint().GetX() << std::endl;

	tetroBlock1.MoveTo(Playfield::GetGridPosition(5, 5).GetTopLeftPoint());
	tetroBlocks.push_back(tetroBlock1);
	tetroBlock1.MoveBy(Vec2D(-24, 0));


	AARectangle tetroBlock2 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));;
	tetroBlock2.MoveTo(Playfield::GetGridPosition(6, 5).GetTopLeftPoint());
	tetroBlocks.push_back(tetroBlock2);

	AARectangle tetroBlock3 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));;
	tetroBlock3.MoveTo(Playfield::GetGridPosition(7, 5).GetTopLeftPoint());
	tetroBlocks.push_back(tetroBlock3);

	AARectangle tetroBlock4 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));;
	tetroBlock4.MoveTo(Playfield::GetGridPosition(6, 4).GetTopLeftPoint());
	tetroBlocks.push_back(tetroBlock4);


	mDirection = TetroDirection::TET_ZERO;
	mStats = TetroStats::TET_PLAY;
}

void Tetromino::Update(uint32_t dt) {

	if (mStats == TET_PLAY) {
		if ((mDirection & TetroDirection::TET_LEFT) == TetroDirection::TET_LEFT 
				&& (mDirection & TetroDirection::TET_RIGHT) == TetroDirection::TET_RIGHT) {
			mDirection = TetroDirection::TET_ZERO;
		}
		if (mDirection == TetroDirection::TET_LEFT) {
			MoveDirection(TetroDirection::TET_LEFT);
		}
		else if (mDirection == TetroDirection::TET_RIGHT) {
			MoveDirection(TetroDirection::TET_RIGHT);
		}

		countDelay++;
		
		if (countDelay >= 100) {
			Gravity();
			countDelay = 0;
		}
	}

}

void Tetromino::Draw(Screen& screen) {
	for (const auto& tetrominos : tetroBlocks) {
		screen.Draw(tetrominos, Color::Cyan(), true, Color::White());
	}

}

bool Tetromino::IsFree(const TetroDirection& dir) {
	AARectangle leftTetromino = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	leftTetromino.MoveTo(Vec2D(9999, 0));

	AARectangle rightTetromino = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));

	AARectangle downTetromino = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	downTetromino.MoveTo(Vec2D(0, 0));

	for (const auto& tetromino : tetroBlocks) {
		if (tetromino.GetTopLeftPoint().GetX() < leftTetromino.GetTopLeftPoint().GetX()) {
			leftTetromino = tetromino;
		}else if (tetromino.GetTopLeftPoint().GetX() > rightTetromino.GetTopLeftPoint().GetX()) {
			rightTetromino = tetromino;
		}

		if (tetromino.GetTopLeftPoint().GetY() > downTetromino.GetTopLeftPoint().GetY()) {
			downTetromino = tetromino;
		}
	}
	if (dir == TetroDirection::TET_LEFT) {
		if (leftTetromino.GetTopLeftPoint().GetX() <= Playfield::GetGridPosition(0, 0).GetTopLeftPoint().GetX()) {
			return false;
		}
	}
	else if (dir == TetroDirection::TET_RIGHT) {
		if (rightTetromino.GetTopLeftPoint().GetX() >= Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX()) {
			return false;
		}
	}
	else if (dir == TetroDirection::TET_DOWN) {
		if (downTetromino.GetTopLeftPoint().GetY() >= Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()) {
			return false;
		}
	}

	return true;
}

void Tetromino::MoveBy(const Vec2D& offset) {
	for (auto& tetrominos : tetroBlocks) {
		tetrominos.MoveBy(offset);
	}
}

void Tetromino::MoveDirection(const TetroDirection& dir) {
		if (dir == TetroDirection::TET_LEFT) {
			if (IsFree(dir)) {
				MoveBy(Vec2D(-Playfield::GRID_BLOCK_SIZE, 0));
			}
			UnsetMovementDirection(TetroDirection::TET_LEFT);
		}
		else if (dir == TetroDirection::TET_RIGHT) {
			if (IsFree(dir)) {
				MoveBy(Vec2D(Playfield::GRID_BLOCK_SIZE, 0));
			}
			
			UnsetMovementDirection(TetroDirection::TET_RIGHT);
		}
}

void Tetromino::Gravity() {
	if (IsFree(TetroDirection::TET_DOWN)) {
		MoveBy(Vec2D(0, Playfield::GRID_BLOCK_SIZE));
	}
}