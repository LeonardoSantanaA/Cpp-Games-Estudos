#pragma once

#include <vector>


class AARectangle;
class Tetromino;

class Collider {
public:
	static std::vector<Tetromino> tetrominos;

	bool IsColliding();

private:
	bool CollideWithTetrominoInPlay(const AARectangle& block);

};