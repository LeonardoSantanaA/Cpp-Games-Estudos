#include "Ship.h"
#include "../../App/App.h"
#include "../../Utils/Utils.h"
#include "../../Shapes/AARectangle.h"
#include <math.h>

Ship::Ship(): mController(nullptr), mAngle(0), lastDx(0), lastDy(0), mSpeed(0), turboPower(0.008f), mDirection(0), moving(false), shoot(false) {

}

Ship::~Ship() {
}

void Ship::Init(GameController& controller, SpriteSheet& mPlayerSpriteSheet, AnimatedSprite& playerSprite) {

	this->mPlayerSprite = playerSprite;
	
	Vec2D playerSpriteSize = mPlayerSprite.GetSize();
	mPlayerSprite.SetAnimation("ship", false);
	mPlayerSprite.SetPosition(Vec2D(App::Singleton().Width() / 2 - playerSpriteSize.GetX(), App::Singleton().Height() / 2 - playerSpriteSize.GetY() / 2));
	mPlayerSprite.SetRotate(true);
	
	mThrusterSprite.Init(App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt", mPlayerSpriteSheet);
	mThrusterSprite.SetAnimation("thrusters", true);
	mThrusterSprite.SetRotate(true);
	
	mController = &controller;

	ButtonAction backAction;
	backAction.key = GameController::CancelKey();
	backAction.action = [](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				App::Singleton().PopScene();
			}
		};
	mController->AddInputActionForKey(backAction);

	ButtonAction leftAction;
	leftAction.key = GameController::LeftKey();
	leftAction.action = [&](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				SetMovementDirection(ShipDirection::SHIP_LEFT);
			}
			else {
				UnsetMovementDirection(ShipDirection::SHIP_LEFT);
			}
		};
	mController->AddInputActionForKey(leftAction);

	ButtonAction rightAction;
	rightAction.key = GameController::RightKey();
	rightAction.action = [&](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				SetMovementDirection(ShipDirection::SHIP_RIGHT);
			}
			else {
				UnsetMovementDirection(ShipDirection::SHIP_RIGHT);
			}
		};
	mController->AddInputActionForKey(rightAction);

	ButtonAction turboAction;
	turboAction.key = GameController::UpKey();
	turboAction.action = [&](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state)) {
				moving = true;
			}
			else {
				moving = false;
			}
		};
	mController->AddInputActionForKey(turboAction);


}

void Ship::Update(uint32_t dt) {
	mPlayerSprite.Update(dt);

	Movement();

	if (mDirection == ShipDirection::SHIP_LEFT) {
		mAngle -= VELOCIY_ROTATE;
	}
	else if (mDirection == ShipDirection::SHIP_RIGHT) {
		mAngle += VELOCIY_ROTATE;
	}

	mPlayerSprite.SetAngle(mAngle + 1.5709f);

}

void Ship::Movement() {
	if (!moving && mSpeed > 0) {
		mSpeed -= 0.005f;
	}
	else if (!moving && mSpeed < 0) {
		mSpeed = 0;
	}
	else if (moving) {
		if (mSpeed < 1) {
			mSpeed += 0.005f;
		}
	}

	float newDx = mSpeed * std::cosf(mAngle);
	float newDy = mSpeed * std::sinf(mAngle);

	float moveDx = lastDx;
	float moveDy = lastDy;
	//std::cout << newDx << std::endl;
	if (moving) {
		if (moveDx < newDx) {
			moveDx += turboPower;
		}
		else if (moveDx > newDx) {
			moveDx -= turboPower;
		}

		if (moveDy < newDy) {
			moveDy += turboPower;
		}
		else if (moveDx > newDy) {
			moveDy -= turboPower;
		}
	}
	else {
		if (mSpeed <= 0.5) {
			if (moveDx < newDx) {
				moveDx += 0.002f;
			}
			else if (moveDx > newDx) {
				moveDx -= 0.002f;
			}

			if (moveDy < newDy) {
				moveDy += 0.002f;
			}
			else if (moveDx > newDy) {
				moveDy -= 0.002f;
			}
		}
	}

	mPlayerSprite.MoveBy(Vec2D(moveDx, moveDy));

	lastDx = moveDx;
	lastDy = moveDy;
}

void Ship::Draw(Screen& screen) {
	mPlayerSprite.Draw(screen);
	screen.Draw(mPlayerSprite.GetBoundingBox(), Color::Blue());
}
