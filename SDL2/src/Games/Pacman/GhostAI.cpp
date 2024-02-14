#include "GhostAI.h"
#include "PacmanLevel.h"
#include "../../Graphics/Screen.h"
#include <cassert>
#include <algorithm>
#include "../../Graphics/Color.h"

GhostAI::GhostAI(): mnoptrGhost(nullptr) {

}

void GhostAI::Init(GhostPacman& ghost, GhostName name) {
	mnoptrGhost = &ghost;
	mName = name;
	std::random_device r;
	mAIRandomGenerator.seed(r());
}

PacmanMovement GhostAI::Update(uint32_t dt, const PacmanLevel& level) {
	if (mnoptrGhost) {
		PacmanMovement currentDirection = mnoptrGhost->GetMovementDirection();

		std::vector<PacmanMovement> tempDirections;
		std::vector<PacmanMovement> possibleDirections;

		possibleDirections = GetPerpendicularMovements(currentDirection);

		if (currentDirection != PACMAN_MOVEMENT_NONE) {
			possibleDirections.push_back(currentDirection);
		}

		for (const auto& pDirection : possibleDirections) {
			tempDirections.push_back(pDirection);
		}

		possibleDirections.clear();

		for (const auto& direction : tempDirections) {
			if (!level.WillCollide(mnoptrGhost->GetBoundingBox(), direction)) {
				possibleDirections.push_back(direction);
			}
		}

		assert(possibleDirections.size() >= 1 && "Why cant we go anywhere?");

		std::sort(possibleDirections.begin(), possibleDirections.end(), [](const PacmanMovement& dir1, const PacmanMovement& dir2) {
			return dir1 < dir2;
			});

		std::uniform_int_distribution<size_t> distribution(0, possibleDirections.size() - 1);
		return possibleDirections[static_cast<int>(distribution(mAIRandomGenerator))];
	}

	return PACMAN_MOVEMENT_NONE;
}

void GhostAI::Draw(Screen& screen) {
	if (mnoptrGhost) {
		AARectangle bbox = mnoptrGhost->GetBoundingBox();
		bbox.MoveBy(GetMovementVector(mnoptrGhost->GetMovementDirection()) * mnoptrGhost->GetBoundingBox().GetWidth());
		Color c = Color(mnoptrGhost->GetSpriteColor().GetRed(), mnoptrGhost->GetSpriteColor().GetGreen(), mnoptrGhost->GetSpriteColor().GetBlue(), 200);
		screen.Draw(bbox, mnoptrGhost->GetSpriteColor(), true, c);
	}
}