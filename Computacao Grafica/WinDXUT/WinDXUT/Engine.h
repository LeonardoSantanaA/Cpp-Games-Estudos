#ifndef DXUT_ENGINE_H
#define DXUT_ENGINE_H

#include "App.h"
#include "Window.h"
#include "Timer.h"

class Engine {
private:
	static Timer timer;
	float FrameTime();	//calcula o tempo do quadro
	int Loop();	//laco principal do motor

public:
	static Window* window;
	static Input* input;
	static App* app;	//aplicacao a ser executada
	static float frameTime;

	Engine();
	~Engine();

	int Start(App* application);

	//trata eventos do windows
	static LRESULT CALLBACK EngineProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lParam);
};

#endif