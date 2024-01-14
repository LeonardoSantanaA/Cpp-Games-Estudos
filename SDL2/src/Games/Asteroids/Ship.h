#pragma once

#include "../../Graphics/AnimatedSprite.h"
#include "../../Graphics/SpriteSheet.h"
#include "../../Input/GameController.h"
#include "../../Shapes/Line2D.h"
#include "../../Utils/Utils.h"

class Screen;
class GameController;

enum ShipDirection {
	SHIP_LEFT = 1 << 0,
	SHIP_RIGHT = 1 << 1
};

class Ship {
public:
	Ship();
	~Ship();

	void Init(GameController& controller);
	void Update(uint32_t dt);
	void SetAngle(float newAngle) { mAngle = newAngle; }
	void Draw(Screen& screen);

private:
	AnimatedSprite mPlayerSprite;
	SpriteSheet mPlayerSpriteSheet;

	inline bool IsMovingLeft() const { return mDirection == ShipDirection::SHIP_LEFT; }
	inline bool IsMovingRight() const { return mDirection == ShipDirection::SHIP_RIGHT; }
	inline void SetMovementDirection(ShipDirection dir) { mDirection |= dir; }
	inline void UnsetMovementDirection(ShipDirection dir) { mDirection &= ~dir; }

	void Movement();

	const float VELOCIY_ROTATE = 0.05f;
	uint32_t mDirection;
	float lastDx, lastDy, turboPower;
	float mSpeed;
	float mAngle;
	bool moving;

	GameController* mController;

};