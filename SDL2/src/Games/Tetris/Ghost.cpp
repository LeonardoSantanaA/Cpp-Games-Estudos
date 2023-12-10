#include "Ghost.h"

Ghost::Ghost() {
	std::cout << "Ghost Started." << std::endl;

	ghostBlocks.push_back(*tetroBlock1);
	ghostBlocks.push_back(*tetroBlock2);
	ghostBlocks.push_back(*tetroBlock3);
	ghostBlocks.push_back(*tetroBlock4);

	SetState(TetroStats::TET_GHOST);

	for (auto& block : GetRectangles()) {
		block.MoveTo(Playfield::GetGridPosition(5, 5).GetTopLeftPoint());
		block.SetColor(Color(15, 56, 15, 155));
		block.SetFillColor(Color(48, 98, 48, 125));
	}
	
}

void Ghost::Update(uint32_t dt) {

	for (auto i = 0; i < Collider::tetrominos.back().GetRectangles().size(); ++i) {

		int xTetromino = Collider::tetrominos.back().GetRectangles()[i].GetTopLeftPoint().GetX();
		int dirX = 0;

		if (this->GetRectangles()[i].GetTopLeftPoint().GetX() < xTetromino) {
			dirX = 1;
		}
		else if (this->GetRectangles()[i].GetTopLeftPoint().GetX() > xTetromino) {
			dirX = -1;
		}
		else {
			dirX = 0;
		}

		this->MoveBy(Vec2D(Playfield::GRID_BLOCK_SIZE * dirX, 0));

	}

	this->SetType(Collider::tetrominos.back().GetType());
	this->SetRotation(Collider::tetrominos.back().GetRotation());
	Rotate();

	Gravity();
	
	Tetromino tetrominoInPlay = Collider::tetrominos.back();

	for (const auto& tetromino : Collider::tetrominos) {
		if (tetromino.GetStats() != TetroStats::TET_PLAY) {
			for (const auto& ghostBlock : this->GetRectangles()) {
				for (const auto& block : tetromino.GetRectangles()) {
					for (const auto blockInPlay : tetrominoInPlay.GetRectangles()) {
					if (ghostBlock.GetTopLeftPoint().GetX() == block.GetTopLeftPoint().GetX() &&
						ghostBlock.GetTopLeftPoint().GetY() >= block.GetTopLeftPoint().GetY() &&
						blockInPlay.GetTopLeftPoint().GetY() < block.GetTopLeftPoint().GetY())
								MoveBy(Vec2D(0, -Playfield::GRID_BLOCK_SIZE));
						}

				}
			}
		}

	}

}

void Ghost::Draw(Screen& screen) {
	for (auto& block : this->GetRectangles()) {
		block.Draw(screen);
	}
}

void Ghost::Gravity() {
	if (IsFree(TetroDirection::TET_DOWN)) {
		MoveBy(Vec2D(0, Playfield::GRID_BLOCK_SIZE));
	}

}

bool Ghost::IsFree(const TetroDirection& dir) {
	mLeftTetromino.MoveTo(Vec2D(9999, 0));
	mRightTetromino.MoveTo(Vec2D(-1, 0));
	mDownTetromino.MoveTo(Vec2D(0, 0));

	for (const auto& tetromino : ghostBlocks) {
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
	if (mDownTetromino.GetTopLeftPoint().GetY() > Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()) {
		MoveBy(Vec2D(0, -Playfield::GRID_BLOCK_SIZE));
	}

	switch (dir) {
	case TetroDirection::TET_DOWN:
	{
		if (VerifyCollision(mDownTetromino, dir)) {
			return false;
		}
	}
	break;
	}

	return true;
}

void Ghost::MoveBy(const Vec2D& offset) {
	for (auto& block : GetRectangles()) {
		block.MoveBy(offset);
	}
}

bool Ghost::VerifyCollision(const Blocks& blockDirection, const TetroDirection& dir) const {
	for (auto& tetromino : Collider::tetrominos) {
		if (tetromino.GetStats() != TetroStats::TET_PLAY) {
			for (auto& block : tetromino.GetRectangles()) {
				if (Collided(block, dir)) {
					return true;
				}
			}
		}
	}

	if (dir == TetroDirection::TET_DOWN) {
		if (blockDirection.GetTopLeftPoint().GetY() >= Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()) {
			return true;
		}
	}

	return false;
}


void Ghost::Rotate() {
	Blocks midBlock = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));;

	Vec2D rotVec[3];

	switch (this->GetType()) {
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
		midBlock = GetRectangles()[0];

		if (CanRotate(this->GetType(), GetRectangles()[0], rotVec)) {
			GetRectangles()[1].MoveTo(rotVec[0]);
			GetRectangles()[2].MoveTo(rotVec[1]);
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

	case TetroTypes::O:
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

bool Ghost::CanRotate(TetroTypes type, Blocks& midBlock, Vec2D* rotVec) {
	switch (type) {
	case TetroTypes::I:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 2));
		}
		//rotation to up
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - (Playfield::GRID_BLOCK_SIZE * 2));
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());


		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_RIGHT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE * 2));

		}
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2));

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

		}

	}
	break;

	case TetroTypes::J:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE * 2));

		}
		//rotation to up
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2));

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());

		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_RIGHT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 2));

		}
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE * 2);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE));
		}
	}
	break;

	case TetroTypes::L:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			//std::cout << "left" << std::endl;
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE * 2));
		}
		//rotation to up
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - (Playfield::GRID_BLOCK_SIZE * 2));

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());
		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_RIGHT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE * 2));
		}
		else{
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE * 2);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE));
		}
	}
	break;

	case TetroTypes::O:
	{
		rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
		rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
		rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

		rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
		rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
		rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + (Playfield::GRID_BLOCK_SIZE));
	}
	break;

	case TetroTypes::S:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);

		}
		//rotation to up
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);

		}

	}
	break;

	case TetroTypes::T:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX());

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
		}
		//rotation to up
		else if (this->GetRotation() == TetroRotations::ROT_UP) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());
		}
		//rotation to right
		else if (this->GetRotation() == TetroRotations::ROT_RIGHT) {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());
		}
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY());
		}
	}
	break;

	case TetroTypes::Z:
	{
		//rotation to left
		if (this->GetRotation() == TetroRotations::ROT_LEFT) {
			//std::cout << "esse aqui" << std::endl;
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() - Playfield::GRID_BLOCK_SIZE);

		}
		//rotation to up
		else {
			rotVec[0].SetX(midBlock.GetTopLeftPoint().GetX() - Playfield::GRID_BLOCK_SIZE);
			rotVec[1].SetX(midBlock.GetTopLeftPoint().GetX());
			rotVec[2].SetX(midBlock.GetTopLeftPoint().GetX() + Playfield::GRID_BLOCK_SIZE);

			rotVec[0].SetY(midBlock.GetTopLeftPoint().GetY());
			rotVec[1].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
			rotVec[2].SetY(midBlock.GetTopLeftPoint().GetY() + Playfield::GRID_BLOCK_SIZE);
		}

	}
	break;

	}

	for (int i = 0; i < 3; ++i) {
		if (!IsFree(rotVec[i])) {
			MoveBy(Vec2D(0, -Playfield::GRID_BLOCK_SIZE));
		}
	}

	return true;
}

bool Ghost::IsFree(const Vec2D& vec) {
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