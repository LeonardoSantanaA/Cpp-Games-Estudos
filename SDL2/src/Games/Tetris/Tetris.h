#pragma once

#include "../Game.h"
#include "../../Graphics/Screen.h"
#include "Playfield.h"
#include "Tetromino.h"
#include "Collider.h"
#include <mutex>
#include "Tetromino.h"


class Tetris: public Game {
public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
	static void GenerateTetromino();

private:
	Playfield playfield;
	Collider collider;

	Tetromino* tetrominoInPlay;

	std::thread threadVerifyScore;
	std::thread tetrominoUpdateThread;
	std::mutex mMutex;

	const int BLOCK_SIZE = 16;
	int countDelay = 0;

	const int WIDTH_BLOCKS = 10;
	const int HEIGHT_BLOCKS = 20;
};