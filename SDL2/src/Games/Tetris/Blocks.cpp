#include "Blocks.h"
#include "../../Graphics/Screen.h"

Blocks::Blocks() : Blocks(Vec2D::Zero, Vec2D::Zero) {
}

Blocks::Blocks(const Vec2D& topLeft, unsigned int width, unsigned int height) {
	//this->rect.SetTopLeftPoint(topLeft);
	rect = AARectangle(topLeft, width, height);
	SetStats(BlockStats::BL_GAME);
}

Blocks::Blocks(const Vec2D& topLeft, const Vec2D& bottomRight) {
	rect = AARectangle(topLeft, bottomRight);
	SetStats(BlockStats::BL_GAME);
}

void Blocks::Draw(Screen& screen){
	if (mStatsBlock == BlockStats::BL_GAME) {
		screen.Draw(rect, Color::Pink(), true, Color::White());
	}
	else {
		screen.Draw(rect, Color::Red(), true, Color::Black());
	}
	
}

void Blocks::MoveTo(Vec2D pos) {
	rect.MoveTo(pos);
}

void Blocks::MoveBy(Vec2D offset) {
	rect.MoveBy(offset);
}