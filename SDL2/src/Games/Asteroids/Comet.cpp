#include "Comet.h"
#include "../../App/App.h"
#include "../../Shapes/AARectangle.h"
#include <random>


Comet::Comet(): mPos(Vec2D::Zero), mVelocity(2), mAngle(0), mDirectionRotateAngle(0), mRotateAngle(0), mSize(0) {

}


void Comet::Init(SpriteSheet& cometSpriteSheet, std::string loadPathSpriteSheet) {

	mCometSpriteSheet = cometSpriteSheet;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> randomSize(0, 2);
	mSize = randomSize(gen);

	switch (mSize) {
	case COMET_SIZE::SMALL_ROCK:
	{
		mCometSprite = mCometSpriteSheet.GetSprite("small_rock");
		mSpriteName = "small_rock";
	}
	break;

	case COMET_SIZE::MEDIUM_ROCK:
	{
		mCometSprite = mCometSpriteSheet.GetSprite("medium_rock");
		mSpriteName = "medium_rock";
	}
	break;

	case COMET_SIZE::LARGE_ROCK:
	{
		mCometSprite = mCometSpriteSheet.GetSprite("medium_rock2");
		mSpriteName = "medium_rock";
	}
	break;

	}

	std::uniform_int_distribution<> randomPos(0, 1);
	int randomPosInitial = randomPos(gen);
	
	switch (randomPosInitial) {
	
	case COMET_INITIAL_SIDE::COMET_X:
	{
		std::uniform_int_distribution<> randomXPos(0, 1);
		int randomXPosInitial = randomXPos(gen);

		std::uniform_int_distribution<> randomYPos(-mCometSprite.height, App::Singleton().Height() + mCometSprite.height);
		int randomYPosInitial = randomYPos(gen);

		if (randomXPosInitial == 0) {
			Vec2D initialVector(-30, randomYPosInitial);
			mPos = initialVector;

			//set angles
			if (randomYPosInitial <= static_cast<int>(App::Singleton().Height() / 2)) {
				std::uniform_int_distribution<> randomAngle(0, 90);
				int randomAngleInitial = randomAngle(gen);
				mAngle = randomAngleInitial;
				
			}
			else {
				std::uniform_int_distribution<> randomAngle(270, 360);
				int randomAngleInitial = randomAngle(gen);
				mAngle = randomAngleInitial;
			}

		}
		else {
			Vec2D initialVector(App::Singleton().Width() + mCometSprite.width, randomYPosInitial);
			mPos = initialVector;

			//set angles
			if (randomYPosInitial <= static_cast<int>(App::Singleton().Height() / 2)) {
				std::uniform_int_distribution<> randomAngle(90, 180);
				int randomAngleInitial = randomAngle(gen);
				mAngle = randomAngleInitial;
			}
			else {
				std::uniform_int_distribution<> randomAngle(180, 270);
				int randomAngleInitial = randomAngle(gen);
				mAngle = randomAngleInitial;
			}
		}
	}
	break;
	
	case COMET_INITIAL_SIDE::COMET_Y:
	{
		std::uniform_int_distribution<> randomYPos(0, 1);
		int randomYPosInitial = randomYPos(gen);

		std::uniform_int_distribution<> randomXPos(-mCometSprite.width, App::Singleton().Height() + mCometSprite.width);
		int randomXPosInitial = randomXPos(gen);

		if (randomYPosInitial == 0) {
			Vec2D initialVector(randomXPosInitial, -30);
			mPos = initialVector;

			//set angles
			if (randomXPosInitial <= static_cast<int>(App::Singleton().Width() / 2)) {
				std::uniform_int_distribution<> randomAngle(0, 90);
				int randomAngleInitial = randomAngle(gen);
				mAngle = randomAngleInitial;
			}
			else {
				std::uniform_int_distribution<> randomAngle(90, 180);
				int randomAngleInitial = randomAngle(gen);
				mAngle = randomAngleInitial;
			}
		}
		else {
			Vec2D initialVector(randomXPosInitial, App::Singleton().Height() + mCometSprite.height);
			mPos = initialVector;

			//set angles
			if (randomXPosInitial <= static_cast<int>(App::Singleton().Width() / 2)) {
				std::uniform_int_distribution<> randomAngle(270, 360);
				int randomAngleInitial = randomAngle(gen);
				mAngle = randomAngleInitial;
			}
			else {
				std::uniform_int_distribution<> randomAngle(180, 270);
				int randomAngleInitial = randomAngle(gen);
				mAngle = randomAngleInitial;
			}
		}
	}
	break;
	
	}
	
	mAngle = (3.14159 / 180) * mAngle;

	std::uniform_int_distribution<> directionRotateRandom(0, 1);
	mDirectionRotateAngle = directionRotateRandom(gen);

	std::uniform_real_distribution<> velocityRandom(0.5, 1.5);
	mVelocity = velocityRandom(gen);

}


void Comet::Update(uint32_t dt) {
	if (mDirectionRotateAngle == 0) {
		mRotateAngle -= 0.03;
	}
	else {
		mRotateAngle += 0.03;
	}

	float dx = mVelocity * std::cosf(mAngle);
	float dy = mVelocity * std::sinf(mAngle);
	mPos += Vec2D(dx, dy);
}

void Comet::Draw(Screen& screen) {
	screen.Draw(mCometSpriteSheet, mSpriteName, mPos, Color::White(), true, mRotateAngle);
	screen.Draw(GetBoundingBox(), Color::White());
}


const AARectangle Comet::GetBoundingBox() {
	AARectangle box = { mPos, static_cast<unsigned int>(mCometSprite.width), static_cast<unsigned int>(mCometSprite.height) };

	return box;
}