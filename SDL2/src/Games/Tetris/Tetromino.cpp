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
		//if ((mDirection & TetroDirection::TET_LEFT) == TetroDirection::TET_LEFT 
			//	&& (mDirection & TetroDirection::TET_RIGHT) == TetroDirection::TET_RIGHT) {
			//mDirection = TetroDirection::TET_ZERO;
		//}
		 if (mDirection == TetroDirection::TET_LEFT) {
			MoveDirection(TetroDirection::TET_LEFT);
		}
		else if (mDirection == TetroDirection::TET_RIGHT) {
			MoveDirection(TetroDirection::TET_RIGHT);
		}
		else if (mDirection == TetroDirection::TET_DOWN) {
			 MoveDirection(TetroDirection::TET_DOWN);
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

		for (const auto& tetromino : tetroBlocks) {
			if (tetromino.GetTopLeftPoint().GetX() < leftTetromino.GetTopLeftPoint().GetX()) {
				leftTetromino = tetromino;
			}
			else if (tetromino.GetTopLeftPoint().GetX() > rightTetromino.GetTopLeftPoint().GetX()) {
				
				rightTetromino = tetromino;
			}

			if (tetromino.GetTopLeftPoint().GetY() > downTetromino.GetTopLeftPoint().GetY()) {
				downTetromino = tetromino;
			}

		}
		if (dir == TetroDirection::TET_LEFT) {
				for (const auto& tetromino : Collider::tetrominos) {
					if (tetromino.GetStats() != TetroStats::TET_PLAY) {
						for (const auto& block : tetromino.GetRectangles()) {
							if (Collided(block, TetroDirection::TET_LEFT)) {
								return false;
							}
						}
					}
				}

			if (leftTetromino.GetTopLeftPoint().GetX() <= Playfield::GetGridPosition(0, 0).GetTopLeftPoint().GetX()) {

				return false;
			}
		}
		else if (dir == TetroDirection::TET_RIGHT) {
			for (const auto& tetromino : Collider::tetrominos) {
				if (tetromino.GetStats() != TetroStats::TET_PLAY) {
					for (const auto& block : tetromino.GetRectangles()) {
						if (Collided(block, TetroDirection::TET_RIGHT)) {
							return false;
						}
					}
				}
			}

			if (rightTetromino.GetTopLeftPoint().GetX() >= Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX()) {
				return false;
			}
		}
		else if (dir == TetroDirection::TET_DOWN) {
			for (const auto& tetromino : Collider::tetrominos) {
				if (tetromino.GetStats() != TetroStats::TET_PLAY) {
					for (const auto& block : tetromino.GetRectangles()) {
						if (Collided(block, TetroDirection::TET_DOWN)) {
							Solidify();
							return false;
						}
					}
				}
			}

			if (downTetromino.GetTopLeftPoint().GetY() >= Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()) {
				Solidify();
				return false;
			}
		}
	else {
		Solidify();
	}
	
	return true;
}

bool Tetromino::IsFree(const Vec2D & vec) {
	for (const auto& tetromino : Collider::tetrominos) {
		if (tetromino.GetStats() != TetroStats::TET_PLAY) {
			for (const auto& block : tetromino.GetRectangles()) {
				if (block.GetTopLeftPoint().GetX() == vec.GetX() &&
					block.GetTopLeftPoint().GetY() == vec.GetY())
				{
					std::cout << "Tem bloco na posicao!" << std::endl;
					return false;
				}
			}
		}
	}

	if (vec.GetX() > Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX() || 
		vec.GetX() < Playfield::GetGridPosition(0, 0).GetTopLeftPoint().GetX() ||
		vec.GetY() > Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()
		) {
		std::cout << "colidiu na parede!" << std::endl;
		return false;
	}

	return true;
}

bool Tetromino::Collided(const AARectangle& block, const TetroDirection& dir) {
	for (const auto& blockInPlay : Collider::tetrominos.back().GetRectangles()) {
		if (dir == TetroDirection::TET_LEFT) {
			if (blockInPlay.GetTopLeftPoint().GetY() == block.GetTopLeftPoint().GetY() &&
				blockInPlay.GetTopLeftPoint().GetX() == block.GetBottomRightPoint().GetX()) {
				return true;
			}
		}
		else if (dir == TetroDirection::TET_RIGHT) {
			if (blockInPlay.GetTopLeftPoint().GetY() == block.GetTopLeftPoint().GetY() &&
				blockInPlay.GetBottomRightPoint().GetX() == block.GetTopLeftPoint().GetX()) {
				return true;
			}
		}
		else if (dir == TetroDirection::TET_DOWN) {
			if (blockInPlay.GetTopLeftPoint().GetX() == block.GetTopLeftPoint().GetX() &&
				blockInPlay.GetTopLeftPoint().GetY() == block.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE)) {
				return true;
			}
		}

		
	}

	return false;
}

void Tetromino::Rotate() {
	AARectangle midBlock = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));;

	Vec2D rotVec[3];

	switch (mType) {
	case TetroTypes::I:
	{
		midBlock = tetroBlocks[1];

		if (CanRotate(this->GetType(), midBlock, rotVec)) {
			tetroBlocks[0].MoveTo(rotVec[0]);
			tetroBlocks[2].MoveTo(rotVec[1]);
			tetroBlocks[3].MoveTo(rotVec[2]);
		}
	}
	break;

	case TetroTypes::J:
	{
		midBlock = tetroBlocks[2];

		if (CanRotate(this->GetType(), midBlock, rotVec)) {
			tetroBlocks[0].MoveTo(rotVec[0]);
			tetroBlocks[1].MoveTo(rotVec[1]);
			tetroBlocks[2].MoveTo(rotVec[2]);
		}
	}
	break;

	}

}

bool Tetromino::CanRotate(TetroTypes type, const AARectangle& midBlock, Vec2D* rotVec) {
	switch (type) {
	case TetroTypes::I:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_DOWN) {
				rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
				rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
				rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

				rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
				rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
				rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 2));
				
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						return false;
					}
				}

				this->SetRotation(TetroRotations::ROT_LEFT);
		}
		//rotation to up
		else if(this->GetRotation() == TetroRotations::ROT_LEFT){
			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - (Playfield::GRID_BLOCK_SIZE * 2));
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			for (int i = 0; i < 3; ++i) {
				if (!IsFree(rotVec[i])) {
					return false;
				}
			}

			this->SetRotation(TetroRotations::ROT_UP);
		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE * 2));

			for (int i = 0; i < 3; ++i) {
				if (!IsFree(rotVec[i])) {
					return false;
				}
			}

			this->SetRotation(TetroRotations::ROT_RIGHT);
		}
		else {
			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2));


			for (int i = 0; i < 3; ++i) {
				if (!IsFree(rotVec[i])) {
					return false;
				}
			}

			this->SetRotation(TetroRotations::ROT_DOWN);
		}

		
	}
	break;

	case TetroTypes::J: 
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_DOWN) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 2));

			for (int i = 0; i < 3; ++i) {
				if (!IsFree(rotVec[i])) {
					return false;
				}
			}

			this->SetRotation(TetroRotations::ROT_LEFT);
		}
		//rotation to up
		else if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - (Playfield::GRID_BLOCK_SIZE * 2));

			for (int i = 0; i < 3; ++i) {
				if (!IsFree(rotVec[i])) {
					return false;
				}
			}

			this->SetRotation(TetroRotations::ROT_UP);
		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE * 2));

			for (int i = 0; i < 3; ++i) {
				if (!IsFree(rotVec[i])) {
					return false;
				}
			}

			this->SetRotation(TetroRotations::ROT_RIGHT);
		}
		else {
			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2));

			for (int i = 0; i < 3; ++i) {
				if (!IsFree(rotVec[i])) {
					return false;
				}
			}

			this->SetRotation(TetroRotations::ROT_DOWN);
		}
	}
	break;
	}

	return true;
}



void Tetromino::GenerateTetromino() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> disX(0, BLOCKS_WIDTH - 4);
	std::uniform_int_distribution<int> disType(0, NUM_TYPES - 1);



	int randomX = disX(generator);
	mType = disType(generator);
	
	//randomX = 0;
	mType = 0;

	switch (mType) {
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

	this->SetRotation(TetroRotations::ROT_DOWN);
	
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
		else if (dir == TetroDirection::TET_DOWN) {
			
			if (IsFree(dir)) {
				MoveBy(Vec2D(0, Playfield::GRID_BLOCK_SIZE));
			}
			UnsetMovementDirection(TetroDirection::TET_DOWN);
		}
}

void Tetromino::Gravity() {
	if (IsFree(TetroDirection::TET_DOWN)) {
		MoveBy(Vec2D(0, Playfield::GRID_BLOCK_SIZE));
	}
}

