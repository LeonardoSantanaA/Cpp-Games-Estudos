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

void Tetris::Init(GameController& controller) {
	controller.ClearAll();
	SetTetrisStates(TetrisGameStates::TET_INPLAY);
	playfield.Init();
	GenerateTetromino();
	scoreFile.LoadScoreFileLoader(App::GetBasePath() + "Assets/Scores.txt");

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
	
}

constexpr int UPDATE_DELAY = 700;

void Tetris::Update(uint32_t dt) {
	if (GetTetrisStates() == TetrisGameStates::TET_INPLAY) {
		for (auto& tet : Collider::tetrominos) {
			tet.Update(dt);
		}
		if (Collider::tetrominos.back().GetStats() == TetroStats::TET_STATIC) {
			Tetris::GenerateTetromino();
		}

		countDelay += dt;

		if (countDelay >= UPDATE_DELAY) {
			threadVerifyScore = std::thread(Collider::VerifyScore, Collider::tetrominos, std::ref(mMutex));
			threadVerifyScore.join();
			countDelay = 0;
		}
	}
	else {

	}

}

void Tetris::Draw(Screen& screen) {
	playfield.Draw(screen);
	for (auto& tet : Collider::tetrominos) {
		tet.Draw(screen);
	}

}

const std::string& Tetris::GetName() const {
	static std::string name = "Tetris";
	return name;
}

void Tetris::GenerateTetromino() {
	Tetromino tetromino;
	//tetromino.Init();
	Collider::tetrominos.push_back(tetromino);
}

void Tetris::RestartGame() {
	scoreFile.SaveScoreToFile(App::GetBasePath() + "Assets/Scores.txt", "ABC", GetScore());
	for (auto& tetromino : Collider::tetrominos) {
		tetromino.GetRectangles().clear();
	}

	mScore = 0;
	Collider::tetrominos.clear();
	GenerateTetromino();
	SetTetrisStates(TetrisGameStates::TET_INPLAY);
}