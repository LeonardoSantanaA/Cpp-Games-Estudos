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
	

	void Update(uint32_t dt);
	void Draw(Screen& screen);

	const AARectangle GetBoundingBox();

	inline float GetAngle() { return mAngle; }
	inline void SetAngle(float angle) { mAngle = angle; }
	void SetSize(uint32_t size);
	inline void SetPos(Vec2D pos) { mPos = pos; }
	inline const Vec2D& GetPos() const { return mPos; }
	inline void SetExplode(bool canExplode) { mCanExplode = canExplode; }
	inline void SetDestroy(bool canDestroy) { mCanDestroy = canDestroy; }
	inline bool CanDestroy() { return mCanDestroy; }
	inline bool CanExplode() { return mCanExplode; }
	inline uint32_t GetSize() const { return mSize; }
	inline const Vec2D& GetSpriteSize() const { return Vec2D(mCometSprite.width, mCometSprite.height); }
	inline float GetVelocity() const { return mVelocity; }
	inline void SetVelocity(float newVel) { mVelocity = newVel; }

private:
	Vec2D mPos;
	float mAngle;
	float mRotateAngle;
	int mDirectionRotateAngle;
	float mVelocity;
	uint32_t mSize;
	bool mCanExplode;
	bool mCanDestroy;

	SpriteSheet mCometSpriteSheet;
	Sprite mCometSprite;
	std::string mSpriteName;
};