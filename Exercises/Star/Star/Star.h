#pragma once

#include "/C++/SDL2/src/Utils/Vec2D.h"
class Star {
private:
	static int SIZE_DEFAULT;
	float size;
	Vec2D startPosition;

	void Initialize();

public:
	Star();
	Star(const Vec2D& vec, float size);
	Vec2D MidPoint() const;
};