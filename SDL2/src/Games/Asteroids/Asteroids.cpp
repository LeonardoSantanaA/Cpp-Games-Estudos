#include "Asteroids.h"
#include "../../Input/GameController.h"
#include "../../App/App.h"
#include "../../Shapes/AARectangle.h"

#include <random>
#include <iostream>
#include <chrono>

Asteroids::Asteroids(): mController(nullptr), countDownStay(0), mScore(0), invertSeconds(0){
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
	
	scoreFile.LoadScoreFileLoader(App::GetBasePath() + "Assets/Scores.txt");

	ButtonAction backAction;
	backAction.key = GameController::CancelKey();
	backAction.action = [&](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				scoreFile.SaveScoreToFile(App::GetBasePath() + "Assets/Scores.txt", InputController::GetName().c_str(), mScore);
				App::Singleton().PopScene();
			}
		};
	controller.AddInputActionForKey(backAction);

	ButtonAction shootAction;
	shootAction.key = GameController::ActionKey();
	shootAction.action = [&](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				if (GetGameStatus() == AST_PLAY) {
					if (CanShoot()) {
						//sound here

					}
				}
				else if (GetGameStatus() == AST_GAMEOVER) {
					for (auto& comet : comets) {
						comet.SetExplode(true);
					}
					bullets.clear();
					SetGameStatus(AST_WAIT);
					playerShip.FullLife();
					scoreFile.SaveScoreToFile(App::GetBasePath() + "Assets/Scores.txt", InputController::GetName().c_str(), mScore);

					mScore = 0;
				}
				
			}

		};
	controller.AddInputActionForKey(shootAction);

	mController = &controller;
	InitGame();

}

void Asteroids::Update(uint32_t dt) {
	playerShip.Update(dt);
	VerifyCollisions();

	for (auto& explosion : explosions) {
		explosion.Update(dt);
	}

	for (auto i = explosions.begin(); i != explosions.end(); ) {
		auto& explosion = *i;

		if (explosion.IsFinishedPlayingAnimation()) {
			i = explosions.erase(i);
		}
		else if (!explosion.GetAnimation().IsPlaying()) {
			std::cout << "cleaning animations." << std::endl;
			i = explosions.erase(i);
		}
		else {
			i++;
		}

	}

	if (GetGameStatus() == AST_PLAY) {

		if (comets.size() < 2)
		{
			GenerateComets();
		}

		for (auto i = comets.begin(); i != comets.end(); ) {
			auto& comet = *i;

			if (comet.GetPos().GetX() < -100 || comet.GetPos().GetX() > App::Singleton().Width() + 100 ||
				comet.GetPos().GetY() < -100 || comet.GetPos().GetY() > App::Singleton().Height() + 100) {
				i = comets.erase(i);
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

		if (playerShip.isDamaged() && playerShip.GetLife() > 0) {
			ResetGame();
		}
		if (playerShip.GetLife() < 0) {
			SetGameStatus(AST_GAMEOVER);
		}
	}
	else if (GetGameStatus() == AST_WAIT) {

	}
	else if (GetGameStatus() == AST_GAMEOVER) {

	}
	

}

void Asteroids::Draw(Screen& screen) {
	playerShip.Draw(screen);
	//screen.Draw(playerShip.GetBoundingBox(), Color::Pink());

	for (auto& bullet : bullets) {
		bullet.Draw(screen);
		//screen.Draw(bullet.GetBoundingBox(), Color::White());
	}

	//draw comets, explosion and erase comets
	for (auto& comet : comets) {
		//for (auto i = comets.begin(); i != comets.end(); ) {
			//auto& comet = *i;

		if (comet.CanExplode()) {
			AnimatedSprite explosionSprite;
			explosions.push_back(explosionSprite);
			explosions.back().Init(App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt", mPlayerSpriteSheet);
			explosions.back().SetAnimation("explosion", false);
			explosions.back().SetPosition(Vec2D(comet.GetPos() - (comet.GetSpriteSize() / 2)));

			//explosionSprite.Draw(screen);
			//i = comets.erase(i);
			comet.SetDestroy(true);
		}
		else {
			comet.Draw(screen);
			//screen.Draw(comet.GetBoundingBox(), Color::Red());
			//++i;
		}
	}

	for (auto& explosion : explosions) {
		explosion.Draw(screen);
	}

	if (GetGameStatus() == AST_WAIT) {
		if (countDownStay < 2) {
			countDownStay++;
			start_time = std::chrono::high_resolution_clock::now();
		}
		else {
			if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count() < 3) {
				int seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count();

				const BitmapFont& font = App::Singleton().GetFont();


				AARectangle rect (Vec2D::Zero, App::Singleton().Width(),
					App::Singleton().Height() - 50);


				if (seconds == 0) {
					invertSeconds = 3;
				}
				else if (seconds == 1) {
					invertSeconds = 1;
				}
				else if (seconds == 2) {
					invertSeconds = -1;
				}

				Vec2D textDrawPosition;
				textDrawPosition = font.GetDrawPosition(std::to_string(seconds + invertSeconds), 
					rect, BFXA_CENTER, BFYA_CENTER);
				screen.Draw(font, std::to_string(seconds + invertSeconds), textDrawPosition, Color::White());

			}
			else {
				SetGameStatus(AST_PLAY);
				countDownStay = 0;
				invertSeconds = 3;
			}

			
		}
	}
	else if (GetGameStatus() == AST_PLAY) {
		const BitmapFont& font = App::Singleton().GetFont();

		AARectangle rect(Vec2D::Zero, App::Singleton().Width(),
			App::Singleton().Height());

		Vec2D textDrawPosition;
		textDrawPosition = font.GetDrawPosition(std::to_string(mScore),
			rect, BFXA_CENTER, BFYA_TOP);
		screen.Draw(font, std::to_string(mScore), textDrawPosition, Color::White());


	}
	else if (GetGameStatus() == AST_GAMEOVER) {
		const BitmapFont& font = App::Singleton().GetFont();

		AARectangle rectGameOver(Vec2D::Zero, App::Singleton().Width(),
			App::Singleton().Height() - 80);
		AARectangle rectPressSpace(Vec2D::Zero, App::Singleton().Width(),
			App::Singleton().Height() - 50);

		Vec2D gameOverDrawPosition;
		gameOverDrawPosition = font.GetDrawPosition("Gameover!",
			rectGameOver, BFXA_CENTER, BFYA_CENTER);
		screen.Draw(font, "Gameover!", gameOverDrawPosition, Color::White());

		Vec2D pressSpaceDrawPosition;
		pressSpaceDrawPosition = font.GetDrawPosition("Press space to continue",
			rectPressSpace, BFXA_CENTER, BFYA_CENTER);
		screen.Draw(font, "Press space to continue", pressSpaceDrawPosition, Color::White());
	}
}

const std::string& Asteroids::GetName() const{
	static std::string name = "Asteroids";
	return name;
}

void Asteroids::InitGame() {
	playerShip.Init(*mController, mPlayerSpriteSheet, mPlayerSprite);

	SetGameStatus(AST_WAIT);
}

void Asteroids::ResetGame() {
	playerShip.Reset();
	bullets.clear();
	for (auto& comet : comets) {
		comet.SetExplode(true);
	}
	SetGameStatus(AST_WAIT);
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
	for (auto& comet : comets) {

		if (playerShip.GetBoundingBox().Intersects(comet.GetBoundingBox()) && playerShip.CanReduceLife() && !comet.CanExplode()) {
			playerShip.SetDamaged(true);
			comet.SetExplode(true);
		}
	}

	for(auto& bullet : bullets){
	//for (auto i = bullets.begin(); i != bullets.end(); ) {
		//auto& bullet = *i;
		std::vector<Comet> newComets;

		for(auto& comet : comets){
			
		//	if (playerShip.GetBoundingBox().Intersects(comet.GetBoundingBox())) {
				
				//std::cout << "colidiu" << std::endl;
				//comet.SetExplode(true);
		//	}

			if (bullet.GetBoundingBox().Intersects(comet.GetBoundingBox())) {

				if (comet.GetSize() == COMET_SIZE::LARGE_ROCK) {
					for (int j = 0; j < 2; ++j) {
						Comet newComet;
						//comets.push_back(newComet);
						newComet.Init(mPlayerSpriteSheet, "AsteroidsSprites");
						newComet.SetSize(COMET_SIZE::MEDIUM_ROCK);

						newComet.SetPos(comet.GetPos());
						newComet.SetVelocity(comet.GetVelocity() - 0.2);

						std::random_device rd;
						std::mt19937 gen(rd());
						std::uniform_real_distribution<> randomAngle(-20, 20);
						float newAngle =  comet.GetAngle()  + randomAngle(gen);
						newComet.SetAngle(newAngle);
						newComets.push_back(newComet);
					}
					mScore += 10;
					comet.SetExplode(true);
				}
				else if (comet.GetSize() == COMET_SIZE::MEDIUM_ROCK) {
					for (int j = 0; j < 3; ++j) {
						Comet newComet;
						//comets.push_back(newComet);
						newComet.Init(mPlayerSpriteSheet, "AsteroidsSprites");
						newComet.SetSize(COMET_SIZE::SMALL_ROCK);

						newComet.SetPos(comet.GetPos());
						newComet.SetVelocity(comet.GetVelocity() - 0.2);

						std::random_device rd;
						std::mt19937 gen(rd());
						std::uniform_real_distribution<> randomAngle(-20, 20);
						float newAngle = comet.GetAngle() + randomAngle(gen);
						newComet.SetAngle(newAngle);
						newComets.push_back(newComet);
					}
					mScore += 50;
					comet.SetExplode(true);
				}
				else {
					mScore += 100;
					comet.SetExplode(true);
				}
				
				bullet.SetToDestroy(true);
			}
		}

		comets.insert(comets.end(), newComets.begin(), newComets.end());
		//++i;
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

	//erase comet that collided
	for (auto i = comets.begin(); i != comets.end(); ) {
		auto& comet = *i;

		if (comet.CanDestroy()) {
			i = comets.erase(i);
		}
		else {
			++i;
		}
	}
}