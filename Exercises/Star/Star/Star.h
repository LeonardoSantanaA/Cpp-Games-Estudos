#pragma once

#include "/C++/SDL2/src/Utils/Vec2D.h"
#include "/C++/Exercises/Star/src/Shapes/Line2D.h"
class Star {
private:
	static const int SIZE_DEFAULT = 40;
	float size;
	Vec2D startPosition;

	Line2D baseBottom;
	Line2D baseTop;
	Line2D sideLU;
	Line2D sideRU;
	Line2D sideLD;
	Line2D sideRD;

	inline void SetBaseBottom(Line2D baseBottom) { this->baseBottom = baseBottom; }
	inline void SetBaseTop(Line2D baseTop) { this->baseTop = baseTop; }
	inline void SetSideLU(Line2D sideLU) { this->sideLU = sideLU; }
	inline void SetSideRU(Line2D sideRU) { this->sideRU = sideRU; }
	inline void SetSideLD(Line2D sideLD) { this->sideLD = sideLD; }
	inline void SetSideRD(Line2D sideRD) { this->sideRD = sideRD; }

	void Initialize();

public:
	Star();
	Star(int x, int y, float size);
	Star(const Vec2D& vec, float size);
	Vec2D MidPoint() const;
	inline Line2D GetBaseBottom() const { return baseBottom; }
	inline Line2D GetBaseTop() const { return baseTop; }
	inline Line2D GetSideLU() const { return sideLU; }
	inline Line2D GetSideRU() const { return sideRU; }
	inline Line2D GetSideLD() const { return sideLD; }
	inline Line2D GetSideRD() const { return sideRD; }
};