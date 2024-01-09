#include "Tetris.h"
#include "../../App/App.h"
#include "../../Utils/Vec2D.h"
#include "../../Shapes/AARectangle.h"
#include "../../Shapes/Line2D.h"
#include <thread>
#include <future>
#include <cstdint>

TetrisGameStates Tetris::mState;
int Tetris::mScore = 0;

std::vector<Tetromino> Tetris::nextTetromino;

void Tetris::Init(GameController& controller) {
	controller.ClearAll();
	SetTetrisStates(TetrisGameStates::TET_INPLAY);
	playfield.Init();
	
	Tetromino tetromino;
	Collider::tetrominos.push_back(tetromino);

	GenerateNextTetromino();

	scoreFile.LoadScoreFileLoader(App::GetBasePath() + "Assets/Scores.txt");
	//Sound::SetVolumeMusic(60);
	int soundtrack = mSound.LoadMusic("TetrisSoundtrack.wav");
	mSound.PlayMusic(soundtrack);

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state) {
	
			if (GameController::IsPressed(state)) {
				Collider::tetrominos.back().SetMovementDirection(TetroDirection::TET_LEFT);
			}
			else {
				Collider::tetrominos.back().UnsetMovementDirection(TetroDirection::TET_LEFT);
			}
		
		};
	controller.AddInputActionForKey(leftKeyAction);
	
	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state) {
		
			if (GameController::IsPressed(state)) {
				Collider::tetrominos.back().SetMovementDirection(TetroDirection::TET_RIGHT);
			}
			else {
				Collider::tetrominos.back().UnsetMovementDirection(TetroDirection::TET_RIGHT);
			}
		
		};
	controller.AddInputActionForKey(rightKeyAction);

	ButtonAction downKeyAction;
	downKeyAction.key = GameController::DownKey();
	downKeyAction.action = [this](uint32_t dt, InputState state) {

		if (GameController::IsPressed(state)) {
			Collider::tetrominos.back().SetMovementDirection(TetroDirection::TET_DOWN);
		}
		else {
			Collider::tetrominos.back().UnsetMovementDirection(TetroDirection::TET_DOWN);
		}

		};
	controller.AddInputActionForKey(downKeyAction);

	ButtonAction rotateKeyAction;
	rotateKeyAction.key = GameController::ActionKey();
	rotateKeyAction.action = [this](uint32_t dt, InputState state) {
		if (GetTetrisStates() == TetrisGameStates::TET_INPLAY) {
			if (GameController::IsPressed(state)) {
				Collider::tetrominos.back().Rotate();
			}
		}
		else {
			RestartGame();
		}
		

		};
	controller.AddInputActionForKey(rotateKeyAction);
	
	ButtonAction backAction;
	backAction.key = GameController::CancelKey();
	backAction.action = [this](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				Collider::tetrominos.clear();
				scoreFile.SaveScoreToFile(App::GetBasePath() + "Assets/Scores.txt", InputController::GetName().c_str(), GetScore());
				App::Singleton().PopScene();
			}
		};
	controller.AddInputActionForKey(backAction);
}

constexpr int UPDATE_DELAY = 700;

void Tetris::Update(uint32_t dt) {
	if (GetTetrisStates() == TetrisGameStates::TET_INPLAY) {
		for (auto& tet : Collider::tetrominos) {
			tet.Update(dt);
		}

		for (auto& next : nextTetromino) {
			next.Update(dt);
		}

		if (Collider::tetrominos.back().GetStats() == TetroStats::TET_STATIC) {
			Tetris::GenerateTetromino();
		}
		ghost.Update(dt);

		countDelay += dt;

		if (countDelay >= UPDATE_DELAY) {
			threadVerifyScore = std::thread(Collider::VerifyScore, Collider::tetrominos, std::ref(mMutex));
			threadVerifyScore.join();
			countDelay = 0;
		}
	}
	else {
		//GAMEOVER
	}

}

void Tetris::Draw(Screen& screen) {
	playfield.Draw(screen);
	ghost.Draw(screen);
	for (auto& tet : Collider::tetrominos) {
		tet.Draw(screen);
	}
	for (auto& next : nextTetromino) {
		next.Draw(screen);
	}

	const BitmapFont& font = App::Singleton().GetFont();

	AARectangle rect = { Vec2D(Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2), 
		Playfield::GetGridPosition(0, 12).GetTopLeftPoint().GetY()),
		static_cast<unsigned int>(Playfield::GRID_BLOCK_SIZE) * 5, static_cast<unsigned int>(Playfield::GRID_BLOCK_SIZE) * 4 };

	Vec2D textDrawPosition;
	textDrawPosition = font.GetDrawPosition(std::to_string(Tetris::GetScore()), rect, BFXA_CENTER, BFYA_CENTER);
	screen.Draw(font, std::to_string(Tetris::GetScore()), textDrawPosition, Color(102, 113, 215, 255));

	if (Collider::IsTetris()) {
		if (mCountTetris <= 50) {
			AARectangle rectTetris = { Vec2D(Playfield::GetGridPosition(BLOCKS_WIDTH - 1, 0).GetTopLeftPoint().GetX() + (Playfield::GRID_BLOCK_SIZE * 2),
				Playfield::GetGridPosition(0, 8).GetTopLeftPoint().GetY()),
				static_cast<unsigned int>(Playfield::GRID_BLOCK_SIZE) * 5, static_cast<unsigned int>(Playfield::GRID_BLOCK_SIZE) * 4 };

			Vec2D textDrawPositionTetris;
			textDrawPositionTetris = font.GetDrawPosition("TETRIS!", rectTetris, BFXA_CENTER, BFYA_CENTER);
			screen.Draw(font, "TETRIS!", textDrawPositionTetris, Color(255, 4, 255, 255));
			mCountTetris++;
		}
		else {
			Collider::DesableTetris();
			mCountTetris = 0;
		}
	}

	if (GetTetrisStates() == TetrisGameStates::TET_GAMEOVER) {
		AARectangle rectBackground = { Vec2D(App::Singleton().Width() / 2 - 50, App::Singleton().Height()/2 - 100), App::Singleton().Width()/2, App::Singleton().Height()/2 - 60};
		Vec2D textDrawPositionBk;
		textDrawPositionBk = font.GetDrawPosition("GAME OVER!", rectBackground, BFXA_CENTER, BFYA_CENTER);
		screen.Draw(font, "GAME OVER!", textDrawPositionBk, Color(180, 13, 45, 255));
		Vec2D textDrawPositionPressSpace;
		textDrawPositionPressSpace = font.GetDrawPosition("Press Space to Continue", rectBackground, BFXA_CENTER, BFYA_BOTTOM);
		screen.Draw(font, "Press Space to Continue", textDrawPositionPressSpace, Color(255, 40, 83, 255));
	}

}

const std::string& Tetris::GetName() const {
	static std::string name = "Tetris";
	return name;
}

void Tetris::GenerateTetromino() {
	nextTetromino.back().PrepareToPlay();
	Collider::tetrominos.push_back(nextTetromino.back());
	GenerateNextTetromino();
}

void Tetris::GenerateNextTetromino() {
	Tetromino tetromino;

	//tetromino.SetState(TetroStats::TET_NEXT);
	nextTetromino.clear();
	nextTetromino.push_back(tetromino);
	nextTetromino.back().SetState(TetroStats::TET_NEXT);

}

void Tetris::RestartGame() {
	scoreFile.SaveScoreToFile(App::GetBasePath() + "Assets/Scores.txt", InputController::GetName().c_str(), GetScore());
	for (auto& tetromino : Collider::tetrominos) {
		tetromino.GetRectangles().clear();
	}

	mScore = 0;
	Collider::tetrominos.clear();
	GenerateTetromino();
	SetTetrisStates(TetrisGameStates::TET_INPLAY);
	mSound.TogglePlay();
}