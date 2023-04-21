#ifndef _TEXTINVADERS_H_
#define _TEXTINVADERS_H_

#include <iostream>
#include <curses.h>
#include <string>
#include <vector>
#include "CursesUtils.hpp"

enum {
  SHIELD_SPRITE_HEIGHT = 3,
  NUM_ALIEN_ROWS = 5,
  NUM_ALIEN_COLUMNS = 11,
  MAX_NUMBER_ALIEN_BOMBS = 3,
  MAX_NUMBER_LIVES
};

enum AlienState{
  AS_ALIVE = 0,
  AS_DEAD,
  AS_EXPLODING
};

enum GameState{
  GS_INTRO = 0,
  GS_HIGH_SCORES,
  GS_PLAY,
  GS_PLAYER_DEAD,
  GS_WAIT,
  GS_GAME_OVER
};

struct Position{
  int x;
  int y;
};

struct Size{
  int width;
  int height;
};

struct Player{
  Position position;
  Position missile;
  Size spriteSize;
  int animation;
  int lives; //max 3 
  int score;
};

struct Shield{
  Position position;
  char* sprite[SHIELD_SPRITE_HEIGHT];
};

struct AlienBomb{
  Position position;
  int animation;
};

struct AlienSwarm{
  Position position;
  AlienState alien[NUM_ALIEN_ROWS][NUM_ALIEN_COLUMNS]; 
  AlienBomb bombs[MAX_NUMBER_ALIEN_BOMBS];
  Size spriteSize;
  int animation;
  int direction; // > 0 - for going right, < 0 - for going left, 1 or -1 
  int numberOfBombsInPlay;
  int movementTime; //this is going capture how fast the aliens should be going
  int explosionTimer; //this is going capture how long to explode for
  int numAliensLeft; //this is to capture when to go to the next level 
  int line; //this is to capture when the aliens win - starts at the current level and decreases to 0 - once it's 0 then the aliens 
};

struct AlienUFO{
  Position position;
  Size size;
  int points; //from 50 - 200
};

struct Score{
  int score;
  std::string name;
};

struct HighScoreTable{
  std::vector<Score> score;
};

struct Game{
  Size windowSize;
  GameState currentState;
  int level;
};

#endif
