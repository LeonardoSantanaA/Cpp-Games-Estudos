#include "Asteroids.h"
#include "../../Input/GameController.h"
#include "../../App/App.h"

#include <iostream>

Asteroids::Asteroids(): mController(nullptr){
}

void Asteroids::Init(GameController& controller) {
	controller.ClearAll();
	
	mController = &controller;
	ResetGame();

}

void Asteroids::Update(uint32_t dt) {
	playerShip.Update(dt);
}

void Asteroids::Draw(Screen& screen) {
	playerShip.Draw(screen);
}

const std::string& Asteroids::GetName() const{
	static std::string name = "Asteroids";
	return name;
}

void Asteroids::ResetGame() {
	playerShip.Init(*mController);
	//playerShip.SetAngle(HALF_PI);
}