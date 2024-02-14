#pragma once

#include "GhostPacman.h"
#include "PacmanGameUtils.h"
#include <random>

class PacmanLevel;
class Screen;

class GhostAI {
public:
	GhostAI();
	void Init(GhostPacman& ghost, GhostName name);

	PacmanMovement Update(uint32_t dt, const PacmanLevel& level);
	void Draw(Screen& screen);

private:
	GhostPacman* mnoptrGhost;
	GhostName mName;
	std::default_random_engine mAIRandomGenerator;

};