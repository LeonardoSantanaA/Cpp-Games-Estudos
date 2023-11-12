#include "ArcadeScene.h"


ArcadeScene::ArcadeScene() {

}

void ArcadeScene::Init() {

}
void ArcadeScene::Update(uint32_t dt) {

}

void ArcadeScene::Draw(Screen& theScreen) {
	Line2D line = { Vec2D(0, 50), Vec2D(theScreen.Width(), theScreen.Height()) };
	AARectangle rect = { Vec2D(theScreen.Width() / 2 - 25, theScreen.Height() / 2 - 25), 50, 50 };
	Triangle triangle = { Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110) };
	Circle circle = { Vec2D(float(theScreen.Width() / 2 + 50), float(theScreen.Height() / 2 + 50)), 50 };

	theScreen.Draw(triangle, Color::Red(), true, Color::Red());
	theScreen.Draw(circle, Color(0, 255, 0, 50), true, Color::Green());
	theScreen.Draw(rect, Color(0, 0, 255, 150), true, Color(0, 0, 255, 50));
	theScreen.Draw(line, Color::Magenta());
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