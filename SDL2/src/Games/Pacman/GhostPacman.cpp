#include "GhostPacman.h"

namespace {
	const uint32_t NUM_POINTS_FOR_GHOST = 200;
}

GhostPacman::GhostPacman(): mPoints(0), mInitialPos(Vec2D::Zero), mIsReleased(false), mDelegate(nullptr) {

}

void GhostPacman::Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor) {
	Actor::Init(spriteSheet, animationsPath, initialPos, movementSpeed, updateSpriteOnMovement, spriteColor);
	mInitialPos = initialPos;
	mPoints = NUM_POINTS_FOR_GHOST;
	ResetToFirstPosition();
}

void GhostPacman::Update(uint32_t dt) {
	Vec2D position = GetPosition();
	Actor::Update(dt);
	mCanChangeDirection = position != GetPosition();

	if (IsVulnerable()) {
		mVulnerabilityTimer += dt;

		if (mState == GHOST_STATE_VULNERABLE && mVulnerabilityTimer >= VULNERABILITY_TIME) {
			SetGhostState(GHOST_STATE_VULNERABLE_ENDING);
		}

		if (mState == GHOST_STATE_VULNERABLE_ENDING && mVulnerabilityTimer >= VULNERABILITY_ENDING_TIME) {
			SetGhostState(GHOST_STATE_ALIVE);
		}
	}
}

void GhostPacman::SetStateToVulnerable() {
	if (mState != GHOST_STATE_DEAD) {
		SetGhostState(GHOST_STATE_VULNERABLE);
	}
}

void GhostPacman::SetMovementDirection(PacmanMovement direction) {
	Actor::SetMovementDirection(direction);

	PacmanMovement movementDir = GetMovementDirection();

	if (mState == GHOST_STATE_ALIVE) {
		if (movementDir == PACMAN_MOVEMENT_RIGHT) {
			SetAnimation("ghost_movement_right", true);
		}
		else if (movementDir == PACMAN_MOVEMENT_UP) {
			SetAnimation("ghost_movement_up", true);
		}
		else if (movementDir == PACMAN_MOVEMENT_LEFT) {
			SetAnimation("ghost_movement_left", true);
		}
		else if (movementDir == PACMAN_MOVEMENT_DOWN) {
			SetAnimation("ghost_movement_down", true);
		}
	}
	else if (mState == GHOST_STATE_DEAD) {
		if (movementDir == PACMAN_MOVEMENT_RIGHT) {
			SetAnimation("ghost_dead_right", true);
		}
		else if (movementDir == PACMAN_MOVEMENT_UP) {
			SetAnimation("ghost_dead_up", true);
		}
		else if (movementDir == PACMAN_MOVEMENT_LEFT) {
			SetAnimation("ghost_dead_left", true);
		}
		else if (movementDir == PACMAN_MOVEMENT_DOWN) {
			SetAnimation("ghost_dead_down", true);
		}
	}
}

void GhostPacman::Stop() {
	SetMovementDirection(PACMAN_MOVEMENT_NONE);
}

void GhostPacman::EatenByPacman() {
	SetGhostState(GHOST_STATE_DEAD);
}

void GhostPacman::ResetToFirstPosition() {
	mSprite.SetPosition(mInitialPos);
	SetMovementDirection(PACMAN_MOVEMENT_NONE);
	mVulnerabilityTimer = 0;
	SetGhostState(GHOST_STATE_ALIVE);
	mCanChangeDirection = true;
	mIsReleased = false;

	if (mDelegate) {
		mDelegate->GhostWasResetToFirstPosition();
	}
}

void GhostPacman::SetGhostState(GhostState state) {
	if (mDelegate) {
		mDelegate->GhostDelegateGhostStateChangedTo(mState, state);
	}

	mState = state;
	switch (mState) {
	case GHOST_STATE_ALIVE:
		SetMovementDirection(GetMovementDirection());
		SetMovementSpeed(GHOST_MOVEMENT_SPEED);
		break;

	case GHOST_STATE_VULNERABLE:
		mSprite.SetAnimation("ghost_vulnerable", true);
		mVulnerabilityTimer = 0;
		SetMovementSpeed(GHOST_VULNERABLE_MOVEMENT_SPEED);
		break;

	case GHOST_STATE_VULNERABLE_ENDING:
		mSprite.SetAnimation("ghost_vulnerable_ending", true);
		mVulnerabilityTimer = 0;
		break;

	case GHOST_STATE_DEAD:
		SetMovementDirection(GetMovementDirection());
		SetMovementSpeed(GHOST_BACK_TO_PEN_SPEED);
		break;
	}
}

void GhostPacman::ReleasedFromPen() {
	mIsReleased = true;

	if (mDelegate) {
		mDelegate->GhostWasReleasedFromPen();
	}
}