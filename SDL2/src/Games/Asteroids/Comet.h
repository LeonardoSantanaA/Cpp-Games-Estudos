#pragma once

#include "../../Utils/Vec2D.h"
#include "../../Graphics/AnimatedSprite.h"
#include "../../Graphics/SpriteSheet.h"

class Screen;

enum COMET_INITIAL_SIDE {
	COMET_Y = 0,
	COMET_X
};

enum COMET_SIZE {
	SMALL_ROCK = 0,
	MEDIUM_ROCK,
	LARGE_ROCK
};

class Comet {
public:
	Comet();

	void Init(SpriteSheet& cometSpriteSheet, std::string loadPathSpriteSheet);
	inline Vec2D GetPos() { return mPos; }

	void Update(uint32_t dt);
	void Draw(Screen& screen);

	const AARectangle GetBoundingBox();

private:
	Vec2D mPos;
	float mAngle;
	float mRotateAngle;
	int mDirectionRotateAngle;
	float mVelocity;
	int mSize;

	SpriteSheet mCometSpriteSheet;
	Sprite mCometSprite;
	std::string mSpriteName;
};