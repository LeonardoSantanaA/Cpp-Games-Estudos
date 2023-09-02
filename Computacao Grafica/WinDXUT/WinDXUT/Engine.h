#ifndef DXUT_ENGINE_H
#define DXUT_ENGINE_H

#include "App.h"
#include "Window.h"

class Engine {
private:
	static App* app;	//aplicacao a ser executada
	int Loop();	//laco principal do motor

public:
	static Window* window;
	static Input* input;

	Engine();
	~Engine();

	int Start(App* application);

	//trata eventos do windows
	static LRESULT CALLBACK EngineProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lParam);
};

#endif