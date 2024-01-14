#pragma once

#include "../Game.h"
#include "Ship.h"


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

 

	void ResetGame();
};