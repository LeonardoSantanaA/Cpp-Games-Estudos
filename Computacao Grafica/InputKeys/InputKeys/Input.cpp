#include "Input.h"

//inicializacao de membros estaticos da classe
bool Input::keys[256] = { 0 };
bool Input::ctrl[256] = { 0 };

Input::Input() {
	//supoe que a janela ja foi criada com uma chamada a window->Create();
	//altera a window procedura da janela ativa para InputProc
	SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)Input::InputProc);
}

Input::~Input() {
	//volta a usar a window procedura da classe window
	SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, (LONG_PTR)Window::WinProc);
}

bool Input::KeyPress(int vkcode) {
	if (ctrl[vkcode]) {
		if (KeyDown(vkcode)) {
			ctrl[vkcode] = false;
			return true;
		}
	}
	else if (KeyUp(vkcode)) {
		ctrl[vkcode] = true;
	}
	return false;
}

LRESULT CALLBACK Input::InputProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		//tecla pressionada
	case WM_KEYDOWN:
		keys[wParam] = true;
		return 0;
		//tecla liberada
	case WM_KEYUP:
		keys[wParam] = false;
		return 0;
	}

	return CallWindowProc(Window::WinProc, hWnd, msg, wParam, lParam);
}