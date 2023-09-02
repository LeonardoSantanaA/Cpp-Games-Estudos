#include "App.h"
#include "Engine.h"

//inicializacao de membros estaticos da classe
Window* App::window = nullptr;
Input* App::input = nullptr;

App::App() {
	if (!window) {	//se nao for nulo
		//assume que a instancia da engine é criada antes da instancia da aplicacao
		window = Engine::window;
		input == Engine::input;
	}
}

App::~App(){}

