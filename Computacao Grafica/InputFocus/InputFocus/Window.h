#ifndef DXUT_WINDOW_H
#define DXUT_WINDOW_H

#include "Types.h"
#include <windows.h> //inclui funcoes do windows
#include <windowsx.h> //inclui extensoes do windows
#include <string>

using std::string;

enum WindowModes { FULLSCREEN, WINDOWED };

class Window {
private:
	HWND windowId; //identificador da janela
	int windowWidth; //largura da janela
	int windowHeight; //altura da janela
	HICON windowIcon; //icone da janela
	HCURSOR windowCursor; //cursor da janela
	COLORREF windowColor; //cor de fundo da janela
	string windowTitle; //nome da barra de titulo
	DWORD windowStyle; //estilo da janela
	int windowMode;	//modo tela cheia, em janela ou sem borda
	int windowPosX; //posicao inicial da janela no eixo x
	int windowPosY; //posicao inicial da janela no eixo y
	int windowCenterX; //centro da janela no eixo x
	int windowCenterY; //centro da janela no eixo y

	static void (*inFocus)();
	static void (*lostFocus)();

public:
	Window();	//construtor

	HWND Id() const;	//retorna o identificador da janela
	int Width() const; //retorna a largura atual da janela
	int Height() const; //retorna a altura atual da janela
	int Mode() const; //retorna o modo atual da janela (Fullscreen/Windowed)
	int CenterX() const; //retorna o centro da janela no eixo x
	int CenterY() const; //retorna o centro da janela no eixo y
	string Title() const; //retorna o titulo da janela
	COLORREF Color() const; //retorna a cor de fundo da janela

	void Icon(const uint icon); //define o icone da janela
	void Cursor(const uint cursor); //define o cursor da janela
	void Title(const string title); //define o titulo da janela
	void Size(int width, int height); //define o tamanho da janela
	void Mode(int mode); //define o modo da janela
	void Color(int r, int g, int b); //define a cor de fundo da janela

	void HideCursor(bool hide); //habilita ou desabilita a exibicao do cursor
	void Print(string text, int x, int y, COLORREF color); //mostra texto na janela
	void Clear(); //limpa a tela
	void Close(); //fecha a janela e sai
	bool Create(); //cria a janela com os valores dos atributos

	void InFocus(void(*func)()); //chama uma funcao ao ganhar foco
	void LostFocus(void(*func)()); //chama uma funcao ao perder foco

	//tratamento de eventos do windows
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

//funcoes inline

inline HWND Window::Id() const {
	return windowId;
}

inline int Window::Width() const {
	return windowWidth;
}

inline int Window::Height() const {
	return windowHeight;
}

inline int Window::Mode() const {
	return windowMode;
}

inline int Window::CenterX() const {
	return windowCenterX;
}

inline int Window::CenterY() const {
	return windowCenterY;
}

inline string Window::Title() const {
	return windowTitle;
}

inline COLORREF Window::Color() const {
	return windowColor;
}

inline void Window::Icon(const uint icon) {
	windowIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(icon));
}

inline void Window::Cursor(const uint cursor) {
	windowCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(cursor));
}

inline void Window::Title(const string title) {
	windowTitle = title;
}

inline void Window::Color(int r, int g, int b) {
	windowColor = RGB(r, g, b);
}

inline void Window::HideCursor(bool hide) {
	ShowCursor(!hide);
}

inline void Window::Close() {
	PostMessage(windowId, WM_DESTROY, 0, 0); //mando a mensagem WM_DESTROY pra minha janela
}

inline void Window::InFocus(void(*func)()) {
	inFocus = func;
}

inline void Window::LostFocus(void(*func)()) {
	lostFocus = func;
}

#endif