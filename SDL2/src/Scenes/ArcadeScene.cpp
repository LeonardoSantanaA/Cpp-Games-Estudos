#include "ArcadeScene.h"
#include <iostream>
#include "../Input/GameController.h"
#include "../App/App.h"


ArcadeScene::ArcadeScene() {

}

void ArcadeScene::Init() {
	mTempImage.LoadFile(App::Singleton().GetBasePath() + "Assets/ArcadeFont.bmp");

	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t dt, InputState state) {
		if (GameController::IsPressed(state)) {
			std::cout << "Action button was pressed!" << std::endl;
		}
		};

	mGameController.AddInputActionForKey(action);
	
	ButtonAction up;
	up.key = GameController::UpKey();
	up.action = [](uint32_t dt, InputState state) {
		if (GameController::IsPressed(state)) {
			std::cout << "Up button was pressed!" << std::endl;
		}
	};

	mGameController.AddInputActionForKey(up);
	
	MouseButtonAction mouseAction;
	mouseAction.mouseButton = GameController::LeftMouseButton();
	mouseAction.mouseInputAction = [](InputState state, const MousePosition& position) {
		if (GameController::IsPressed(state)) {
			std::cout << "Left Mouse button pressed!" << std::endl;
		}
	};
	mGameController.AddMouseButtonAction(mouseAction);

	mGameController.SetMouseMovedAction([](const MousePosition& mousePosition) {
		std::cout << "Mouse position x: " << mousePosition.xPos << ", y: " << mousePosition.yPos << std::endl;
	});

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
	theScreen.Draw(mTempImage, Vec2D::Zero);
}

const std::string& ArcadeScene::GetSceneName() const {
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game) {
	switch (game) {
		case TETRIS:
		{
			
		}
		break;

		case BREAK_OUT:
		{

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

		default:
		{

		}
		break;
	}
	return nullptr;
}