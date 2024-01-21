#include "Bullet.h"
#include "../../App/App.h"
#include "../../Shapes/AARectangle.h"

Bullet::Bullet(): mPos(Vec2D::Zero), mAngle(0), mBulletSpeed(3), mCanDestroy(false) {
	
}

Bullet::Bullet(const Vec2D& pos, float angle): mPos(pos), mAngle(angle), mBulletSpeed(3), mCanDestroy(false){


}

Bullet::~Bullet() {

}

Bullet::Bullet(Bullet&& other) noexcept
	: mPos(other.mPos),
	mAngle(other.mAngle),
	mBulletSpeed(other.mBulletSpeed),
	mBulletSprite(other.mBulletSprite),
	mCanDestroy(false)
{
	 other.mPos = {};
	 other.mAngle = 0;
	 other.mBulletSpeed = 0;
	 other.mBulletSprite = {};
}

Bullet& Bullet::operator=(const Bullet& other) {
	if (this != &other) {
		mPos = other.mPos;
		mAngle = other.mAngle;
		mBulletSpeed = other.mBulletSpeed;
		mBulletSprite = other.mBulletSprite;
	}
	return *this;
}

void Bullet::Init(SpriteSheet& spriteSheet, AnimatedSprite& bulletSprite) {
	this->mBulletSprite = bulletSprite;
	
	Load(spriteSheet);
	mBulletSprite.SetPosition(mPos - Vec2D(mBulletSprite.GetSize().GetX() / 2, 0));
}

void Bullet::Load(SpriteSheet& mPlayerSpriteSheet) {
	mBulletSprite.SetAnimation("missile", true);
	mBulletSprite.SetRotate(true);
}

void Bullet::Update(uint32_t dt) {
	float dx = mBulletSpeed * std::cosf(mAngle);
	float dy = mBulletSpeed * std::sinf(mAngle);
	mBulletSprite.SetAngle(mAngle + 1.5709f);
	mBulletSprite.MoveBy(Vec2D(dx, dy));

	mBulletSprite.Update(dt);
}

void Bullet::Draw(Screen& screen) {
	mBulletSprite.Draw(screen);	
}

const AARectangle Bullet::GetBoundingBox() {
	return mBulletSprite.GetBoundingBox();
}