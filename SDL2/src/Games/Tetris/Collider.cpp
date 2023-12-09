#include "Collider.h"
#include "Tetromino.h"
#include "Playfield.h"

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
							if (yToDelete[i] <= Playfield::grid[0][0].GetTopLeftPoint().GetY()) {
								std::cout << "PERDEU" << std::endl;
							}
							i++;
						}
					}
				}
			}
		

		}
		
		countColumn = 0;	
	}

	for (int index = 0; index < i; ++index) {
		Collider::DeleteBlocks(tetrominos, yToDelete[index]);
		ClearBlocks(tetrominos);
	}

	if (i > 3) {
		std::cout << "TETRIS" << std::endl;
	}

	i = 0;
	delete[] yToDelete;
}

void Collider::DeleteBlocks(std::vector<Tetromino>& tetrominos, int y) {
	for (auto& tetromino : Collider::tetrominos) {
		for (auto& block : tetromino.GetRectangles()) {
			if (block.GetTopLeftPoint().GetY() == y) {
				block.SetStats(BlockStats::BL_REMOVE);
			}
		}
	}
	FallTetrominos(tetrominos, y);
}

void Collider::FallTetrominos(std::vector<Tetromino>& tetrominos, int y) {
	Blocks* downTetromino = new Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	for (auto& tetromino : Collider::tetrominos) {
		if (tetromino.GetStats() == TetroStats::TET_STATIC) {
		for (auto& tetromino : tetromino.GetRectangles()) {
			if (tetromino.GetTopLeftPoint().GetY() > downTetromino->GetTopLeftPoint().GetY()) {
				*downTetromino = tetromino;
			}
		}
		for (auto& block : tetromino.GetRectangles()) {
				if (block.GetTopLeftPoint().GetY() < y) {
					block.MoveBy(Vec2D(0, Playfield::GRID_BLOCK_SIZE));
				}
			}
		}
	}
	delete downTetromino;
}

void Collider::ClearBlocks(std::vector<Tetromino>& tetrominos) {
	//create a new vector
	std::vector<Blocks> newRectangles;
	std::vector<Tetromino> newTetrominos;
	//for (auto& tetromino : Collider::tetrominos) {
		//for (const auto& block : tetromino.GetRectangles()) {
			//std::cout << "valor antigo: " << tetromino.GetRectangles().size() << std::endl;

		//}
	//}
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

			std::cout << "vetor de blocos deletado" << std::endl;

			//free memory
			tetromino.GetRectangles().shrink_to_fit();
		}
		else {
			newTetrominos.push_back(tetromino);
		}

	}

	std::cout << "liberado memoria de vetor de tetrominos" << std::endl;
	Collider::tetrominos = std::move(newTetrominos);
	

	//for (auto& tetromino : Collider::tetrominos) {
		//for (const auto& block : tetromino.GetRectangles()) {
			//std::cout << "valor novo: " << tetromino.GetRectangles().size() << std::endl;

		//}
	//}
}