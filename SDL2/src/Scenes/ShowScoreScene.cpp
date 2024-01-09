#include "ShowScoreScene.h"
#include "../App/App.h"
#include "../Shapes/AARectangle.h"


void ShowScoreScene::Init() {
	scoreFile.LoadScoreFileLoader(App::GetBasePath() + "Assets/Scores.txt");

	ButtonAction backAction;
	backAction.key = GameController::CancelKey();
	backAction.action = [](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				App::Singleton().PopScene();
			}
		};
	mGameController.AddInputActionForKey(backAction);
 }

void ShowScoreScene::Update(uint32_t dt) {

}

void ShowScoreScene::Draw(Screen& theScreen) {
	const BitmapFont& font = App::Singleton().GetFont();
	Size fontSize = font.GetSizeOf("str");
	int yOffset = fontSize.height * 10;

	AARectangle rectTitle = { Vec2D(0, fontSize.height), App::Singleton().Width(), App::Singleton().Height() };
	std::string title = "Scores";
	Vec2D textDrawPositionScore;
	textDrawPositionScore = font.GetDrawPosition(title, rectTitle, BFXA_CENTER, BFYA_TOP);
	theScreen.Draw(font, title, textDrawPositionScore, Color::White());

	for(int i = 0; i < ScoreFileLoader::SCORES_TO_SHOW; ++i) {	
		AARectangle rect = { Vec2D(0, yOffset), App::Singleton().Width(), App::Singleton().Height() };

		std::string nameStr = ScoreFileLoader::GetScores(i).name;
		std::string spaceStr = " - ";
		std::string scoreStr = std::to_string(ScoreFileLoader::GetScores(i).score);
		std::string showScoreStr = nameStr + spaceStr + scoreStr;
		
		Vec2D textDrawPositionScore;
		textDrawPositionScore = font.GetDrawPosition(showScoreStr, rect, BFXA_CENTER, BFYA_TOP);
		if (ScoreFileLoader::GetScores(i).score > 0) {
			theScreen.Draw(font, showScoreStr, textDrawPositionScore, Color::White());
		}
		
		yOffset += 15;
	}
	
 }

const std::string& ShowScoreScene::GetSceneName() const{
	static std::string name = "Scores";
	return name;
}

