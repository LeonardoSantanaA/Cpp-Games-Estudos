#include "Star.h"
#include "/C++/Exercises/Star/src/Shapes/Line2D.h"

Star::Star() : Star(Vec2D::Zero, SIZE_DEFAULT) {

}

Star::Star(int x, int y, float size) : startPosition(x, y), size(size) {
	Initialize();
}

Star::Star(const Vec2D& vec, float size): startPosition(vec), size(size) {
	Initialize();
}



Vec2D Star::MidPoint() const{
	Vec2D midVec(startPosition.GetX() + (size/2), startPosition.GetY() + (size/2));
	return midVec;
}

void Star::Initialize() {
	Vec2D midPoint = MidPoint();
	float midSize = size / 2;
	float yBaseBottom = midPoint.GetY() + (midSize / 2);
	float yBaseTop = midPoint.GetY() - (midSize / 2);
	
	//Base Bottom
	Vec2D p0BaseBottom = { startPosition.GetX(), yBaseBottom };
	Vec2D p1BaseBottom = { startPosition.GetX() + size, yBaseBottom };
	Line2D baseBottom(p0BaseBottom, p1BaseBottom);
	SetBaseBottom(baseBottom);

	//Base Top
	Vec2D p0BaseTop = { startPosition.GetX(), yBaseTop };
	Vec2D p1BaseTop = { startPosition.GetX() + size, yBaseTop };
	Line2D baseTop(p0BaseTop, p1BaseTop);
	SetBaseTop(baseTop);

	//Side Left-Up
	Vec2D p0SideLU = { p0BaseBottom.GetX(),yBaseBottom};
	Vec2D p1SideLU = { midPoint.GetX(), startPosition.GetY()};
	Line2D sideLU(p0SideLU, p1SideLU);
	SetSideLU(sideLU);

	//Size Right-Up
	Vec2D p0SideRU = { p1BaseBottom.GetX(), yBaseBottom };
	Vec2D p1SideRU = { midPoint.GetX(), startPosition.GetY() };
	Line2D sideRU(p0SideRU, p1SideRU);
	SetSideRU(sideRU);

	//Size Left-Down
	Vec2D p0SideLD = { p0BaseTop.GetX(), yBaseTop };
	Vec2D p1SideLD = { midPoint.GetX(), startPosition.GetY() + size};
	Line2D sideLD(p0SideLD, p1SideLD);
	SetSideLD(sideLD);

	//Size Right-Down
	Vec2D p0SideRD = { p1BaseTop.GetX(), yBaseTop };
	Vec2D p1SideRD = { midPoint.GetX(), startPosition.GetY() + size};
	Line2D sideRD(p0SideRD, p1SideRD);
	SetSideRD(sideRD);
}