#pragma once

#include "../Game.h"
#include "../../Graphics/Screen.h"
#include "Playfield.h"
#include "Tetromino.h"
#include "Collider.h"
#include <mutex>
#include "Tetromino.h"
#include "../../Utils/ScoreFileLoader.h"
#include "Ghost.h"

enum TetrisGameStates {
	TET_INPLAY = 0,
	TET_GAMEOVER
};


class Tetris: public Game {
public:
	static std::vector<Tetromino> nextTetromino;

	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
	static void GenerateTetromino();

	inline static void SetTetrisStates(TetrisGameStates newState) { mState = newState; }
	inline TetrisGameStates GetTetrisStates() { return mState; }

	inline static void IncrementScore(int increment) { 
		mScore += increment; 
		std::cout << "new score: " << Tetris::GetScore() << std::endl;
	}
	inline static int GetScore() { return mScore; }

private:
	Playfield playfield;
	Collider collider;
	Ghost ghost;

	Tetromino* tetrominoInPlay;

	std::thread threadVerifyScore;
	std::thread tetrominoUpdateThread;
	std::mutex mMutex;

	ScoreFileLoader scoreFile;

	const int BLOCK_SIZE = 16;
	int countDelay = 0;
	static int mScore;
	static TetrisGameStates mState;

	static void GenerateNextTetromino();
	void RestartGame();

	const int WIDTH_BLOCKS = 10;
	const int HEIGHT_BLOCKS = 20;
};