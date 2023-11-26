#include "Tetris.h"
#include "../../App/App.h"
#include "../../Utils/Vec2D.h"

/*
	Fazer uma grid pro jogo com 10 blocos de largura e 20 de altura;
	Playfield:
	matriz de blocos, com cor preta e borda branca, serve para desenhar e detectar colisao se necessario futuramente
	essa classe tambem sera responsavel de verificar se alguma linha ficou completa para destruir e dar score

	
*/

void Tetris::Init(GameController& controller) {
	playfield.Init();
	Tetromino tetromino;
	tetromino.Init();
	tetrominos.push_back(tetromino);

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state) {
	
			if (GameController::IsPressed(state)) {
				tetrominos.back().SetMovementDirection(TetroDirection::TET_LEFT);
			}
			else {
				tetrominos.back().UnsetMovementDirection(TetroDirection::TET_LEFT);
			}
		
		};
	controller.AddInputActionForKey(leftKeyAction);
	
	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state) {
		
			if (GameController::IsPressed(state)) {
				tetrominos.back().SetMovementDirection(TetroDirection::TET_RIGHT);
			}
			else {
				tetrominos.back().UnsetMovementDirection(TetroDirection::TET_RIGHT);
			}
		
		};
	controller.AddInputActionForKey(rightKeyAction);
	
}

void Tetris::Update(uint32_t dt) {
	for (auto& tet : tetrominos) {
		tet.Update(dt);
	}
}

void Tetris::Draw(Screen& screen) {
	playfield.Draw(screen);
	for (auto& tet : tetrominos) {
		tet.Draw(screen);
	}
}

const std::string& Tetris::GetName() const {
	static std::string name = "Tetris";
	return name;
}