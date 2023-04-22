#include <iostream>
#include <cmath>
#include <cstring>
#include "TextInvaders.hpp"
#include "CursesUtils.hpp"

void InitGame(Game& game);
void InitPlayer(const Game& game, Player& player);
void ResetPlayer(const Game& game, Player& player);
void ResetMissile(Player& player);
int HandleInput(const Game& game, Player& player);
void UpdateGame(const Game& game, Player& player);
void DrawGame(const Game& game, const Player& player, Shield shields[], int numberOfShields);
void MovePlayer(const Game& game, Player& player, int dx);
void PlayerShoot(Player& player);
void DrawPlayer(const Player& player, const char* sprite[]);
void UpdateMissile(Player& player);
void InitShields(const Game& game, Shield shields[], int numberOfShields);
void CleanUpShields(Shield shields[], int numberOfShields);
void DrawShields(const Shield shields[], int numberOfShields);

int main(){
  Game game;
  Player player;
  Shield shields[NUM_SHIELS];

  InitializeCurses(true);

  InitGame(game);
  InitPlayer(game, player);
  InitShields(game, shields, NUM_SHIELS);

  bool quit = false;
  int input;

  clock_t lastTime = clock();

  while(!quit){
    input = HandleInput(game, player);

    if(input != 'q'){
      clock_t currentTime = clock();
      clock_t dt = currentTime - lastTime;

      if(dt > CLOCKS_PER_SEC / FPS){
      lastTime = currentTime;

      UpdateGame(game, player);
      ClearScreen(); //curses utils 
      DrawGame(game, player, shields, NUM_SHIELS);
      RefreshScreen(); //curses utils

      }
    }else{
      quit = true;
    }
  }

  CleanUpShields(shields, NUM_SHIELS);
  ShutdownCurses();

  return 0;
}

void InitGame(Game& game){
  game.windowSize.width = ScreenWidth();
  game.windowSize.height = ScreenHeight();
  game.level = 1;
  game.currentState = GS_PLAY; //for now - TODO: change to GS_INTRO at the end
}

void InitPlayer(const Game& game, Player& player){
  player.lives = MAX_NUMBER_LIVES;
  player.spriteSize.height = PLAYER_SPRITE_HEIGHT;
  player.spriteSize.width = PLAYER_SPRITE_WIDTH;
  ResetPlayer(game, player);
}

void ResetPlayer(const Game& game, Player& player){
  player.position.x = game.windowSize.width / 2 - player.spriteSize.width / 2; //puts the player in the center 
  player.position.y = game.windowSize.height - player.spriteSize.height - 1;
  player.animation = 0;
  ResetMissile(player);
}

void ResetMissile(Player& player){
  player.missile.x = NOT_IN_PLAY;
  player.missile.y = NOT_IN_PLAY;
}

int HandleInput(const Game& game, Player& player){
  int input = GetChar();

  switch(input){
    case 'q':
      return input;

    case AK_LEFT: 
      MovePlayer(game, player, -PLAYER_MOVEMENT_AMOUNT);
      break;

    case AK_RIGHT:
      MovePlayer(game, player, PLAYER_MOVEMENT_AMOUNT);
      break;

    case ' ':
      PlayerShoot(player);
      break;
  }

  return ' ';
}

void UpdateGame(const Game& game, Player& player){
  UpdateMissile(player); 
}

void DrawGame(const Game& game, const Player& player, Shield shields[], int numberOfShields){
  DrawPlayer(player, PLAYER_SPRITE);
  DrawShields(shields, numberOfShields);
}

void MovePlayer(const Game& game, Player& player, int dx){
  if(player.position.x + player.spriteSize.width + dx > game.windowSize.width){ //screen limits
    player.position.x = game.windowSize.width - player.spriteSize.width;
  }else if(player.position.x + dx < 0){
    player.position.x = 0;
  }else{
    player.position.x += dx;
  }
}

void PlayerShoot(Player& player){
  if(player.missile.x == NOT_IN_PLAY || player.missile.y == NOT_IN_PLAY){
    player.missile.y = player.position.y - 1; //one row above the player 
    player.missile.x = player.position.x + player.spriteSize.width / 2;
  }
}

void DrawPlayer(const Player& player, const char* sprite[]){
  DrawSprite(player.position.x, player.position.y, PLAYER_SPRITE, player.spriteSize.height);
  if(player.missile.x != NOT_IN_PLAY){
    DrawCharacter(player.missile.x, player.missile.y, PLAYER_MISSILE_SPRITE);
  }
}

void UpdateMissile(Player& player){
  if(player.missile.y != NOT_IN_PLAY){
    player.missile.y -= PLAYER_MISSILE_SPEED;

    if(player.missile.y < 0){
      ResetMissile(player);
    }
  }
}

void InitShields(const Game& game, Shield shields[], int numberOfShields){
  int firstPadding = std::ceil(float(game.windowSize.width - numberOfShields * SHIELD_SPRITE_WIDTH) / float(numberOfShields + 1));
  int xPadding = std::floor(float(game.windowSize.width - numberOfShields * SHIELD_SPRITE_WIDTH) / float(numberOfShields + 1));

  for(int i = 0; i < numberOfShields; i++){
    Shield& shield = shields[i];
    shield.position.x = firstPadding + i * (SHIELD_SPRITE_WIDTH + xPadding);
    shield.position.y = game.windowSize.height - PLAYER_SPRITE_HEIGHT - 1 - SHIELD_SPRITE_HEIGHT - 2;

    for(int row = 0; row < SHIELD_SPRITE_HEIGHT; row++){
      shield.sprite[row] = new char[SHIELD_SPRITE_WIDTH + 1];
      strcpy(shield.sprite[row], SHIELD_SPRITE[row]);
    }
  }
}

void CleanUpShields(Shield shields[], int numberOfShields){
  for(int i = 0; i < numberOfShields; i++){
    Shield& shield = shields[i];

    for(int row = 0; row < SHIELD_SPRITE_HEIGHT; row++){
      delete [] shield.sprite[row];
    }
  }
}

void DrawShields(const Shield shields[], int numberOfShields){
  for(int i = 0; i < numberOfShields; i++){
    const Shield& shield = shields[i];

    DrawSprite(shield.position.x, shield.position.y, (const char**)shield.sprite, SHIELD_SPRITE_HEIGHT);
  }
}
