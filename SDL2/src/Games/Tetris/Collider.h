#pragma once

#include <vector>


class AARectangle;
class Tetromino;

class Collider {
public:
	static std::vector<Tetromino> tetrominos;
	static void VerifyScore();

private:
	static void DeleteBlocks(int y);

	static void ClearBlocks();
};