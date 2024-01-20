#pragma once

#include "../Game.h"
#include "Ship.h"
#include "Comet.h"


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
	SpriteSheet mPlayerSpriteSheet;

	std::vector<Bullet> bullets;
	std::vector<Comet> comets;

	bool CanShoot();
	void GenerateComets();

	void ResetGame();

	int tempCount = 0;
};