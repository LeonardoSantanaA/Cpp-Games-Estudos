#include "AnimatedSprite.h"
#include "../Shapes/AARectangle.h"
#include "Screen.h"

AnimatedSprite::AnimatedSprite(): mPosition(Vec2D::Zero), mnoptrSpriteSheet(nullptr), mRotate(false), mAngle(0) {

}

AnimatedSprite::AnimatedSprite(const AnimatedSprite& other)
	:mPosition(other.mPosition), mnoptrSpriteSheet(other.mnoptrSpriteSheet), mRotate(other.mRotate), mAngle(other.mAngle), mColor(other.mColor) {
}


void AnimatedSprite::Init(const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color){
	mAnimationPlayer.Init(animationsPath);
	mnoptrSpriteSheet = &spriteSheet;
	mColor = color;
}

void AnimatedSprite::Update(uint32_t dt) {
	mAnimationPlayer.Update(dt);
}

void AnimatedSprite::Draw(Screen& theScreen) {
	AnimationFrame frame = mAnimationPlayer.GetCurrentAnimationFrame();

	Color frameColor = frame.frameColor;

	if (!frame.frameColorSet) {
		frameColor = mColor;
	}

	theScreen.Draw(*mnoptrSpriteSheet, frame.frame, mPosition + frame.offset, frameColor, mRotate, mAngle);

	if (frame.overlay.size() > 0) {
		theScreen.Draw(*mnoptrSpriteSheet, frame.overlay, mPosition, frame.overlayColor, mRotate, mAngle);
	}
	
}

void AnimatedSprite::SetAnimation(const std::string& animationName, bool looped) {
	mAnimationPlayer.Play(animationName, looped);
}

Vec2D AnimatedSprite::GetSize() const {
	return mAnimationPlayer.GetCurrentAnimationFrame().size;
}

void AnimatedSprite::Stop() {
	mAnimationPlayer.Stop();
}

const AARectangle AnimatedSprite::GetBoundingBox() const {
	AARectangle box = { mPosition, static_cast<unsigned int>(GetSize().GetX()), static_cast<unsigned int>(GetSize().GetY()) };
	return box;
}