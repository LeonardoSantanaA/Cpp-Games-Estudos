#pragma once

#include "../../Shapes/AARectangle.h"
#include "../../Shapes/Line2D.h"
#include "Playfield.h"
#include "Collider.h"

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

	inline std::vector<AARectangle> GetRectangles() const { return tetroBlocks; }

	inline bool IsMovingLeft() const { return mDirection == TetroDirection::TET_LEFT; }
	inline bool IsMovingRight() const { return mDirection == TetroDirection::TET_RIGHT; }

	inline void SetMovementDirection(TetroDirection dir) { mDirection |= dir; }
	inline void UnsetMovementDirection(TetroDirection dir) { mDirection &= ~dir; }
	inline void StopMovement() { mDirection = 0; }

	void MoveBy(const Vec2D& offset);
	void Rotate();


private:
	const int NUM_TYPES = 7;

	bool IsFree(const TetroDirection& dir);
	bool IsFree(const Vec2D& vec);
	bool Collided(const AARectangle& block, const TetroDirection& dir);
	bool CanRotate(TetroTypes type, const AARectangle& midBlock, Vec2D* rotVec);

	inline void SetRotation(uint32_t rot) { mRotation = rot; }
	inline TetroTypes GetType() const { return (TetroTypes)mType; }

	void GenerateTetromino();
	
	void MoveDirection(const TetroDirection& dir);
	void Gravity();

	uint32_t mDirection;
	uint32_t mStats;
	uint32_t mRotation;
	

	AARectangle tetroBlock1 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	AARectangle tetroBlock2 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	AARectangle tetroBlock3 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	AARectangle tetroBlock4 = AARectangle(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));

	std::vector<AARectangle> tetroBlocks;

	Playfield playfield;

	int countDelay = 0;
	int mType = 0;
};