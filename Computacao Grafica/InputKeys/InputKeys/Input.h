#ifndef DXUT_INPUT_H
#define DXUT_INPUT_H

#include "Window.h"

class Input {
private:
	static bool keys[256];	//estado das teclas do teclado/mouse
	static bool ctrl[256];	//controle da liberaçao das teclas

public:
	Input();
	~Input();

	bool KeyDown(int vkcode);
	bool KeyUp(int vkcode);
	bool KeyPress(int vkcode);

	static LRESULT CALLBACK InputProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

inline bool Input::KeyDown(int vkcode) {
	return keys[vkcode];
}

inline bool Input::KeyUp(int vkcode) {
	return !(keys[vkcode]);
}

#endif