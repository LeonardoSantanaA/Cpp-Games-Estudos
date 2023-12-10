#include "Collider.h"
#include "Tetromino.h"
#include "Playfield.h"
#include "Tetris.h"


std::vector<Tetromino> Collider::tetrominos;

void Collider::VerifyScore(std::vector<Tetromino>& tetrominos, std::mutex& mutex) {
	std::lock_guard<std::mutex> lock(mutex);

	int countColumn = 0;
	int* yToDelete = new int[4];
	int i = 0;

	for (int yy = BLOCKS_HEIGHT - 1; yy >= 0; yy--) {
		for (auto& tetromino : tetrominos) {
			//std::cout << "tamanho vetor tetrominos: " << tetrominos.size() << std::endl;
			if (tetromino.GetStats() != TetroStats::TET_PLAY) {
				for (auto& block : tetromino.GetRectangles()) {
					//std::cout << "tamanho vetor block: " << tetromino.GetRectangles().size() << std::endl;
					if (Playfield::grid[0][yy].GetTopLeftPoint().GetY() == block.GetTopLeftPoint().GetY()) {
						countColumn++;
						if (countColumn == BLOCKS_WIDTH) {
							yToDelete[i] = static_cast<int>(block.GetTopLeftPoint().GetY());
							Tetris::IncrementScore(10);
							if (yToDelete[i] <= Playfield::grid[0][0].GetTopLeftPoint().GetY()) {
								Tetris::SetTetrisStates(TetrisGameStates::TET_GAMEOVER);
								std::cout << "Game Over!" << std::endl;
							}
							i++;
						}
					}
				}
			}
		

		}
		
		countColumn = 0;	
	}
	int higherY = yToDelete[0];

	for (int index = 0; index < i; ++index) {
		if (yToDelete[index] > higherY) {
			higherY = yToDelete[index];
		}

		Collider::DeleteBlocks(tetrominos, yToDelete[index]);
		ClearBlocks(tetrominos);
		
	}

	FallTetrominos(tetrominos, higherY, i);

	if (i > 3) {
		std::cout << "########" << std::endl;
		std::cout << "#TETRIS#" << std::endl;
		std::cout << "########" << std::endl;
		Tetris::IncrementScore(100);
	}

	i = 0;
	delete[] yToDelete;
}

void Collider::DeleteBlocks(std::vector<Tetromino>& tetrominos, int y) {
	for (auto& tetromino : Collider::tetrominos) {
		for (auto& block : tetromino.GetRectangles()) {
			if (block.GetTopLeftPoint().GetY() == y) {
				block.SetStats(BlockStats::BL_REMOVE);
				block.SetColor(Color::Red());
			}
		}
	}

}

bool Collider::FallTetrominos(std::vector<Tetromino>& tetrominos, int y, int qtd) {
	for (auto& tetromino : Collider::tetrominos) {
		if (tetromino.GetStats() == TetroStats::TET_STATIC) {
			for (auto& block : tetromino.GetRectangles()) {
				if (block.GetTopLeftPoint().GetY() < y) {
					block.MoveBy(Vec2D(0, (Playfield::GRID_BLOCK_SIZE * (qtd))));
				}
			}
		}
	}
	return true;
}


void Collider::ClearBlocks(std::vector<Tetromino>& tetrominos) {

		//create a new vector
		std::vector<Blocks> newRectangles;
		std::vector<Tetromino> newTetrominos;

		for (auto& tetromino : Collider::tetrominos) {
			// push into new vector only blocks where stats is BL_PLAY
			for (auto& block : tetromino.GetRectangles()) {
				if (block.GetStats() != BlockStats::BL_REMOVE) {
					newRectangles.push_back(block);
				}
			}

			// change my vector to newRectangle vector
			tetromino.GetRectangles() = std::move(newRectangles);

			if (tetromino.GetRectangles().empty()) {
				// transforms my vector in a empty vector
				tetromino.GetRectangles() = std::vector<Blocks>();

				std::cout << "Blocks vector released." << std::endl;

				//free memory
				tetromino.GetRectangles().shrink_to_fit();
			}
			else {
				newTetrominos.push_back(tetromino);
			}

		}

		std::cout << "Tetrominos vector memory released." << std::endl;
		Collider::tetrominos = std::move(newTetrominos);

}