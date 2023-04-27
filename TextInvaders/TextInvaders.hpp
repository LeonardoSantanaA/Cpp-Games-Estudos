#ifndef _TEXTINVADERS_H_
#define _TEXTINVADERS_H_

#include <string>
#include <vector>
#include <ctime>

const char* PLAYER_SPRITE[] = {" =A= ", "====="};

const char PLAYER_MISSILE_SPRITE = '|';

const char* SHIELD_SPRITE[] = {"/IIIII\\", "IIIIIII", "I/   \\I"};

const char* ALIEN30_SPRITE[] = {"/oo\\", "<  >", "/oo\\","/\"\"\\"};
const char* ALIEN20_SPRITE[] = {" >< ", "|\\/|", "|><|", "/  \\"};
const char* ALIEN10_SPRITE[] = {"/--\\","/  \\", "/--\\", "<  >"};

enum {
  SHIELD_SPRITE_HEIGHT = 3,
  SHIELD_SPRITE_WIDTH = 7,
  NUM_ALIEN_ROWS = 5,
  NUM_ALIEN_COLUMNS = 11,
  MAX_NUMBER_ALIEN_BOMBS = 3,
  MAX_NUMBER_LIVES,
  PLAYER_SPRITE_WIDTH = 5,
  PLAYER_SPRITE_HEIGHT = 2,
  NOT_IN_PLAY = -1,
  PLAYER_MOVEMENT_AMOUNT = 2,
  PLAYER_MISSILE_SPEED = 1,
  FPS = 20,
  NUM_SHIELDS = 4,
  ALIEN_SPRITE_WIDTH = 4,
  ALIEN_SPRITE_HEIGHT = 2,
  ALIENS_X_PADDING = 1,
  ALIENS_Y_PADDING = 1,
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
  AlienState aliens[NUM_ALIEN_ROWS][NUM_ALIEN_COLUMNS]; 
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
