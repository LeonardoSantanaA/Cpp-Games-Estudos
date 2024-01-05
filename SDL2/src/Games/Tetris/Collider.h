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
	static void SetGameOver();
	static inline bool IsTetris() { return tetris; }
	static inline bool DesableTetris() { return tetris = false; }

private:
	int yy = 0;

	static bool tetris;
	static void DeleteBlocks(std::vector<Tetromino>& tetrominos, int y);
	static void ClearBlocks(std::vector<Tetromino>& tetrominos);
	static bool FallTetrominos(std::vector<Tetromino>& tetrominos, int index, int qtd);
};