#pragma once

#include "../../Shapes/Line2D.h"
#include "Playfield.h"
#include "Blocks.h"

class Screen;



enum TetroStats {
	TET_PLAY = 0,
	TET_STATIC
};

enum TetroRotations {
	ROT_LEFT = 0,
	ROT_UP,
	ROT_RIGHT,
	ROT_DOWN
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
	inline uint32_t GetStats() const { return mStats; }
	inline uint32_t GetRotation() const { return mRotation; }

	inline std::vector<Blocks>& GetRectangles() { return tetroBlocks; }

	inline bool IsMovingLeft() const { return mDirection == TetroDirection::TET_LEFT; }
	inline bool IsMovingRight() const { return mDirection == TetroDirection::TET_RIGHT; }

	inline void SetMovementDirection(TetroDirection dir) { mDirection |= dir; }
	inline void UnsetMovementDirection(TetroDirection dir) { mDirection &= ~dir; }
	inline void StopMovement() { mDirection = 0; }

	void MoveBy(const Vec2D& offset);
	void Rotate();

	void VerifyScore();

private:
	const int NUM_TYPES = 7;

	bool IsFree(const TetroDirection& dir);
	bool IsFree(const Vec2D& vec);
	bool Collided(const Blocks& block, const TetroDirection& dir);
	bool CanRotate(TetroTypes type, const Blocks& midBlock, Vec2D* rotVec);

	inline void SetRotation(uint32_t rot) { mRotation = rot; }
	inline TetroTypes GetType() const { return (TetroTypes)mType; }


	void GenerateTetromino();
	
	void MoveDirection(const TetroDirection& dir);
	void Gravity();

	uint32_t mDirection;
	uint32_t mStats;
	uint32_t mRotation;


	Blocks tetroBlock1 = Blocks (Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	Blocks tetroBlock2 = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	Blocks tetroBlock3 = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	Blocks tetroBlock4 = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));

	std::vector<Blocks> tetroBlocks;

	int countDelay = 0;
	int mType = 0;
};