#pragma once

#include "../../Shapes/AARectangle.h"
#include "../../Graphics/Screen.h"

enum BlockStats {
	BL_GAME = 0,
	BL_REMOVE
};

//fazer proprio metodo Draw
class Screen;

class Blocks {
public:
	Blocks();
	Blocks(const Vec2D& topLeft, unsigned int width, unsigned int height);
	Blocks(const Vec2D& topLeft, const Vec2D& bottomRight);
	void CantRotate();

	void Draw(Screen& screen);

	inline Vec2D GetTopLeftPoint() const { return rect.GetTopLeftPoint(); }
	inline Vec2D GetBottomRightPoint() const { return rect.GetBottomRightPoint(); }
	inline void SetColor(const Color& newColor) { color = newColor; }
	inline void SetFillColor(const Color& newColor) { fillColor = newColor; }
	inline void SetPosition(const Vec2D& pos) { rect.MoveTo(pos); }
	void MoveTo(Vec2D pos);
	void MoveBy(Vec2D offset);


	inline uint32_t GetStats() const { return mStatsBlock; }
	inline void SetStats(uint32_t status)  { mStatsBlock = status; }

private:
	uint32_t mStatsBlock;

	bool cantRotate = false;
	Color color;
	Color fillColor;
	AARectangle rect;
};