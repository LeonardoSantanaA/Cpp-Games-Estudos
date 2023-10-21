#pragma once

#include "/C++/SDL2/src/Utils/Vec2D.h"
#include "/C++/Exercises/Star/src/Shapes/Line2D.h"
#include <SDL.h>

class Star {
private:
	static const int SIZE_DEFAULT = 40;
	float size;
	Vec2D startPosition;
	Line2D* starVertice = new Line2D[6];

	Line2D baseBottom; //0
	Line2D baseTop; //1
	Line2D sideLU; //2
	Line2D sideRU; //3
	Line2D sideLD; //4
	Line2D sideRD; //5

	void Initialize();

public:
	Star();
	Star(int x, int y, float size);
	Star(const Vec2D& vec, float size);
	~Star();
	Line2D GetVertice(int index);
	Vec2D MidPoint() const;
};