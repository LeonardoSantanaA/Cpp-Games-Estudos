#include "BreakOut.h"
#include <iostream>

/*
	Paddle
		- Can move side to side (by the user)
		- Stops at the edge of the screen
		- Width and Height
		- Bounces the ball
		- Bounces the ball differently based on the position that was hit on the paddle

	Ball
		- Bounces off of the walls and the paddles and blocks
		- Width and height
		- velocity position
		
	Block
		- part of the level
		- Has HP - one hit by the ball is -1 HP
		- Color and position
		- Width and Height (AARectangle)
		- Bounces the ball

	Level
		- Container that holds all of the blocks
		- Should be able to load a level from the levels.txt file
		- Handle collisions of the blocks?
		- contain the walls/edges of the screens
		- Reset the level

	Game
		- Contains all of the objects (paddle, ball, levels)
		- Player which has 3 lives
		- States - Serve the ball, In Game, Game Over
		- Reset the game

*/

void BreakOut::Init(GameController& controller) {
	std::cout << "Break Out Game Init" << std::endl;
}

void BreakOut::Update(uint32_t dt) {
	std::cout << "Break Out Update!" << std::endl;
}

void BreakOut::Draw(Screen& screen) {
	std::cout << "Break Out Draw!" << std::endl;
}

std::string BreakOut::GetName() const {
	return "Break Out!";
}