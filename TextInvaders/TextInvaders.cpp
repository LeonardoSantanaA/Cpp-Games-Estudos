#include <iostream>
#include "TextInvaders.hpp"
#include "CursesUtils.hpp"

void InitGame(Game& game);
void InitPlayer(const Game& game, Player& player);
void ResetPlayer(const Game& game, Player& player);
void ResetMissile(Player& player);
int HandleInput(const Game& game, Player& player);
void UpdateGame(const Game& game, Player& player);
void DrawGame(const Game& game, const Player& player);
void MovePlayer(const Game& game, Player& player, int dx);

int main(){
  Game game;
  Player player;

  InitializeCurses(true);

  InitGame(game);
  InitPlayer(game, player);

  bool quit = false;
  int input;

  while(!quit){
    input = HandleInput(game, player);

    if(input != 'q'){
      UpdateGame(game, player);
      ClearScreen(); //curses utils 
      DrawGame(game, player);
      RefreshScreen(); //curses utils
    }else{
      quit = true;
    }

  }

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
  }

  return ' ';
}

void UpdateGame(const Game& game, Player& player){
  
}

void DrawGame(const Game& game, const Player& player){
  DrawSprite(player.position.x, player.position.y, PLAYER_SPRITE, player.spriteSize.height);
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
