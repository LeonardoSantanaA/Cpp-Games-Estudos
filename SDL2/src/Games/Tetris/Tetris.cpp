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
}

void Tetris::Update(uint32_t dt) {

}

void Tetris::Draw(Screen& screen) {
	playfield.Draw(screen);
}

const std::string& Tetris::GetName() const {
	static std::string name = "Tetris";
	return name;
}