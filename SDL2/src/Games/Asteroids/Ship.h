#pragma once

#include "Bullet.h"
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

	void Init(GameController& controller, SpriteSheet& playerSpriteSheet, AnimatedSprite& playerSprite);
	void Reset();
	void Update(uint32_t dt);
	void SetAngle(float newAngle) { mAngle = newAngle; }
	void Draw(Screen& screen);

	const AARectangle GetBoundingBox();
	const Vec2D& GetPosition() { return mPlayerSprite.GetPosition(); }
	float GetAngle() { return mAngle; }

	inline int GetLife() const { return mLife; }
	inline bool CanReduceLife() const { return canReduceLife; }
	inline void SetDamaged(bool wasDamaged) { damaged = wasDamaged; }
	inline bool isDamaged() { return damaged; }
	inline void FullLife() { mLife = 3; }

private:
	AnimatedSprite mPlayerSprite;
	AnimatedSprite mThrusterSprite;
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
	bool shoot;
	int countDownLife;
	bool canReduceLife;
	bool damaged;
	int mLife;

	Vec2D midPoint;
	GameController* mController;

};