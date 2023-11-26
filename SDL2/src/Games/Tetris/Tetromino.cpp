#include "Tetromino.h"
#include "Playfield.h"
#include "../../Graphics/Screen.h"
#include <random>


void Tetromino::Init() {
	GenerateTetromino();

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
	else if (mStats == TET_STATIC) {
		//todo: STATIC TETROMINO!


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
			Solidify();
			return false;
		}
	}

	return true;
}

void Tetromino::GenerateTetromino() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> disX(0, BLOCKS_WIDTH - 4);
	std::uniform_int_distribution<int> disType(0, NUM_TYPES - 1);

	AARectangle tetroBlock1 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	AARectangle tetroBlock2 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	AARectangle tetroBlock3 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	AARectangle tetroBlock4 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));

	int randomX = disX(generator);
	int tetroType = disType(generator);
	
	switch (tetroType) {
	case TetroTypes::I:
	{
		tetroBlock1.MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2.MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3.MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4.MoveTo(Playfield::GetGridPosition(randomX + 3, 0).GetTopLeftPoint());
	}
	break;

	case TetroTypes::J:
	{
		tetroBlock1.MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2.MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3.MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4.MoveTo(Playfield::GetGridPosition(randomX + 2, 1).GetTopLeftPoint());
	}
	break;

	case TetroTypes::L:
	{
		tetroBlock1.MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2.MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3.MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4.MoveTo(Playfield::GetGridPosition(randomX, 1).GetTopLeftPoint());
	}
	break;

	case TetroTypes::O:
	{
		tetroBlock1.MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2.MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3.MoveTo(Playfield::GetGridPosition(randomX, 1).GetTopLeftPoint());
		tetroBlock4.MoveTo(Playfield::GetGridPosition(randomX + 1, 1).GetTopLeftPoint());
	}
	break;

	case TetroTypes::S:
	{
		tetroBlock1.MoveTo(Playfield::GetGridPosition(randomX, 1).GetTopLeftPoint());
		tetroBlock2.MoveTo(Playfield::GetGridPosition(randomX + 1, 1).GetTopLeftPoint());
		tetroBlock3.MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock4.MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
	}
	break;

	case TetroTypes::T:
	{
		tetroBlock1.MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2.MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3.MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4.MoveTo(Playfield::GetGridPosition(randomX + 1, 1).GetTopLeftPoint());
	}
	break;

	case TetroTypes::Z:
	{
		tetroBlock1.MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2.MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3.MoveTo(Playfield::GetGridPosition(randomX + 1, 1).GetTopLeftPoint());
		tetroBlock4.MoveTo(Playfield::GetGridPosition(randomX + 2, 1).GetTopLeftPoint());
	}
	break;
	
	default: 
	{
		tetroBlock1.MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2.MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3.MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4.MoveTo(Playfield::GetGridPosition(randomX + 3, 0).GetTopLeftPoint());
	}
	break;

	} //end switch
	tetroBlocks.push_back(tetroBlock1);
	tetroBlocks.push_back(tetroBlock2);
	tetroBlocks.push_back(tetroBlock3);
	tetroBlocks.push_back(tetroBlock4);
	
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