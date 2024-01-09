#include "SelectNameScene.h"
#include "../App/App.h"
#include "../Shapes/AARectangle.h"
#include "../Input/InputAction.h"
#include "../Graphics/Screen.h"
#include "ArcadeScene.h"

SelectNameScene::~SelectNameScene() {
	SDL_StopTextInput();
}

void SelectNameScene::Init() {
	SDL_StartTextInput();
	

	ButtonAction confirmNameAction;
	confirmNameAction.key = GameController::ActionKey();
	confirmNameAction.action = [](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				App::Singleton().PopScene();
			}
		};
	mGameController.AddInputActionForKey(confirmNameAction);
}

void SelectNameScene::Update(uint32_t dt) {

}

void SelectNameScene::Draw(Screen& theScreen) {
	const BitmapFont& font = App::Singleton().GetFont();
	AARectangle rect = { Vec2D(0, ((App::Singleton().Height()/2) / 2)), App::Singleton().Width(), App::Singleton().Height() / 2};


	Vec2D textDrawPositionSelectName;
	textDrawPositionSelectName = font.GetDrawPosition( "Selecione seu nome", rect, BFXA_CENTER, BFYA_TOP);
	theScreen.Draw(font, "Selecione seu nome", textDrawPositionSelectName, Color::Red());


	Vec2D textDrawPositionName;
	textDrawPositionName = font.GetDrawPosition(InputController::GetName(), rect, BFXA_CENTER, BFYA_CENTER);
	theScreen.Draw(font, InputController::GetName(), textDrawPositionName, Color::Red());

	Size sizeDrawLineName;
	sizeDrawLineName = font.GetSizeOf(InputController::GetName());
	AARectangle rectLine = { Vec2D(0, sizeDrawLineName.height), App::Singleton().Width(), App::Singleton().Height() / 2 };
	Vec2D textDrawLineName;
	textDrawLineName = font.GetDrawPosition("___", rectLine, BFXA_CENTER, BFYA_BOTTOM);
	//theScreen.Draw(rectLine, Color::White());
	theScreen.Draw(font, "___", textDrawLineName, Color::White());


	Vec2D textDrawPositionSpaceToConfirm;
	textDrawPositionSpaceToConfirm = font.GetDrawPosition("Press space to confirm", rect, BFXA_CENTER, BFYA_BOTTOM);
	theScreen.Draw(font, "Press space to confirm", textDrawPositionSpaceToConfirm, Color::Red());

}

const std::string& SelectNameScene::GetSceneName() const {
	static std::string name = "Select your name!";
	return name;
}