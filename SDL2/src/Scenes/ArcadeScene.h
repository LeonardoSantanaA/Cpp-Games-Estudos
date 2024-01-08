#pragma once

#include "Scene.h"
#include "../Graphics/Screen.h"
#include "../Utils/Sound.h"
#include "ButtonOptionsScene.h"
#include <memory>

enum eGame {
	TETRIS = 0,
	BREAK_OUT,
	ASTEROIDS,
	PACMAN,
	NUM_GAMES
};

class Screen;

class ArcadeScene : public ButtonOptionsScene {
public:
	ArcadeScene();
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& theScreen) override;
	virtual const std::string& GetSceneName() const override;

private:
	std::unique_ptr<Scene> GetScene(eGame game);

};