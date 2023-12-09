#pragma once

#include <vector>
#include <mutex>
#include <thread>
#include "Blocks.h"


class Tetromino;

class Collider {
public:
	static std::vector<Tetromino> tetrominos;
	static void VerifyScore(std::vector<Tetromino>& tetrominos, std::mutex& mutex);

private:
	int yy = 0;

	static void DeleteBlocks(std::vector<Tetromino>& tetrominos, int y);
	static void ClearBlocks(std::vector<Tetromino>& tetrominos);
	static void FallTetrominos(std::vector<Tetromino>& tetrominos, int y);
};