#include <iostream>
#include "ArcadeScene.h"
#include "../Input/GameController.h"
#include "../App/App.h"
#include "GameScene.h"
#include "NotImplementedScene.h"
#include "SelectNameScene.h"
#include "ShowScoreScene.h"
#include "../Games/BreakOut/BreakOut.h"
#include "../Games/Tetris/Tetris.h"

ArcadeScene::ArcadeScene():
	ButtonOptionsScene({ "Select Name", "Tetris", "Break Out!", "Asteroids", "Pac-man", "Show Scores"}, Color::Cyan())
{
}

void ArcadeScene::Init() {
	
	std::vector<Button::ButtonAction> actions;

	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(SELECT_NAME));
		});

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

	actions.push_back([this] {
		App::Singleton().PushScene(GetScene(SHOW_SCORES));
		});

	SetButtonActions(actions);

	ButtonOptionsScene::Init();

	//temp
	{
		mSpriteSheet.Load("PacmanSprites");
		mSprite.Init(App::Singleton().GetBasePath() + "Assets/Pacman_animations.txt", mSpriteSheet);

		mSprite.SetAnimation("death", true);
		mSprite.SetRotate(true);
	}

}
void ArcadeScene::Update(uint32_t dt) {
	mSprite.Update(dt);

	angle -= 0.1;
	mSprite.SetAngle(angle);

	if (InputController::GetName().size() < 1) {
		cantPlay = true;
	}
	else {
		cantPlay = false;
	}
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

	mSprite.Draw(theScreen);

	ButtonOptionsScene::Draw(theScreen);
	
	if (cantPlay) {
		const BitmapFont& font = App::Singleton().GetFont();

		Size sizeDrawCantPlay;
		sizeDrawCantPlay = font.GetSizeOf("Type your name first!");
		AARectangle rectCantPlay = { Vec2D(0, sizeDrawCantPlay.height), App::Singleton().Width(), App::Singleton().Height() / 2 };
		Vec2D textDrawCantPlay;
		textDrawCantPlay = font.GetDrawPosition("Type your name first!", rectCantPlay, BFXA_CENTER, BFYA_TOP);
		//theScreen.Draw(rectLine, Color::White());
		theScreen.Draw(font, "Type your name first!", textDrawCantPlay, Color::Red());

	}
	if (InputController::GetName().size() >= 1) {
		const BitmapFont& font = App::Singleton().GetFont();

		AARectangle rect = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()};
		Vec2D textDrawName = font.GetDrawPosition("Player: " + InputController::GetName(), rect, BFXA_LEFT, BFYA_BOTTOM);
		theScreen.Draw(font, "Player: " + InputController::GetName(), textDrawName, Color::Red());
	}
	

}



const std::string& ArcadeScene::GetSceneName() const {
	static std::string sceneName = "Arcade";
	return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game) {
	Sound::QuitMixer();

	switch (game) {
		case SELECT_NAME:
		{
			std::unique_ptr<Scene> selectNameScene = std::make_unique<SelectNameScene>();

			InputController::ClearName();
			return selectNameScene;
		}
		break;

		case TETRIS:
		{
			if (!cantPlay) {
				std::unique_ptr<Tetris> tetrisGame = std::make_unique<Tetris>();

				std::unique_ptr<GameScene> tetrisScene = std::make_unique<GameScene>(std::move(tetrisGame));
				return tetrisScene;
			}
			else {
				return 0;
			}
			
		}
		break;

		case BREAK_OUT:
		{
			if (!cantPlay) {
				std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();

				std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));

				return breakoutScene;
			}
			else {
				return 0;
			}
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

		case SHOW_SCORES:
		{
			std::unique_ptr<Scene> showScoresScene = std::make_unique<ShowScoreScene>();

			return showScoresScene;
		}
		break;

	}
	std::unique_ptr<Scene> notImplementedScene = std::make_unique<NotImplementedScene>();

	return notImplementedScene;
}