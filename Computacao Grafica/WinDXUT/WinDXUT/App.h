#ifndef DXUT_APP_H
#define DXUT_APP_H

#include "Window.h"
#include "Input.h"

class App {
protected:
	static Window* window;
	static Input* input;

public:
	App();
	virtual ~App();

	//metodos puramente virtuais, devem ser implementados em todas as classes derivadas de App
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Finalize() = 0;

	//os metodos a seguir possuem uma implementacao vazia por padrao,
	// e apenas um deles deve ser sobrescrito na classe derivada:
	// Draw() e executado a cada ciclo do laco principal
	// Display() e chamado apenas uma vez no inicio da aplicacao
	// e deve ser chamado manualmente em Update toda vez
	// que a tela precisar ser redesenhada
	virtual void Draw() {};
	virtual void Display() {};


};

#endif