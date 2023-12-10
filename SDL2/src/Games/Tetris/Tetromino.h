#pragma once

#include "../../Shapes/Line2D.h"
#include "Playfield.h"
#include "Blocks.h"
#include <memory>

class Screen;



enum TetroStats {
	TET_PLAY = 0,
	TET_STATIC,
	TET_GHOST
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
	Tetromino();
	~Tetromino();

	void Update(uint32_t dt);
	void Draw(Screen& screen);

	inline uint32_t GetStats() const { return mStats; }
	inline virtual TetroRotations GetRotation() const { return mRotation; }
	virtual inline TetroTypes GetType() const { return mType; }

	virtual inline std::vector<Blocks> GetRectangles() const { return tetroBlocks; }
	virtual inline std::vector<Blocks>& GetRectangles() { return tetroBlocks; }

	bool IsFree(const Tetromino& tetrominoToDown, const Vec2D& vec);
	virtual void MoveBy(const Vec2D& offset);


	inline bool IsMovingLeft() const { return mDirection == TetroDirection::TET_LEFT; }
	inline bool IsMovingRight() const { return mDirection == TetroDirection::TET_RIGHT; }

	inline void SetMovementDirection(TetroDirection dir) { mDirection |= dir; }
	inline void UnsetMovementDirection(TetroDirection dir) { mDirection &= ~dir; }
	inline void StopMovement() { mDirection = 0; }

	virtual void Rotate();

	void VerifyScore();

private:
	const int NUM_TYPES = 7;

	void Solidify();
	void GenerateTetromino();
	void MoveDirection(const TetroDirection& dir);
	
	uint32_t mDirection;
	uint32_t mStats;

	std::vector<Blocks> tetroBlocks;

	int countDelay = 0;

protected:
	TetroRotations mRotation;
	TetroTypes mType;

	std::shared_ptr<Blocks> tetroBlock1 = std::make_shared<Blocks>(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	std::shared_ptr<Blocks> tetroBlock2 = std::make_shared<Blocks>(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	std::shared_ptr<Blocks> tetroBlock3 = std::make_shared<Blocks>(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	std::shared_ptr<Blocks> tetroBlock4 = std::make_shared<Blocks>(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));

	Blocks mLeftTetromino = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	Blocks mRightTetromino = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));
	Blocks mDownTetromino = Blocks(Vec2D(0, 0),
		Vec2D(Playfield::GRID_BLOCK_SIZE, Playfield::GRID_BLOCK_SIZE));

	virtual void Gravity();

	inline void SetState(uint32_t newState) { mStats = newState; }
	inline virtual void SetRotation(TetroRotations rot) { mRotation = rot; }
	inline virtual void SetType(TetroTypes newType) { mType = newType; }

	virtual bool CanRotate(TetroTypes type, Blocks& midBlock, Vec2D* rotVec);

	virtual bool IsFree(const Vec2D& vec);
	virtual bool IsFree(const TetroDirection& dir);
	
	virtual bool VerifyCollision(const Blocks& blockDirection, const TetroDirection& dir) const;
	bool Collided(const Blocks& block, const TetroDirection& dir) const;

};