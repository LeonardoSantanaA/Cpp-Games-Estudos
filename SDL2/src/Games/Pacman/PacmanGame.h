#pragma once

#include "../../Games/Game.h"
#include "PacmanLevel.h"
#include "Pacman.h"
#include "../../Graphics/SpriteSheet.h"
#include "../../Input/InputAction.h"
#include "GhostPacman.h"
#include "GhostAI.h"
#include "../../Utils/ScoreFileLoader.h"

enum PacmanGameState {
	LEVEL_STARTING = 0,
	PLAY_GAME,
	LOST_LIFE,
	GAME_OVER
};

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
	void DrawLives(Screen& screen);
	void SetupGhosts();

	PacmanMovement mPressedDirection;
	SpriteSheet mPacmanSpriteSheet;
	Pacman mPacman;
	PacmanLevel mLevel;
	int mNumLives;
	std::vector<GhostPacman> mGhosts;
	std::vector<GhostAI> mGhostAIs;
	uint32_t mReleaseGhostTimer;
	PacmanGameState mGameState;
	uint32_t mLevelStartingTimer;
	AARectangle mStringRect;

	ScoreFileLoader scoreFile;
};