#include "Collider.h"
#include "Tetromino.h"
#include "Playfield.h"


std::vector<Tetromino> Collider::tetrominos;

bool Collider::IsColliding() {
	if (tetrominos.size() > 1) {
		for (auto& tetromino : tetrominos) {
			if (tetromino.GetStats() != TetroStats::TET_PLAY) {
				for (auto& block : tetromino.GetRectangles()) {
					if (CollideWithTetrominoInPlay(block)) {
						return true;
					}
				}	
			}
		}
	}


	return false;
}

bool Collider::CollideWithTetrominoInPlay(const AARectangle& block) {
	for (auto& blockInPlay : tetrominos.back().GetRectangles()) {
		if (blockInPlay.GetTopLeftPoint().GetX() == block.GetTopLeftPoint().GetX() &&
			blockInPlay.GetTopLeftPoint().GetY() == block.GetTopLeftPoint().GetY() - (Playfield::GRID_BLOCK_SIZE * 2)){
				return true;
		}
	}
	return false;
}