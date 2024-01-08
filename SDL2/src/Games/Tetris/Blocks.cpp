#include "Blocks.h"
#include "../../Graphics/Screen.h"

Blocks::Blocks() : Blocks(Vec2D::Zero, Vec2D::Zero) {

}

Blocks::Blocks(const Vec2D& topLeft, unsigned int width, unsigned int height) {
	//this->rect.SetTopLeftPoint(topLeft);
	rect = AARectangle(topLeft, width, height);
	SetStats(BlockStats::BL_GAME);
	SetColor(Color(102, 113, 215, 255));
	SetFillColor(Color(63, 172, 149, 255));
}

Blocks::Blocks(const Vec2D& topLeft, const Vec2D& bottomRight) {
	rect = AARectangle(topLeft, bottomRight);
	SetStats(BlockStats::BL_GAME);
	SetColor(Color(102, 113, 215, 255));
	SetFillColor(Color(63, 172, 149, 255));
}

void Blocks::Draw(Screen& screen){
	if (this != nullptr) {
		screen.Draw(rect, color, true, fillColor);
	}
}

void Blocks::MoveTo(Vec2D pos) {
	if (this != nullptr) {
		rect.MoveTo(pos);
	}
	
}

void Blocks::MoveBy(Vec2D offset) {
	if (this != nullptr) {
		rect.MoveBy(offset);
	}
}