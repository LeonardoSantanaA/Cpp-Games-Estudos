#pragma once

#include "../../Games/Game.h"
#include "PacmanLevel.h"
#include "Pacman.h"
#include "../../Graphics/SpriteSheet.h"
#include "../../Input/InputAction.h"

class PacmanGame: public Game {

	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;

private:
	void ResetGame();
	void UpdatePacmanMovement();
	void HandleGameControllerState(uint32_t dt, InputState state, PacmanMovement direction);
	void ResetLevel();

	PacmanMovement mPressedDirection;
	SpriteSheet mPacmanSpriteSheet;
	Pacman mPacman;
	PacmanLevel mLevel;
};