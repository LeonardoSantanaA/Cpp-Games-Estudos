#include "BreakOut.h"
#include "../../Input/GameController.h"
#include "../../App/App.h"
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
	controller.ClearAll();
	ResetGame();

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state) {
			if (GameController::IsPressed(state)) {
				mPaddle.SetMovementDirection(PaddleDirection::LEFT);
			}
			else {
				mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
			}
		};
	controller.AddInputActionForKey(leftKeyAction);

	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state) {
		if (GameController::IsPressed(state)) {
			mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
		}
		else {
			mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
		}
		};
	controller.AddInputActionForKey(rightKeyAction);
}

void BreakOut::Update(uint32_t dt) {
	mBall.Update(dt);
	mPaddle.Update(dt, mBall);

	BoundaryEdge edge;

	if (mPaddle.Bounce(mBall)) {
		return;
	}

	if (mLevelBoundary.HasCollided(mBall, edge)) {
		mBall.Bounce(edge);
		return;
	}
}

void BreakOut::Draw(Screen& screen) {
	mBall.Draw(screen);
	mPaddle.Draw(screen);
	screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());
}

const std::string& BreakOut::GetName() const {
	static std::string name = "Break Out!";

	return name;
}

void BreakOut::ResetGame() {
	AARectangle paddleRect = { Vec2D(App::Singleton().Width() / 2 - Paddle::PADDLE_WIDTH / 2, App::Singleton().Height() - 3 * Paddle::PADDLE_HEIGHT), 
		Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT };
	AARectangle levelBoundary = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height() };

	mLevelBoundary = { levelBoundary };

	mPaddle.Init(paddleRect, levelBoundary);
	mBall.MoveTo(Vec2D(App::Singleton().Width() / 2, App::Singleton().Height() / 2));

	mBall.SetVelocity(INITIAL_BALL_VELOCITY);
}