#include "Engine.h"
#include <windows.h>
#include <sstream>

using std::stringstream;

//inicializacao de variaveis estaticas da classe
Window* Engine::window = nullptr;	//janela da aplicacao
Input* Engine::input = nullptr;	//dispositivos de entrada
App* Engine::app = nullptr;	//apontador da aplicacao

Engine::Engine() {
	window = new Window();
}

Engine::~Engine() {
	delete app;
	delete input;
	delete window;
}

int Engine::Start(App* application) {
	app = application;

	//cria a janela
	window->Create();

	//Atencao: a entrada deve ser instanciada apos a criacao da jenala
	input = new Input();

	//altera a window procedura da janela ativa para a engineproc
	SetWindowLongPtr(window->Id(), GWLP_WNDPROC, (LONG_PTR)EngineProc);

	//retorna resultado da aplicacao
	return Loop();
}

int Engine::Loop() {
	//mensagens do windows
	MSG msg = { 0 };

	//inicializacao da aplicacao
	app->Init();

	//laco principal
	do {
		//trata dos eventos antes de atualizar a aplicacao
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//atualizacao da aplicacao
			app->Update();

			//desenho da aplicacao
			app->Draw();

			//aguarda 16 milissegundos ou a proxima interacao com a janela
			MsgWaitForMultipleObjects(0, NULL, FALSE, 10, QS_ALLINPUT);
		}
	} while (msg.message != WM_QUIT);

	//finalizacao da aplicacao
	app->Finalize();

	//encera a aplicacao
	return int(msg.wParam);
}

LRESULT CALLBACK Engine::EngineProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//janela precisa ser repintada
	if (msg == WM_PAINT)
		app->Display();

	return CallWindowProc(Input::InputProc, hWnd, msg, wParam, lParam);
}