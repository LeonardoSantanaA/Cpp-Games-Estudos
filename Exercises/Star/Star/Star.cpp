#include "Star.h"
#include "/C++/Exercises/Star/src/Shapes/Line2D.h"

static int SIZE_DEFAULT = 20;

Star::Star() : Star(Vec2D::Zero, SIZE_DEFAULT) {

}

Star::Star(const Vec2D& vec, float size): startPosition(vec), size(size) {
	Initialize();
}

Vec2D Star::MidPoint() const{
	Vec2D midVec = { (startPosition.GetX() + size) / 2, (startPosition.GetY() + size) / 2};
	return midVec;
}

void Star::Initialize() {
	Vec2D midPoint = MidPoint();
	float yBaseBottom = midPoint.GetY() + (midPoint.GetY() / 2);
	float yBaseTop = midPoint.GetY() - (midPoint.GetY() / 2);
	
	//Base Bottom
	Vec2D p0BaseBottom = { startPosition.GetX(), yBaseBottom };
	Vec2D p1BaseBottom = { startPosition.GetX() + size, yBaseBottom };
	Line2D baseBottom(p0BaseBottom, p1BaseBottom);

	//Base Top
	Vec2D p0BaseTop = { startPosition.GetX(), yBaseTop };
	Vec2D p1BaseTop = { startPosition.GetX() + size, yBaseTop };
	Line2D baseTop(p0BaseTop, p1BaseTop);

	//Side Left-Up
	Vec2D p0SideLU = { startPosition.GetX(), yBaseBottom };
	Vec2D p1SideLU = { midPoint.GetX(), startPosition.GetY()};
	Line2D sideLU(p0SideLU, p1SideLU);

	//Size Right-Up
	Vec2D p0SideRU = { startPosition.GetX() + size, yBaseBottom };
	Vec2D p1SideRU = { midPoint.GetX(), startPosition.GetY() };
	Line2D sideRU(p0SideRU, p1SideRU);

	//Size Left-Down
	Vec2D p0SideLD = { startPosition.GetX(), yBaseTop };
	Vec2D p1SideLD = { midPoint.GetX(), startPosition.GetY() + size };
	Line2D sideLD(p0SideLD, p1SideLD);

	//Size Left-Down
	Vec2D p0SideLD = { startPosition.GetX() + size, yBaseTop };
	Vec2D p1SideLD = { midPoint.GetX(), startPosition.GetY() + size };
	Line2D sideLD(p0SideLD, p1SideLD);
}