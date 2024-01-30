#pragma once

#include "../../Utils/Vec2D.h"
#include "../BreakOut/Excluder.h"
#include <string>
#include <vector>

class Screen;

class PacmanLevel {
public:
	bool Init(const std::string& levelPath);
	void Update(uint32_t dt);
	void Draw(Screen& screen);


private:
	struct Tile {
		Vec2D position = Vec2D::Zero;
		int width = 0;
		int collidable = 0;
		char symbol = '-';
	};

	bool LoadLevel(const std::string& levelPath);
	Tile* GetTileForSymbol(char symbol);

	std::vector<Excluder> mWalls;
	std::vector<Tile> mTiles;

	Vec2D mLayoutOffset;
	size_t mTileHeight;

};