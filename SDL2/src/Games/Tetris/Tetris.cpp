#include "Tetris.h"
#include "../../App/App.h"
#include "../../Utils/Vec2D.h"
#include "../../Shapes/AARectangle.h"
#include "../../Shapes/Line2D.h"


/*
	Fazer uma grid pro jogo com 10 blocos de largura e 20 de altura;
	Playfield:
	matriz de blocos, com cor preta e borda branca, serve para desenhar e detectar colisao se necessario futuramente
	essa classe tambem sera responsavel de verificar se alguma linha ficou completa para destruir e dar score

	
*/

void Tetris::Init(GameController& controller) {
	playfield.Init();
	GenerateTetromino();

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

		if (GameController::IsPressed(state)) {
			Collider::tetrominos.back().Rotate();
		}

		};
	controller.AddInputActionForKey(rotateKeyAction);
	
}

void Tetris::Update(uint32_t dt) {
	for (auto& tet : Collider::tetrominos) {
		tet.Update(dt);
	}

	if (Collider::tetrominos.back().GetStats() == TetroStats::TET_STATIC) {
		GenerateTetromino();
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
	tetromino.Init();
	Collider::tetrominos.push_back(tetromino);
}
