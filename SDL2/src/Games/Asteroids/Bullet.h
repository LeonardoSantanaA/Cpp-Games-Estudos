#pragma once

#include "../../Utils/Vec2D.h"
#include "../../Graphics/AnimatedSprite.h"
#include "../../Graphics/SpriteSheet.h"

class Bullet {
public:
	Bullet();
	Bullet(const Vec2D& pos, float angle);

	Bullet(Bullet&& other) noexcept;
	Bullet& operator=(const Bullet& other);

	void Init(SpriteSheet& mPlayerSpriteSheet, AnimatedSprite& shootSprite);
	void Load(SpriteSheet& mPlayerSpriteSheet);

	void Update(uint32_t dt);
	void Draw(Screen& screen);

	inline Vec2D GetPos() { return mBulletSprite.GetPosition(); }
	inline void SetPos(const Vec2D& pos) { mPos = pos; }

	AARectangle GetBoundingBox();

private:
	Vec2D mPos;
	float mAngle;
	float mBulletSpeed;

	AnimatedSprite mBulletSprite;
};