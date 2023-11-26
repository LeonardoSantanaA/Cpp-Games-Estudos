#pragma once

#include "../Game.h"
#include "../../Graphics/Screen.h"
#include "Playfield.h"
#include "Tetromino.h"

class Tetris: public Game {
public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;

private:
	Playfield playfield;
	std::vector<Tetromino> tetrominos;
	const int BLOCK_SIZE = 16;


	const int WIDTH_BLOCKS = 10;
	const int HEIGHT_BLOCKS = 20;
};