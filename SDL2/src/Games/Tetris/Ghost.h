#pragma once

#include "Tetromino.h"

class Screen;

class Ghost : public Tetromino {
public:
	Ghost();

	void Update(uint32_t dt);

	void Draw(Screen& screen);

private:
	bool IsFree(const TetroDirection& dir) override;
	bool IsFree(const Vec2D& vec) override;
	bool VerifyCollision(const Blocks& blockDirection, const TetroDirection& dir) const override;

	std::vector<Blocks> ghostBlocks;

	inline std::vector<Blocks> GetRectangles() const override{ return ghostBlocks; }
	inline std::vector<Blocks>& GetRectangles() override{ return ghostBlocks; }

	inline TetroTypes GetType() const override{ return mType; }
	inline TetroRotations GetRotation() const override{ return mRotation; }
	inline void SetRotation(TetroRotations rot) override{ mRotation = rot; }
	inline void SetType(TetroTypes newType) override{ mType = newType; }

	void Gravity() override;
	void MoveBy(const Vec2D& offset) override;

	void Rotate() override;
	bool CanRotate(TetroTypes type, Blocks& midBlock, Vec2D* rotVec) override;


};