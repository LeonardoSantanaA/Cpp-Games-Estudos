#ifndef DXUT_INPUT_H
#define DXUT_INPUT_H

#include "Window.h"
#include <string>
using std::string;

class Input {
private:
	static bool keys[256];	//estado das teclas do teclado/mouse
	static bool ctrl[256];	//controle da liberašao das teclas
	static string text;

public:
	Input();
	~Input();

	bool KeyDown(int vkcode);
	bool KeyUp(int vkcode);
	bool KeyPress(int vkcode);

	void Read();	//armazena texto digitado ate o proximo ENTER ou TAB
	static const char* Text();	//retorna endereco do texto armazenado

	//trata eventos do windows
	static LRESULT CALLBACK Reader(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lParam);
	static LRESULT CALLBACK InputProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

inline bool Input::KeyDown(int vkcode) {
	return keys[vkcode];
}

inline bool Input::KeyUp(int vkcode) {
	return !(keys[vkcode]);
}

inline const char* Input::Text() {
	return text.c_str();
}

#endif