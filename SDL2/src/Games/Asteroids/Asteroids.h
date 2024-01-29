#pragma once

#include "../Game.h"
#include "Ship.h"
#include "Comet.h"
#include "../../Utils/ScoreFileLoader.h"
#include "../../Utils/Sound.h"
#include <chrono>

enum AST_STATUS {
	AST_WAIT = 0,
	AST_PLAY,
	AST_GAMEOVER
};

class Asteroids : public Game {
public:
	Asteroids();

	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;

private:
	GameController* mController;
	Ship playerShip;

	AnimatedSprite mBulletSprite;
	AnimatedSprite mPlayerSprite;
	AnimatedSprite mExplosionSprite;
	SpriteSheet mPlayerSpriteSheet;

	std::vector<Bullet> bullets;
	std::vector<Comet> comets;
	std::vector<AnimatedSprite> explosions;

	bool CanShoot();
	void GenerateComets();
	void VerifyCollisions();
	inline void SetGameStatus(AST_STATUS status) { mGameStatus = status; }
	inline AST_STATUS GetGameStatus() { return mGameStatus; }

	void InitGame();
	void ResetGame();
	inline int GetAsteroidsScore() { return mScore; }

	int countDownStay;
	int invertSeconds;
	AST_STATUS mGameStatus;
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

	ScoreFileLoader scoreFile;
	int mScore;
};