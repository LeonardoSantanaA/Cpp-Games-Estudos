#include "Asteroids.h"
#include "../../Input/GameController.h"
#include "../../App/App.h"
#include "../../Shapes/AARectangle.h"

#include <iostream>

Asteroids::Asteroids(): mController(nullptr){
	mPlayerSpriteSheet.Load("AsteroidsSprites");
	mPlayerSprite.Init(App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt", mPlayerSpriteSheet);
	
	mBulletSprite.Init(App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt", mPlayerSpriteSheet);
	mBulletSprite.SetAnimation("missile", true);

	mExplosionSprite.Init(App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt", mPlayerSpriteSheet);
	mExplosionSprite.SetAnimation("explosion", false);

	bullets.reserve(3);


	GenerateComets();

	
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
	

	if (comets.empty())
	{
		GenerateComets();
	}

	for (auto i = comets.begin(); i != comets.end(); ) {
		auto& comet = *i;

		if (comet.GetPos().GetX() < -100 || comet.GetPos().GetX() > App::Singleton().Width() + 100 ||
			comet.GetPos().GetY() < -100 || comet.GetPos().GetY() > App::Singleton().Height() + 100) {
			i = comets.erase(i);
			std::cout << "comet deleted." << std::endl;
		}
		else {
			comet.Update(dt);
			++i;
		}
	}


	for (auto i = bullets.begin(); i != bullets.end(); ) {
		auto& bullet = *i;

		if (bullet.GetPos().GetX() < 0 || bullet.GetPos().GetX() > App::Singleton().Width() ||
			bullet.GetPos().GetY() < 0 || bullet.GetPos().GetY() > App::Singleton().Height()) {
			i = bullets.erase(i);

		}
		else {
			bullet.Update(dt);
			++i;
		}
	}

	VerifyCollisions();
}

void Asteroids::Draw(Screen& screen) {
	playerShip.Draw(screen);

	for (auto& bullet : bullets) {
		bullet.Draw(screen);
		screen.Draw(bullet.GetBoundingBox(), Color::White());
	}

	//draw comets, explosion and erase comets
	for (auto i = comets.begin(); i != comets.end(); ) {
		auto& comet = *i;

		if (comet.CanExplode()) {
			AnimatedSprite explosionSprite;
			explosionSprite.Init(App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt", mPlayerSpriteSheet);
			explosionSprite.SetAnimation("explosion", false);
			explosionSprite.SetPosition(Vec2D(comet.GetPos() - (comet.GetSpriteSize() / 2)));
			explosionSprite.Draw(screen);
			std::cout << "draw explosion." << std::endl;
			i = comets.erase(i);
		}
		else {
			comet.Draw(screen);
			screen.Draw(comet.GetBoundingBox(), Color::Red());
			++i;
		}
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

void Asteroids::GenerateComets() {
	for (int i = 0; i < 3; ++i) {
		Comet comet;
		comets.push_back(comet);
		comets.back().Init(mPlayerSpriteSheet, "AsteroidsSprites");
	}
}

void Asteroids::VerifyCollisions() {
	for (auto i = bullets.begin(); i != bullets.end(); ) {
		auto& bullet = *i;
		for (auto c = comets.begin(); c != comets.end();) {
			auto& comet = *c;

			if (bullet.GetBoundingBox().Intersects(comet.GetBoundingBox())) {

				if (comet.GetSize() == COMET_SIZE::LARGE_ROCK) {
					std::cout << "dividir em pedaco um pouco menor." << std::endl;
					c = comets.erase(c);
				}
				else if (comet.GetSize() == COMET_SIZE::MEDIUM_ROCK) {
					std::cout << "dividir em pedaco pequenininho" << std::endl;
					c = comets.erase(c);
				}
				else {
					comet.SetExplode(true);
					++c;
				}
				
				
				
				bullet.SetToDestroy(true);
			}
			else {
				++c;
			}	
		}
		++i;
	}

	//erase bullet that collided
	for (auto i = bullets.begin(); i != bullets.end(); ) {
		auto& bullet = *i;

		if (bullet.CanDestroy()) {
			i = bullets.erase(i);
		}
		else {
			++i;
		}
	}
}