#include "Collider.h"
#include "Tetromino.h"
#include "Playfield.h"
#include "Blocks.h"

std::vector<Tetromino> Collider::tetrominos;

void Collider::VerifyScore() {
	int count = 0;

	for (int yy = BLOCKS_HEIGHT - 1; yy > 0; yy--) {
		for (auto& tetromino : Collider::tetrominos) {
			for (auto& block : tetromino.GetRectangles()) {
				if (Playfield::grid[0][yy].GetTopLeftPoint().GetY() == block.GetTopLeftPoint().GetY()) {
					count++;
					if (count == BLOCKS_WIDTH) {
						Collider::DeleteBlocks(block.GetTopLeftPoint().GetY());
						//std::cout << "pode deletar!" << std::endl;
					}
					//std::cout << "contador: " << count << std::endl;
				}
			}

		}
		count = 0;
	}

	ClearBlocks();
}

void Collider::DeleteBlocks(int y) {
	for (auto& tetromino : Collider::tetrominos) {
		for (auto& block : tetromino.GetRectangles()) {
			if (block.GetTopLeftPoint().GetY() == y) {
				block.SetStats(BlockStats::BL_REMOVE);
				
			}
		}
	}

	
}

void Collider::ClearBlocks() {
	for (auto& tetromino : Collider::tetrominos) {
		for (const auto& block : tetromino.GetRectangles()) {
			std::cout << "valor antigo: " << tetromino.GetRectangles().size() << std::endl;

		}
	}
	for (auto& tetromino : Collider::tetrominos) {
		// Crie um novo vetor para armazenar os elementos a serem mantidos
		std::vector<Blocks> newRectangles;

		// Preencha o novo vetor apenas com os elementos que não precisam ser removidos
		for (const auto& block : tetromino.GetRectangles()) {
			if (block.GetStats() != BlockStats::BL_REMOVE) {
				newRectangles.push_back(block);
			}
		}

		// Substitua o vetor original pelo novo vetor
		tetromino.GetRectangles() = std::move(newRectangles);
	}

	for (auto& tetromino : Collider::tetrominos) {
		for (const auto& block : tetromino.GetRectangles()) {
			std::cout << "valor novo: " << tetromino.GetRectangles().size() << std::endl;

		}
	}
}

