#include "Tetromino.h"
#include "Playfield.h"
#include "../../Graphics/Screen.h"
#include <random>
#include "Collider.h"
#include <chrono>

constexpr int GRAVITY_DELAY = 700;

Tetromino::Tetromino() {
	GenerateTetromino();

	mDirection = TetroDirection::TET_ZERO;
	mStats = TetroStats::TET_PLAY;
}

Tetromino::~Tetromino() {
}

void Tetromino::Update(uint32_t dt) {
	if (mStats == TET_PLAY) {
		 if (mDirection == TetroDirection::TET_LEFT) {
			MoveDirection(TetroDirection::TET_LEFT);
		}
		else if (mDirection == TetroDirection::TET_RIGHT) {
			MoveDirection(TetroDirection::TET_RIGHT);
		}
		else if (mDirection == TetroDirection::TET_DOWN) {
			 MoveDirection(TetroDirection::TET_DOWN);
		}

		 countDelay += dt;
		 
		 if (countDelay >= GRAVITY_DELAY && mStats == TET_PLAY) {
			 Gravity();
			 countDelay = 0;
			 UnsetMovementDirection(TetroDirection::TET_DOWN);
		 }

	}
	else if (mStats == TET_NEXT) {
		Blocks* NextBlockRectangle = Playfield::GetNextTetrominoRect();
		int xMidNextBlockRectangle = 0;
		int yMidNextBlockRectangle = 0;
		int dirX = 0;
		int dirY = 0;

		for (auto& block : this->GetRectangles()) {
			switch (mType) {
				case TetroTypes::I:
				{
					xMidNextBlockRectangle = Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetBottomRightPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 3);
					yMidNextBlockRectangle = Playfield::GetGridPosition(0, 1).GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 4);
					this->SetRotation(TetroRotations::ROT_DOWN);
					this->Rotate();
				}
				break;

				case TetroTypes::J:
				{
					xMidNextBlockRectangle = Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetBottomRightPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 4);
					yMidNextBlockRectangle = Playfield::GetGridPosition(0, 1).GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 3);
				}
				break;

				case TetroTypes::L:
				{
					xMidNextBlockRectangle = Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetBottomRightPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 3);
					yMidNextBlockRectangle = Playfield::GetGridPosition(0, 1).GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 3);
				}
				break;

				case TetroTypes::O:
				{
					xMidNextBlockRectangle = Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetBottomRightPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 3);
					yMidNextBlockRectangle = Playfield::GetGridPosition(0, 1).GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 3);
				}
				break;

				case TetroTypes::S:
				{
					xMidNextBlockRectangle = Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetBottomRightPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 4);
					yMidNextBlockRectangle = Playfield::GetGridPosition(0, 1).GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 2);
				}
				break;

				case TetroTypes::T:
				{
					xMidNextBlockRectangle = Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetBottomRightPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 3);
					yMidNextBlockRectangle = Playfield::GetGridPosition(0, 1).GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 3);
				}
				break;

				case TetroTypes::Z:
				{
					xMidNextBlockRectangle = Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetBottomRightPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 4);
					yMidNextBlockRectangle = Playfield::GetGridPosition(0, 1).GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 3);
				}
				break;
			}

				if (block.GetTopLeftPoint().GetX() < xMidNextBlockRectangle) {
					dirX = 1;
				}
				else if (block.GetTopLeftPoint().GetX() > xMidNextBlockRectangle) {
					dirX = -1;
				}
				else {
					dirX = 0;
				}

				if (block.GetTopLeftPoint().GetY() < yMidNextBlockRectangle) {
					dirY = 1;
				}
				else if (block.GetTopLeftPoint().GetY() > yMidNextBlockRectangle) {
					dirY = -1;
				}
				else {
					dirY = 0;
				}

				this->MoveBy(Vec2D(Playfield::GRID_BLOCK_SIZE * dirX, Playfield::GRID_BLOCK_SIZE * dirY));
		}
	}
	for (auto& block : this->GetRectangles()) {
		if (block.GetTopLeftPoint().GetY() > Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()) {
			std::cout << "adjusting position!" << std::endl;
			this->MoveBy(Vec2D(0, -Playfield::GRID_BLOCK_SIZE));
		}
	}
}

void Tetromino::Draw(Screen& screen) {
	for (auto& block : this->GetRectangles()) {
			block.Draw(screen);
	}
}

void Tetromino::PrepareToPlay() {
	int maxIterations = 1000;
	int xStart = Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint().GetX();
	int yStart = Playfield::GetGridPosition(0, 0).GetTopLeftPoint().GetY();
	int dirX = 0;
	int dirY = 0;

	while (GetRectangles()[0].GetTopLeftPoint().GetX() != randomX && maxIterations > 0) {
		if (GetRectangles()[0].GetTopLeftPoint().GetX() < xStart) {
			dirX = 1;
		}
		else if (GetRectangles()[0].GetTopLeftPoint().GetX() > xStart) {
			dirX = -1;
		}
		else {
			dirX = 0;
		}

		if (GetRectangles()[0].GetTopLeftPoint().GetY() < yStart) {
			dirY = 1;
		}
		else if (GetRectangles()[0].GetTopLeftPoint().GetY() > yStart) {
			dirY = -1;
		}
		else {
			dirY = 0;
		}

		this->MoveBy(Vec2D(Playfield::GRID_BLOCK_SIZE * dirX, Playfield::GRID_BLOCK_SIZE * dirY));
		maxIterations--;
	}
		
	this->SetRotation(TetroRotations::ROT_RIGHT);
	this->SetState(TetroStats::TET_PLAY);
	this->Rotate();
}

void Tetromino::Solidify() {	
	for (auto& block : this->GetRectangles()) {
		block.SetColor(Color(44, 33, 55, 150));
		block.SetFillColor(Color(44, 188, 166, 255));
	}

	mStats = TetroStats::TET_STATIC;

	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	UnsetMovementDirection(TetroDirection::TET_DOWN);
}

bool Tetromino::IsFree(const TetroDirection& dir) {
	mLeftTetromino.MoveTo(Vec2D(9999, 0));
	mRightTetromino.MoveTo(Vec2D(-1, 0));
	mDownTetromino.MoveTo(Vec2D(0, 0));

		for (const auto& tetromino : tetroBlocks) {
			if (tetromino.GetTopLeftPoint().GetX() < mLeftTetromino.GetTopLeftPoint().GetX()) {
				mLeftTetromino = tetromino;
			}
			else if (tetromino.GetTopLeftPoint().GetX() > mRightTetromino.GetTopLeftPoint().GetX()) {
				mRightTetromino = tetromino;
			}

			if (tetromino.GetTopLeftPoint().GetY() > mDownTetromino.GetTopLeftPoint().GetY()) {
				mDownTetromino = tetromino;
			}

		}

		switch (dir) {
			case TetroDirection::TET_LEFT:
			{
				if (VerifyCollision(mLeftTetromino, dir)) {
					return false;
				}
			}
			break;

			case TetroDirection::TET_RIGHT:
			{
				if (VerifyCollision(mRightTetromino, dir)) {
					return false;
				}
			}
			break;

			case TetroDirection::TET_DOWN:
			{
				if (VerifyCollision(mDownTetromino, dir)){
					if (mStats == TetroStats::TET_PLAY) {
						if (mDownTetromino.GetTopLeftPoint().GetY() > Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()) {
							MoveBy(Vec2D(0, -Playfield::GRID_BLOCK_SIZE));
						}
						Solidify();
						
					}
					return false;					
				}
			}
			break;
		}
	
	return true;
}

bool Tetromino::VerifyCollision(const Blocks& blockDirection, const TetroDirection& dir) const{
	if (this->GetStats() == TetroStats::TET_PLAY) {
		for (auto& tetromino : Collider::tetrominos) {
			if (tetromino.GetStats() != TetroStats::TET_PLAY) {
				for (auto& block : tetromino.GetRectangles()) {
					if (Collided(block, dir)) {
						return true;
					}
				}
			}
		}

		if (dir == TetroDirection::TET_LEFT) {
			if (blockDirection.GetTopLeftPoint().GetX() <= Playfield::GetGridPosition(0, 0).GetTopLeftPoint().GetX()) {
				return true;
			}
		}
		else if (dir == TetroDirection::TET_RIGHT) {
			if (blockDirection.GetTopLeftPoint().GetX() >= Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX()) {
				return true;
			}
		}
		else if (dir == TetroDirection::TET_DOWN) {
			if (blockDirection.GetTopLeftPoint().GetY() >= Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()) {
				return true;
			}
		}
	}
	
	return false;
}

bool Tetromino::IsFree(const Vec2D & vec) {
	for (auto& tetromino : Collider::tetrominos) {
		if (tetromino.GetStats() != TetroStats::TET_PLAY) {
			for (auto& block : tetromino.GetRectangles()) {
				if (block.GetTopLeftPoint().GetX() == vec.GetX() &&
					block.GetTopLeftPoint().GetY() == vec.GetY())
				{
					return false;
				}
			}
		}
	}

	if (vec.GetX() > Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX() || 
		vec.GetX() < Playfield::GetGridPosition(0, 0).GetTopLeftPoint().GetX() ||
		vec.GetY() > Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()
		) {
		return false;
	}

	return true;
}

bool Tetromino::IsFree(const Tetromino& tetrominoToDown, const Vec2D& vec) {
	for (const auto& blockToDown : tetrominoToDown.GetRectangles()) {
		if (!IsFree(vec)) {
			return false;
		}

	}

	return true;
}

bool Tetromino::Collided(const Blocks& block, const TetroDirection& dir) const{
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
	Blocks midBlock = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));;

	Vec2D rotVec[3];

	switch (mType) {
	case TetroTypes::I:
	{
		midBlock = GetRectangles()[1];

		if (CanRotate(this->GetType(), midBlock, rotVec)) {
			GetRectangles()[0].MoveTo(rotVec[0]);
			GetRectangles()[2].MoveTo(rotVec[1]);
			GetRectangles()[3].MoveTo(rotVec[2]);
		}
	}
	break;

	case TetroTypes::J:
	{
		midBlock = GetRectangles()[2];

		if (CanRotate(this->GetType(), midBlock, rotVec)) {
			GetRectangles()[0].MoveTo(rotVec[0]);
			GetRectangles()[1].MoveTo(rotVec[1]);
			GetRectangles()[3].MoveTo(rotVec[2]);
		}
	}
	break;

	case TetroTypes::L:
	{
		midBlock = GetRectangles()[0];

		if (CanRotate(this->GetType(), midBlock, rotVec)) {
			GetRectangles()[1].MoveTo(rotVec[0]);
			GetRectangles()[2].MoveTo(rotVec[1]);
			GetRectangles()[3].MoveTo(rotVec[2]);
		}
	}
	break;

	case TetroTypes::S:
	{
		midBlock = GetRectangles()[2];

		if (CanRotate(this->GetType(), midBlock, rotVec)) {
			GetRectangles()[0].MoveTo(rotVec[0]);
			GetRectangles()[1].MoveTo(rotVec[1]);
			GetRectangles()[3].MoveTo(rotVec[2]);
		}
	}
	break;

	case TetroTypes::T:
	{
		midBlock = GetRectangles()[1];

		if (CanRotate(this->GetType(), midBlock, rotVec)) {
			GetRectangles()[0].MoveTo(rotVec[0]);
			GetRectangles()[2].MoveTo(rotVec[1]);
			GetRectangles()[3].MoveTo(rotVec[2]);
		}
	}
	break;

	case TetroTypes::Z:
	{
		midBlock = GetRectangles()[2];

		if (CanRotate(this->GetType(), midBlock, rotVec)) {
			GetRectangles()[0].MoveTo(rotVec[0]);
			GetRectangles()[1].MoveTo(rotVec[1]);
			GetRectangles()[3].MoveTo(rotVec[2]);
		}
	}
	break;

	}

}

bool Tetromino::CanRotate(TetroTypes type, Blocks& midBlock, Vec2D* rotVec) {
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
			
			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}
			this->SetRotation(TetroRotations::ROT_LEFT);
		}
		//rotation to up
		else if(this->GetRotation() == TetroRotations::ROT_LEFT){
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - (Playfield::GRID_BLOCK_SIZE * 2));
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
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

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_RIGHT);
		}
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2));

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
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
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE * 2));

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_LEFT);
		}
		//rotation to up
		else if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2));

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_UP);
		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 2));

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}
			this->SetRotation(TetroRotations::ROT_RIGHT);
		}
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - (Playfield::GRID_BLOCK_SIZE * 2));

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());
	
			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}
			this->SetRotation(TetroRotations::ROT_DOWN);
		}
	}
	break;

	case TetroTypes::L:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_DOWN) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 2));

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_LEFT);
		}
		//rotation to up
		else if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - (Playfield::GRID_BLOCK_SIZE * 2));

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_UP);

		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE * 2));

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_RIGHT);
		}
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2));

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_DOWN);
		}
	}
	break;

	case TetroTypes::S:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_DOWN) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_LEFT);
		}
		//rotation to up
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() +Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_DOWN);
		}
		
	}
	break;

	case TetroTypes::T:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_DOWN) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_LEFT);
		}
		//rotation to up
		else if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_UP);
		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_RIGHT);
		}
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_DOWN);
		}
	}
	break;

	case TetroTypes::Z:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_DOWN) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
				}
			}

			this->SetRotation(TetroRotations::ROT_LEFT);
		}
		//rotation to up
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);

			if (this->GetStats() == TetroStats::TET_PLAY) {
				for (int i = 0; i < 3; ++i) {
					if (!IsFree(rotVec[i])) {
						std::cout << "can't rotate!" << std::endl;
						return false;
					}
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
	std::uniform_int_distribution<int> disX(1, BLOCKS_WIDTH - 4);
	std::uniform_int_distribution<int> disType(0, NUM_TYPES - 1);

	randomX = disX(generator);
	this->SetType(TetroTypes(disType(generator)));
	
	//DEBUG
	//randomX = 0;
	mType = TetroTypes::I;

	switch (mType) {
	case TetroTypes::I:
	{
		tetroBlock1->MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2->MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3->MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4->MoveTo(Playfield::GetGridPosition(randomX + 3, 0).GetTopLeftPoint());
	}
	break;

	case TetroTypes::J:
	{
		tetroBlock1->MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2->MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3->MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4->MoveTo(Playfield::GetGridPosition(randomX + 2, 1).GetTopLeftPoint());
	}
	break;

	case TetroTypes::L:
	{
		tetroBlock1->MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2->MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3->MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4->MoveTo(Playfield::GetGridPosition(randomX, 1).GetTopLeftPoint());
	}
	break;

	case TetroTypes::O:
	{
		tetroBlock1->MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2->MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3->MoveTo(Playfield::GetGridPosition(randomX, 1).GetTopLeftPoint());
		tetroBlock4->MoveTo(Playfield::GetGridPosition(randomX + 1, 1).GetTopLeftPoint());
	}
	break;

	case TetroTypes::S:
	{
		tetroBlock1->MoveTo(Playfield::GetGridPosition(randomX, 1).GetTopLeftPoint());
		tetroBlock2->MoveTo(Playfield::GetGridPosition(randomX + 1, 1).GetTopLeftPoint());
		tetroBlock3->MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock4->MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
	}
	break;

	case TetroTypes::T:
	{
		tetroBlock1->MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2->MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3->MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4->MoveTo(Playfield::GetGridPosition(randomX + 1, 1).GetTopLeftPoint());
	}
	break;

	case TetroTypes::Z:
	{
		tetroBlock1->MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2->MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3->MoveTo(Playfield::GetGridPosition(randomX + 1, 1).GetTopLeftPoint());
		tetroBlock4->MoveTo(Playfield::GetGridPosition(randomX + 2, 1).GetTopLeftPoint());
	}
	break;
	
	default: 
	{
		tetroBlock1->MoveTo(Playfield::GetGridPosition(randomX, 0).GetTopLeftPoint());
		tetroBlock2->MoveTo(Playfield::GetGridPosition(randomX + 1, 0).GetTopLeftPoint());
		tetroBlock3->MoveTo(Playfield::GetGridPosition(randomX + 2, 0).GetTopLeftPoint());
		tetroBlock4->MoveTo(Playfield::GetGridPosition(randomX + 3, 0).GetTopLeftPoint());
	}
	break;

	} //end switch

	tetroBlocks.push_back(*tetroBlock1);
	tetroBlocks.push_back(*tetroBlock2);
	tetroBlocks.push_back(*tetroBlock3);
	tetroBlocks.push_back(*tetroBlock4);

	this->SetRotation(TetroRotations::ROT_DOWN);
}

void Tetromino::MoveBy(const Vec2D& offset) {
	for (auto& tetrominos : GetRectangles()) {
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
		if (dir == TetroDirection::TET_DOWN) {	
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

