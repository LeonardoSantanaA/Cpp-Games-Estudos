#pragma once

#include <vector>
#include <mutex>
#include <thread>
#include "../../Utils/Sound.h"
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
	static bool tetris;

	Sound sound;
	int scoreSoundEffect = sound.LoadSound("ScoreNormal.wav");
	int tetrisSoundEffect = sound.LoadSound("TetrisEffect.wav");
	int gameOverSoundEffect = sound.LoadSound("GameOver.wav");

	void SoundEffect();

	static void DeleteBlocks(std::vector<Tetromino>& tetrominos, int y);
	static void ClearBlocks(std::vector<Tetromino>& tetrominos);
	static bool FallTetrominos(std::vector<Tetromino>& tetrominos, int index, int qtd);
};