#include <iostream>
#include "ArcadeScene.h"
#include "../Input/GameController.h"
#include "../App/App.h"
#include "GameScene.h"

#include "NotImplementedScene.h"
#include "../Games/BreakOut/BreakOut.h"
#include "../Games/Tetris/Tetris.h"



ArcadeScene::ArcadeScene():
	ButtonOptionsScene({ "Tetris", "Break Out!", "Asteroids", "Pac-man"}, Color::Cyan())
{
}

void ArcadeScene::Init() {
	
	std::vector<Button::ButtonAction> actions;

	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(TETRIS));
		});

	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(BREAK_OUT));
		});

	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(ASTEROIDS));
		});

	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(PACMAN));
		});

	SetButtonActions(actions);

	ButtonOptionsScene::Init();

}
void ArcadeScene::Update(uint32_t dt) {

}

void ArcadeScene::Draw(Screen& theScreen) {
	/*
	Line2D line = { Vec2D(0, 50), Vec2D(theScreen.Width(), theScreen.Height()) };
	AARectangle rect = { Vec2D(theScreen.Width() / 2 - 25, theScreen.Height() / 2 - 25), 50, 50 };
	Triangle triangle = { Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110) };
	Circle circle = { Vec2D(float(theScreen.Width() / 2 + 50), float(theScreen.Height() / 2 + 50)), 50 };

	theScreen.Draw(triangle, Color::Red(), true, Color::Red());
	theScreen.Draw(circle, Color(0, 255, 0, 50), true, Color::Green());
	theScreen.Draw(rect, Color(0, 0, 255, 150), true, Color(0, 0, 255, 50));
	theScreen.Draw(line, Color::Magenta());
	*/
	//theScreen.Draw(mTempSS, "5", Vec2D::Zero);

//	const BitmapFont& font = App::Singleton().GetFont();

//	AARectangle rect = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height() };
//	Vec2D textDrawPosition;
//	textDrawPosition = font.GetDrawPosition(GetSceneName(), rect, BFXA_CENTER, BFYA_CENTER);
//	theScreen.Draw(font, GetSceneName(), textDrawPosition, Color::Red());

	ButtonOptionsScene::Draw(theScreen);

}

const std::string& ArcadeScene::GetSceneName() const {
	static std::string sceneName = "Arcade";
	return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game) {
	Sound::QuitMixer();
	switch (game) {
		case TETRIS:
		{
			std::unique_ptr<Tetris> tetrisGame = std::make_unique<Tetris>();

			std::unique_ptr<GameScene> tetrisScene = std::make_unique<GameScene>(std::move(tetrisGame));
			return tetrisScene;
		}
		break;

		case BREAK_OUT:
		{
			std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();

			std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));

			return breakoutScene;
		}
		break;

		case ASTEROIDS:
		{

		}
		break;

		case PACMAN:
		{

		}
		break;

	}
	std::unique_ptr<Scene> notImplementedScene = std::make_unique<NotImplementedScene>();

	return notImplementedScene;
}