#pragma once

#include "../../Shapes/AARectangle.h"
#include "Playfield.h"

class Screen;

enum TetroStats {
	TET_PLAY = 0,
	TET_STATIC, 
	TET_FALLING
};

enum TetroDirection {
	TET_ZERO = 0,
	TET_RIGHT,
	TET_LEFT,
	TET_DOWN
};

enum TetroTypes {
	I = 0,
	J,
	L,
	O,
	S,
	T,
	Z
};

class Tetromino {
public:
	void Init();
	void Update(uint32_t dt);
	void Draw(Screen& screen);

	inline void Solidify() { mStats = TetroStats::TET_STATIC; }

	inline bool IsMovingLeft() const { return mDirection == TetroDirection::TET_LEFT; }
	inline bool IsMovingRight() const { return mDirection == TetroDirection::TET_RIGHT; }

	inline void SetMovementDirection(TetroDirection dir) { mDirection |= dir; }
	inline void UnsetMovementDirection(TetroDirection dir) { mDirection &= ~dir; }
	inline void StopMovement() { mDirection = 0; }

private:
	const int NUM_TYPES = 7;

	bool IsFree(const TetroDirection& dir);
	void GenerateTetromino();
	void MoveBy(const Vec2D& offset);
	void MoveDirection(const TetroDirection& dir);
	void Gravity();

	uint32_t mDirection;
	uint32_t mStats;

	std::vector<AARectangle> tetroBlocks;
	Playfield playfield;
	int countDelay = 0;
};