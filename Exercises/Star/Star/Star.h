#pragma once

#include "../Utils/Vec2D.h"
#include "../Shapes/Line2D.h"
#include <SDL.h>

class Star {
private:
	static const int SIZE_DEFAULT = 40;
	float size;
	Vec2D startPosition;
	Line2D* starVertice = new Line2D[6];

	void Initialize();

public:
	Star();
	Star(int x, int y);
	Star(int x, int y, float size);
	Star(const Vec2D& vec, float size);
	~Star();
	Line2D GetVertice(int index);
	Vec2D MidPoint() const;
};