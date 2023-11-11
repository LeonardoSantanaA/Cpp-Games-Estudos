#pragma once

#include "/C++/SDL2/src/Utils/Vec2D.h"
#include "/C++/Exercises/Star/src/Shapes/Line2D.h"
#include <SDL.h>
#include <vector>

class Star {
private:
	static const int SIZE_DEFAULT = 40;
	float size;
	float rotationSpeed;
	Vec2D startPosition;
	std::vector<Line2D> starVertice;

	void Initialize();

public:
	Star();
	Star(int x, int y);
	Star(int x, int y, float size);
	Star(const Vec2D& vec, float size);
	inline void SetRotationSpeed(float speed) { rotationSpeed = speed; }
	inline float GetRotationSpeed() { return rotationSpeed; }
	inline float GetSize() { return size; }
	inline Vec2D GetVec() { return startPosition; }
	inline std::vector<Line2D> GetLines() { return starVertice; }
	Line2D GetVertice(int index);
	Vec2D MidPoint() const;
};