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
void UpdateGame(const Game& game, Player& player, Shield shields[], int numberOfShields);
void DrawGame(const Game& game, const Player& player, Shield shields[], int numberOfShields, const AlienSwarm& aliens);
void MovePlayer(const Game& game, Player& player, int dx);
void PlayerShoot(Player& player);
void DrawPlayer(const Player& player, const char* sprite[]);
void UpdateMissile(Player& player);
void InitShields(const Game& game, Shield shields[], int numberOfShields);
void CleanUpShields(Shield shields[], int numberOfShields);
void DrawShields(const Shield shields[], int numberOfShields);
//Returns the shield index of which shield got, return NOT_IT_PLAY if nothing was hit, also returns the shield collision point 
int IsCollision(const Position& projectile, const Shield shields[], int numberOfShields, Position& shieldCollisionPoint);
void ResolveShieldCollision(Shield shields[], int shieldIndex, const Position& shieldCollisionPoint);
void InitAliens(const Game& game, AlienSwarm& aliens);
void DrawAliens(const AlienSwarm& aliens);

int main(){
  Game game;
  Player player;
  Shield shields[NUM_SHIELDS];
  AlienSwarm aliens;

  InitializeCurses(true);

  InitGame(game);
  InitPlayer(game, player);
  InitShields(game, shields, NUM_SHIELDS);
  InitAliens(game, aliens);

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

      UpdateGame(game, player, shields, NUM_SHIELDS);
      ClearScreen(); //curses utils 
      DrawGame(game, player, shields, NUM_SHIELDS, aliens);
      RefreshScreen(); //curses utils

      }
    }else{
      quit = true;
    }
  }

  CleanUpShields(shields, NUM_SHIELDS);
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

void UpdateGame(const Game& game, Player& player, Shield shields[], int numberOfShields){
  UpdateMissile(player);

  Position shieldCollisionPoint;
  int shieldIndex = IsCollision(player.missile, shields, numberOfShields, shieldCollisionPoint);
  if(shieldIndex != NOT_IN_PLAY){
    ResetMissile(player);
    ResolveShieldCollision(shields, shieldIndex, shieldCollisionPoint);
  }
}

void DrawGame(const Game& game, const Player& player, Shield shields[], int numberOfShields, const AlienSwarm& aliens){
  DrawPlayer(player, PLAYER_SPRITE);
  DrawShields(shields, numberOfShields);
  DrawAliens(aliens);
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

int IsCollision(const Position& projectile, const Shield shields[], int numberOfShields, Position& shieldCollisionPoint){
  shieldCollisionPoint.x = NOT_IN_PLAY;
  shieldCollisionPoint.y = NOT_IN_PLAY;

  if(projectile.y != NOT_IN_PLAY){
    for(int i = 0; i < numberOfShields; i++){
      const Shield& shield = shields[i];
      
      if(projectile.x >= shield.position.x && projectile.x < (shield.position.x + SHIELD_SPRITE_WIDTH)){
        if(projectile.y >= shield.position.y && projectile.y < (shield.position.y + SHIELD_SPRITE_HEIGHT)){
          if(shield.sprite[projectile.y - shield.position.y][projectile.x - shield.position.x] != ' '){
            std::string strProjectile = std::to_string(projectile.y);
            shieldCollisionPoint.x = projectile.x - shield.position.x;
            shieldCollisionPoint.y = projectile.y - shield.position.y;
            return i;
          }
        }
      }
    }
  }

  return NOT_IN_PLAY;
}

void ResolveShieldCollision(Shield shields[], int shieldIndex, const Position& shieldCollisionPoint){
  shields[shieldIndex].sprite[shieldCollisionPoint.y][shieldCollisionPoint.x] = ' ';
}

void InitAliens(const Game& game, AlienSwarm& aliens){
  for(int row = 0; row < NUM_ALIEN_ROWS; row++){
    for(int col = 0; col < NUM_ALIEN_COLUMNS; col++){
      aliens.aliens[row][col] = AS_ALIVE; 
    }
  }

  aliens.direction = 1; //right 
  aliens.numAliensLeft = NUM_ALIEN_ROWS * NUM_ALIEN_COLUMNS;
  aliens.animation = 0;
  aliens.spriteSize.width = ALIEN_SPRITE_WIDTH;
  aliens.spriteSize.height = ALIEN_SPRITE_HEIGHT;
  aliens.numberOfBombsInPlay = 0;
  aliens.position.x = (game.windowSize.width - NUM_ALIEN_COLUMNS * (aliens.spriteSize.width + ALIENS_X_PADDING)) / 2;
  aliens.position.y = game.windowSize.height - NUM_ALIEN_COLUMNS - NUM_ALIEN_ROWS * aliens.spriteSize.height - ALIENS_Y_PADDING * (NUM_ALIEN_ROWS -  1) - 3 + game.level;
  aliens.line = NUM_ALIEN_COLUMNS - (game.level - 1);
  aliens.explosionTimer = 0;

}

void DrawAliens(const AlienSwarm& aliens){
  const int NUM_30_POINT_ALIEN_ROWS = 1;
  const int NUM_20_POINT_ALIEN_ROWS = 2;
  const int NUM_10_POINT_ALIEN_ROWS = 2;

  //draw 1 row of the 30 point aliens 
  for(int col = 0; col < NUM_ALIEN_COLUMNS; col++){
    int xPos = aliens.position.x + col * (aliens.spriteSize.width + ALIENS_X_PADDING);
    int yPos = aliens.position.y;

    if(aliens.aliens[0][col] == AS_ALIVE){
      DrawSprite(xPos, yPos, ALIEN30_SPRITE, aliens.spriteSize.height);
    }
  }

  //draw 2 rows of the 20 point aliens 
  for(int row = 0; row < NUM_20_POINT_ALIEN_ROWS; row++){
    for(int col = 0; col < NUM_ALIEN_COLUMNS; col++){
      int xPos = aliens.position.x + col * (aliens.spriteSize.width + ALIENS_X_PADDING);
      int yPos = aliens.position.y + row * (aliens.spriteSize.height + ALIENS_Y_PADDING) + NUM_30_POINT_ALIEN_ROWS * (aliens.spriteSize.height + ALIENS_Y_PADDING);

      if(aliens.aliens[NUM_30_POINT_ALIEN_ROWS + row][col] == AS_ALIVE){
        DrawSprite(xPos, yPos, ALIEN20_SPRITE, aliens.spriteSize.height);
      }

    }
  }

  //draw 2 rows of the 10 points aliens
  for(int row = 0; row < NUM_10_POINT_ALIEN_ROWS; row++){
    for(int col = 0; col < NUM_ALIEN_COLUMNS; col++){
      int xPos = aliens.position.x + col * (aliens.spriteSize.width + ALIENS_X_PADDING);
      int yPos = aliens.position.y + row * (aliens.spriteSize.height + ALIENS_Y_PADDING) + NUM_30_POINT_ALIEN_ROWS * (aliens.spriteSize.height + ALIENS_Y_PADDING) + NUM_20_POINT_ALIEN_ROWS * (aliens.spriteSize.height + ALIENS_Y_PADDING);

      if(aliens.aliens[NUM_30_POINT_ALIEN_ROWS + NUM_20_POINT_ALIEN_ROWS + row][col] == AS_ALIVE){
        DrawSprite(xPos, yPos, ALIEN10_SPRITE, aliens.spriteSize.height);
      }

    }
  }
}
