#pragma once

#include "Actor.h"
#include "../../Graphics/Color.h"
#include "PacmanGameUtils.h"
#include "../../Shapes/AARectangle.h"

enum GhostName {
	BLINKY = 0,
	PINKY,
	INKY,
	CLYDE,
	NUM_GHOSTS
};

enum GhostState {
	GHOST_STATE_ALIVE = 0,
	GHOST_STATE_VULNERABLE,
	GHOST_STATE_VULNERABLE_ENDING,
	GHOST_STATE_DEAD
};

class GhostPacman : public Actor {
public:
	static const uint32_t VULNERABILITY_TIME = 6000;
	static const uint32_t VULNERABILITY_ENDING_TIME = 4000;

	GhostPacman();
	virtual void Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vec2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor = Color::White()) override;
	virtual void Update(uint32_t dt) override;

	void SetStateToVulnerable();
	virtual void SetMovementDirection(PacmanMovement direction) override;
	virtual void Stop() override;

	void EatenByPacman();
	void ResetToFirstPosition();

	inline bool IsDead() const { return mState == GHOST_STATE_DEAD; }
	inline bool IsVulnerable() const { return mState == GHOST_STATE_VULNERABLE || mState == GHOST_STATE_VULNERABLE_ENDING; }
	inline bool IsAlive() const { return mState == GHOST_STATE_ALIVE; }
	inline uint32_t GetPoints() const { return mPoints; }
	inline void LockCanChangeDirection() { mCanChangeDirection = false; }


private:
	void SetGhostState(GhostState state);

	uint32_t mVulnerabilityTimer;
	uint32_t mPoints;
	GhostState mState;
	bool mCanChangeDirection;
	Vec2D mInitialPos;

};