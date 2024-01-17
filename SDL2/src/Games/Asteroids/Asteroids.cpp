#include "Asteroids.h"
#include "../../Input/GameController.h"
#include "../../App/App.h"

#include <iostream>

Asteroids::Asteroids(): mController(nullptr){
	mPlayerSpriteSheet.Load("AsteroidsSprites");
	mPlayerSprite.Init(App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt", mPlayerSpriteSheet);
	
	mBulletSprite.Init(App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt", mPlayerSpriteSheet);
	mBulletSprite.SetAnimation("missile", true);

	bullets.reserve(3);
}

void Asteroids::Init(GameController& controller) {
	controller.ClearAll();
	
	ButtonAction shootAction;
	shootAction.key = GameController::ActionKey();
	shootAction.action = [&](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				if (CanShoot()) {
					//sound here

				}
				else {

				}
			}

		};
	controller.AddInputActionForKey(shootAction);

	mController = &controller;
	ResetGame();

}

void Asteroids::Update(uint32_t dt) {
	playerShip.Update(dt);


	for (auto& bullet : bullets) {
		bullet.Update(dt);
	}

	for (auto i = bullets.begin(); i != bullets.end(); ) {
		auto& bullet = *i; // Evita chamadas repetitivas de i->GetPos()

		if (bullet.GetPos().GetX() < 0 || bullet.GetPos().GetX() > App::Singleton().Width() ||
			bullet.GetPos().GetY() < 0 || bullet.GetPos().GetY() > App::Singleton().Height()) {
			i = bullets.erase(i);
			std::cout << "bullet deleted." << std::endl;
		}
		else {
			//bullet.Update(dt);
			++i;
		}
	}
}

void Asteroids::Draw(Screen& screen) {
	playerShip.Draw(screen);

	for (auto& bullet : bullets) {
		bullet.Draw(screen);
	}
}

const std::string& Asteroids::GetName() const{
	static std::string name = "Asteroids";
	return name;
}

void Asteroids::ResetGame() {
	playerShip.Init(*mController, mPlayerSpriteSheet, mPlayerSprite);
}

bool Asteroids::CanShoot() {
	if (bullets.size() < 3) {
		Bullet bullet(playerShip.GetPosition() + mPlayerSprite.GetSize() / 2, playerShip.GetAngle());
		bullets.push_back(std::move(bullet));
		bullets.back().Init(mPlayerSpriteSheet, mBulletSprite);

		return true;
	}
	return false;
}