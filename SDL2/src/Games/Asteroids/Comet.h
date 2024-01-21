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
	~Comet();

	void Init(SpriteSheet& cometSpriteSheet, std::string loadPathSpriteSheet);
	inline Vec2D GetPos() { return mPos; }

	void Update(uint32_t dt);
	void Draw(Screen& screen);

	const AARectangle GetBoundingBox();

	inline void SetExplode(bool canExplode) { mCanExplode = canExplode; }
	inline bool CanExplode() { return mCanExplode; }
	inline uint32_t GetSize() { return mSize; }
	inline Vec2D GetSpriteSize() { return Vec2D(mCometSprite.width, mCometSprite.height); }

private:
	Vec2D mPos;
	float mAngle;
	float mRotateAngle;
	int mDirectionRotateAngle;
	float mVelocity;
	uint32_t mSize;
	bool mCanExplode;

	SpriteSheet mCometSpriteSheet;
	Sprite mCometSprite;
	std::string mSpriteName;
};