#include "Collider.h"
#include "Tetromino.h"
#include "Playfield.h"
#include "Blocks.h"
#include <thread>

std::vector<Tetromino> Collider::tetrominos;

void Collider::VerifyScore(std::vector<Tetromino>& tetrominos, std::mutex& mutex) {
	std::lock_guard<std::mutex> lock(mutex);
	std::cout << "recursos bloqueados para uso da thread de VerifyScore" << std::endl;

	int countLine = 0;

	for (int yy = BLOCKS_HEIGHT - 1; yy > 0; yy--) {
		for (auto& tetromino : tetrominos) {
			if (tetromino.GetStats() != TetroStats::TET_PLAY) {
				for (auto& block : tetromino.GetRectangles()) {
					if (Playfield::grid[0][yy].GetTopLeftPoint().GetY() == block.GetTopLeftPoint().GetY()) {
						countLine++;
						if (countLine == BLOCKS_WIDTH) {
							Collider::DeleteBlocks(tetrominos, block.GetTopLeftPoint().GetY());
							ClearBlocks(tetrominos);
							//break;
							//std::cout << "pode deletar!" << std::endl;
						}
						//std::cout << "contador: " << count << std::endl;
					}
				}
			}
		

		}
		countLine = 0;
	}
}

void Collider::DeleteBlocks(std::vector<Tetromino>& tetrominos, int y) {
	for (auto& tetromino : Collider::tetrominos) {
		for (auto& block : tetromino.GetRectangles()) {
			if (block.GetTopLeftPoint().GetY() == y) {
				block.SetStats(BlockStats::BL_REMOVE);
			}
		}
	}
	//AnimationDestroy(y);
	FallTetrominos(tetrominos, y);
}

//void Collider::AnimationDestroy(int y) {
//	int count = 0;
//
//	while (count <= 1000) {
//		count++;
//	}
//
//	if (count >= 1000) {
//		for (auto& tetromino : Collider::tetrominos) {
//			if (tetromino.GetStats() == TetroStats::TET_STATIC) {
//				for (auto& block : tetromino.GetRectangles()) {
//					if (block.GetTopLeftPoint().GetY() == y) {
//						block.SetColor(Color::Red());
//					}
//				}
//			}
//		}
//		//std::this_thread::sleep_for(std::chrono::milliseconds(500)));
//		
//	}
//
//}

void Collider::FallTetrominos(std::vector<Tetromino>& tetrominos, int y) {
	Blocks downTetromino = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	for (auto& tetromino : Collider::tetrominos) {
		if (tetromino.GetStats() == TetroStats::TET_STATIC) {
		for (const auto& tetromino : tetromino.GetRectangles()) {
			if (tetromino.GetTopLeftPoint().GetY() > downTetromino.GetTopLeftPoint().GetY()) {
				downTetromino = tetromino;
			}
		}
		for (auto& block : tetromino.GetRectangles()) {
				if (downTetromino.GetTopLeftPoint().GetY() <= y) {
					tetromino.MoveBy(Vec2D(0, Playfield::GRID_BLOCK_SIZE));
				}
				if (downTetromino.GetTopLeftPoint().GetY() > Playfield::GetGridPosition(0, BLOCKS_HEIGHT - 1).GetTopLeftPoint().GetY()) {
					tetromino.MoveBy(Vec2D(0, -Playfield::GRID_BLOCK_SIZE));
				}
			}
		}
	}
}



void Collider::ClearBlocks(std::vector<Tetromino>& tetrominos) {
	std::cout << "chamano clear blocks" << std::endl;

	//for (auto& tetromino : Collider::tetrominos) {
		//for (const auto& block : tetromino.GetRectangles()) {
			//std::cout << "valor antigo: " << tetromino.GetRectangles().size() << std::endl;

		//}
	//}
	for (auto& tetromino : Collider::tetrominos) {
		//create a new vector
		std::vector<Blocks> newRectangles;

		// push into new vector only blocks where stats is BL_PLAY
		for (const auto& block : tetromino.GetRectangles()) {
			if (block.GetStats() != BlockStats::BL_REMOVE) {
				newRectangles.push_back(block);
			}
		}

		// change my vector to newRectangle vector
		tetromino.GetRectangles() = std::move(newRectangles);

		if (tetromino.GetRectangles().empty()) {
			// transforms my vector in a empty vector
			tetromino.GetRectangles() = std::vector<Blocks>();

			//free memory
			tetromino.GetRectangles().shrink_to_fit();
		}

	}

	//for (auto& tetromino : Collider::tetrominos) {
		//for (const auto& block : tetromino.GetRectangles()) {
			//std::cout << "valor novo: " << tetromino.GetRectangles().size() << std::endl;

		//}
	//}
}