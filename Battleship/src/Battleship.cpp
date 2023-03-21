#include <iostream>
#include <cstring>
#include "./includes/Utils.hpp"

enum{
  AIRCRAFT_CARRIER_SIZE = 5,
  BATTLESHIP_SIZE = 4,
  CRUISER_SIZE = 3,
  DESTROYER_SIZE = 3,
  SUBMARINE_SIZE = 2,

  BOARD_SIZE = 10,
  NUM_SHIPS = 5,
  PLAYER_NAME_SIZE = 10, //Player1, Player2
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
void DrawSeparatorLine();
void DrawColumnRow();
void DrawShipBoardRow(const Player &player, int row);
void DrawGuessBoardRow(const Player &player, int row);
char GetGuessRepresentationAt(const Player &player, int row, int col);
char GetShipRepresentationAt(const Player &player, int row, int col);
const char *GetShipNameForShipType(ShipType shipType);
ShipPositionType GetBoardPosition();
ShipPositionType MapBoardPosition(char rowInput, int colInput);
ShipOrientationType GetShipOrientation();
bool IsValidPlacement(const Player &player, const Ship &currentShip, const ShipPositionType &shipPosition, ShipOrientationType orientation);
void PlaceShipOnBoard(Player &player, Ship &currentShip, const ShipPositionType &shipPosition, ShipOrientationType orientation);

int main( int argc , char **argv ){
  Player player1;
  Player player2;

  InitializePlayer(player1, "[Player1] ");
  InitializePlayer(player2, "[Player2] ");

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

const char *GetShipNameForShipType(ShipType shipType){
  if(shipType == ST_AIRCRAFT_CARRIER)
    return "Aircrafter Carrier";
  else if(shipType == ST_BATTLESHIP)
    return "Battleship";
  else if(shipType == ST_CRUISER)
    return "Cruiser";
  else if(shipType == ST_DESTROYER)
    return "Destroyer";
  else if(shipType == ST_SUBMARINE)
    return "Submarine"; 
  return "None";
}

bool IsValidPlacement(const Player &player, const Ship &currentShip, const ShipPositionType &shipPosition, ShipOrientationType orientation){
  if(orientation == SO_HORIZONTAL){
    for(int c = shipPosition.col; c < (shipPosition.col + currentShip.shipSize); c++){
      if(player.shipBoard[shipPosition.row][c].shipType != ST_NONE || c >= BOARD_SIZE)
        return false;
    }
  }else{
    for(int r = shipPosition.row; r < (shipPosition.row + currentShip.shipSize); r++){
      if(player.shipBoard[r][shipPosition.col].shipType != ST_NONE || r >= BOARD_SIZE)
        return false;
    }
  }
  return true;
}

void PlaceShipOnBoard(Player &player, Ship &currentShip, const ShipPositionType &shipPosition, ShipOrientationType orientation){
  currentShip.position = shipPosition;
  currentShip.orientation = orientation;

  if(orientation == SO_HORIZONTAL){
    for(int c = shipPosition.col; c < (shipPosition.col + currentShip.shipSize); c++){
      player.shipBoard[shipPosition.row][c].shipType = currentShip.shipType;
      player.shipBoard[shipPosition.row][c].isHit = false;
    }
  }else{
    for(int r = shipPosition.row; r < (shipPosition.row + currentShip.shipSize); r++){
      player.shipBoard[r][shipPosition.col].shipType = currentShip.shipType;
      player.shipBoard[r][shipPosition.col].isHit = false;
    }
  }
}

ShipPositionType MapBoardPosition(char rowInput, int colInput){
  int realRow = rowInput - 'A';
  int realCol = colInput - 1;

  ShipPositionType boardPosition;

  boardPosition.row = realRow;
  boardPosition.col = realCol;

  return boardPosition;
}

ShipPositionType GetBoardPosition(){
  char rowInput;
  int colInput;

  const char validRowsInputs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}; 
  const int validColumnsInputs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  rowInput = GetCharacter("Please input a row (A - J): ", Utils::INPUT_ERROR_STRING, validRowsInputs, BOARD_SIZE, Utils::CC_UPPER_CASE);
  colInput = GetInteger("Please input a column (1 - 10): ", Utils::INPUT_ERROR_STRING, validColumnsInputs, BOARD_SIZE);

  return MapBoardPosition(rowInput, colInput);
}

ShipOrientationType GetShipOrientation(){
  ShipOrientationType orientation;
  const char validInput[2] = {'H', 'V'};
  char input = GetCharacter("Please choose a orientation (H) for Horizontal or (V) for Vertical: ", Utils::INPUT_ERROR_STRING, validInput, 2, Utils::CC_UPPER_CASE);
  
  if(input == validInput[0])
    return SO_HORIZONTAL;
  else
    return SO_VERTICAL;
}

void SetupBoards(Player &player){
  ClearBoards(player);
  
  for(int i = 0; i < NUM_SHIPS; i++){
    DrawBoards(player);
    Ship &currentShip = player.ships[i];
    ShipPositionType shipPosition;
    ShipOrientationType orientation;

    bool isValidPlacement = false;

    do{
      std::cout << player.playerName << "please set the position and orientation for your " << GetShipNameForShipType(currentShip.shipType) << std::endl;
      
      shipPosition = GetBoardPosition();
      orientation = GetShipOrientation();

      isValidPlacement = IsValidPlacement(player, currentShip, shipPosition, orientation);

      if(!isValidPlacement){
        std::cout << "That was not a valid placement. Please try again." << std::endl;
      }

    }while(!isValidPlacement);

    PlaceShipOnBoard(player, currentShip, shipPosition, orientation);
  }
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

char GetShipRepresentationAt(const Player &player, int row, int col){
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
    std::cout << " " << GetShipRepresentationAt(player, row, c) << " |";
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


