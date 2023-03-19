#include <iostream>
#include <cstring>
#include "Utils.hpp"

enum{
  AIRCRAFT_CARRIER_SIZE = 5,
  BATTLESHIP_SIZE = 4,
  CRUISER_SIZE = 3,
  DESTROYER_SIZE = 3,
  SUBMARINE_SIZE = 2,

  BOARD_SIZE = 10,
  NUM_SHIPS = 5,
  PLAYER_NAME_SIZE = 8, //Player1, Player2
  MAX_SHIP_SIZE = AIRCRAFT_CARRIER_SIZE
};

enum ShipType{
  ST_NONE = 0,
  ST_AIRCRAFT_CARRIER,
  ST_BATTLESHIP,
  ST_CRUISER,
  ST_DESTROYER,
  ST_SUBMARINE
};

enum ShipOrientationType{
  SO_HORIZONTAL = 0,
  SO_VERTICAL
};

struct ShipPositionType{
  int row;
  int col;
};

struct Ship{
  ShipType shipType;
  int shipSize;
  ShipOrientationType orientation;
  ShipPositionType position;
};

enum GuessType{
  GT_NONE = 0,
  GT_MISSED,
  GT_HIT
};

struct ShipPartType{
  ShipType shipType;
  bool isHit;
};

struct Player{
  char playerName[PLAYER_NAME_SIZE];
  Ship ships[NUM_SHIPS];
  GuessType guessBoard[BOARD_SIZE][BOARD_SIZE];
  ShipPartType shipBoard[BOARD_SIZE][BOARD_SIZE];
};



void InitializePlayer(Player &player, const char* playerName);
void InitializeShip(Ship &ship, int shipSize, ShipType shipType);
void PlayGame(Player &player1, Player &player2);
bool WantToPlayAgain();
void SetupBoards(Player &player);
void ClearBoards(Player &player);
void DrawBoards(const Player &player);

int main( int argc , char **argv ){
  Player player1;
  Player player2;

  InitializePlayer(player1, "Player1");
  InitializePlayer(player2, "Player2");

  do{
    PlayGame(player1, player2);
  }while(WantToPlayAgain());

  return 0;
}

void InitializePlayer(Player &player, const char* playerName){
  if(playerName != nullptr && std::strlen(playerName) > 0){
    std::strcpy(player.playerName, playerName);
  }

  InitializeShip(player.ships[0], AIRCRAFT_CARRIER_SIZE, ST_AIRCRAFT_CARRIER);
  InitializeShip(player.ships[1], BATTLESHIP_SIZE, ST_BATTLESHIP);
  InitializeShip(player.ships[2], CRUISER_SIZE, ST_CRUISER);
  InitializeShip(player.ships[3], DESTROYER_SIZE, ST_DESTROYER);
  InitializeShip(player.ships[4], SUBMARINE_SIZE, ST_SUBMARINE);
}

void InitializeShip(Ship &ship, int shipSize, ShipType shipType){
  ship.shipType = shipType;
  ship.shipSize = shipSize;
  ship.position.row = 0;
  ship.position.col = 0;
  ship.orientation = SO_HORIZONTAL; 
}

void PlayGame(Player &player1, Player &player2){
  SetupBoards(player1);
  SetupBoards(player2);

}

bool WantToPlayAgain(){
  char input;

  const char validInput[2] = {'y', 'n'};

  input = GetCharacter("Would you like to player again? (y/n)", Utils::INPUT_ERROR_STRING, validInput, 2, Utils::CC_LOWER_CASE);

  return input == 'y';
}

void SetupBoards(Player &player){
  ClearBoards(player);
  
  DrawBoards(player);
}

void ClearBoards(Player& player){
  for(int r = 0; r < BOARD_SIZE; r++){
    for(int c = 0; c < BOARD_SIZE; c++){
      player.guessBoard[r][c] = GT_NONE;
      player.shipBoard[r][c].shipType = ST_NONE; //no ship here
      player.shipBoard[r][c].isHit = false;
    }
  }
}

void DrawSeparatorLine(){
  std::cout << " ";
  for(int c = 0; c < BOARD_SIZE; c++){
    std::cout << "+---";
  }
  std::cout << "+";
}

void DrawColumnsRow(){
  std::cout << "  ";
  for(int c = 0; c < BOARD_SIZE; c++){
    int columnName = c + 1;
    std::cout << " " << columnName << "  ";
  }
}

char GetShipRepresentation(const Player &player, int row, int col){
  if(player.shipBoard[row][col].isHit){
    return '*'; //represents hit 
  }

  if(player.shipBoard[row][col].shipType == ST_AIRCRAFT_CARRIER){
    return 'A';
  }else if(player.shipBoard[row][col].shipType == ST_BATTLESHIP){
    return 'B';
  }else if(player.shipBoard[row][col].shipType == ST_CRUISER){
    return 'C';
  }else if(player.shipBoard[row][col].shipType == ST_DESTROYER){
    return 'D';
  }else if(player.shipBoard[row][col].shipType == ST_SUBMARINE){
    return 'S';
  }else{
    return ' ';
  }
}

char GetGuessRepresentationAt(const Player &player, int row, int col){
  if(player.guessBoard[row][col] == GT_HIT){
    return '*';
  }else if(player.guessBoard[row][col] == GT_MISSED){
    return 'o';
  }else{
    return ' ';
  }
}

void DrawShipBoardRow(const Player &player, int row){
  char rowName = row + 'A'; //1 + 'A' = 'B' for example
  std::cout << rowName << '|';

  for(int c = 0; c < BOARD_SIZE; c++){
    std::cout << " " << GetShipRepresentation(player, row, c) << " |";
  }
}

void DrawGuessBoardRow(const Player &player, int row){
  char rowName = row + 'A'; //1 + 'A' = 'B' for example
  std::cout << rowName << '|';

  for(int c = 0; c < BOARD_SIZE; c++){
    std::cout << " " << GetGuessRepresentationAt(player, row, c) << " |";
  }
}

void DrawBoards(const Player &player){
  DrawColumnsRow();
  DrawColumnsRow();
  std::cout << std::endl;
  for(int r = 0; r < BOARD_SIZE; r++){
    DrawSeparatorLine();
    std::cout << " ";
    DrawSeparatorLine();
    std::cout << std::endl;
    DrawShipBoardRow(player, r);
    std::cout << " ";
    DrawGuessBoardRow(player, r);
   std::cout << std::endl;
  }
  DrawSeparatorLine();
  std::cout << " ";
  DrawSeparatorLine();
  std::cout << std::endl;
}
