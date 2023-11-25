#pragma once

#include "../Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakoutGameLevel.h"
#include "../../Utils/ScoreFileLoader.h"
#include <vector>


enum BreakoutGameStates {
	IN_PLAY = 0,
	IN_SERVE,
	IN_GAME_OVER
};

class BreakOut: public Game {
public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;

	inline int GetLevelScore() { return mScore; }
//	inline void SetLevelScore(int val) { mScore = val; }

private:
	const int NUM_LIVES = 3;
	
	void ResetGame(size_t toLevel = 0);

	inline BreakoutGameLevel& GetCurrentLevel() { return mLevels[mCurrentLevel]; }
	void SetToServeState();

	bool IsBallPassedCutoffY() const;
	void ReduceLifeByOne();
	bool IsGameOver() const { return mLives < 0; }

	ScoreFileLoader scoreFile;

	const float INITIAL_BALL_SPEED = 100.0f;
	const Vec2D INITIAL_BALL_VELOCITY = Vec2D(100, -100);
	Paddle mPaddle;
	Ball mBall;
	LevelBoundary mLevelBoundary;
	std::vector<BreakoutGameLevel> mLevels;
	size_t mCurrentLevel;
	BreakoutGameStates mGameState;
	int mLives;
	int mScore;
	float mYCutoff;
};