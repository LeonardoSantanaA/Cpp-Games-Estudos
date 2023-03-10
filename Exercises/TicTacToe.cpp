#include <iostream>

void Game();
bool WantToPlayAgain();
void Draw();
void ChangePlayer(bool &player2);
int GetIndex(bool player2);
bool CheckAnswer(int answer);
void AddIndex(int answer);
void UpdateTable(int answer, bool player2);
bool GameOver();
bool verifyWinner();

char table[9];
int availableIndex[9];
int top = 0;

const int IGNORE_CHARS = 256;
const char *INPUT_ERROR_STRING = "Input error! Please try again.";

int main( int argc , char **argv ){
 do{
    Game();
 }while(WantToPlayAgain());
  return 0;
}

void Game(){
  bool failure;
  bool player2 = false;
  int answer;

  Draw();

  do{
    failure = false;

    answer = GetIndex(player2);
    UpdateTable(answer, player2);
    ChangePlayer(player2);

  }while(!GameOver() && !verifyWinner());
}

void Draw(){
  std::cout << "+---+---+---+\n";
  for(int i = 0; i < 9; i++){
    table[i] = ' ';
    if(i == 0 || i == 3 || i == 6){
      std::cout << "| " << i << " | ";
    }else if(i == 1 || i == 4 || i == 7){
      std:: cout << i << " | ";
    }else{
      std::cout << i << " |\n";
      std::cout << "+---+---+---+" << std::endl;
    }
  }
}

void ChangePlayer(bool &player2){
  player2 = !player2;
}

int GetIndex(bool player2){
  bool failure;
  int answer;
  std::string player = " ";
  do{
    failure = false;
    if(!player2)
      player = "Player 1";
    else
      player = "Player 2";
    std::cout << "[" << player << "]" << "Choose an index: ";
    std::cin >> answer;
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(IGNORE_CHARS, '\n');
      std::cout << INPUT_ERROR_STRING << std::endl;
      failure = true;
    }else{
      if(answer < 0 || answer > 8){
        std::cin.clear();
        std::cin.ignore(IGNORE_CHARS, '\n');
        std::cout << "You must type numbers of 0 to 8!" << std::endl;
        failure = true;
      }
      else if(!CheckAnswer(answer)){
        std::cin.clear();
        std::cin.ignore(IGNORE_CHARS, '\n');
        std::cout << "Choose another number, please." << std::endl;
        failure = true;
      }else{
        AddIndex(answer);
      }
    }
  }while(failure);
  return answer;
}

void AddIndex(int answer){
  availableIndex[top] = answer;
  top++;
}

bool CheckAnswer(int answer){
  if(table[answer] == ' '){
    return true;
  }
  return false;
}

void UpdateTable(int answer, bool player2){
  char symbol;
  char symbolTable;
  if(!player2)
    symbol = 'X';
  else 
    symbol = 'O';

  table[answer] = symbol;

  std::cout << "+---+---+---+\n";
  for(int i = 0; i < 9; i++){


    if(i == 0 || i == 3 || i == 6){
      std::cout << "| " << table[i] << " | ";
    }else if(i == 1 || i == 4 || i == 7){
      std:: cout << table[i] << " | ";
    }else{
      std::cout << table[i] << " |\n";
      std::cout << "+---+---+---+" << std::endl;
    }
    }
}

bool GameOver(){
  for(int i = 0; i < 9; i++){
    if(table[i] == ' ')
      return false;
  }
  std::cout << "Cat Game!" << std::endl;
  return true;
}

bool verifyWinner(){
  char currentSymbol = 'X';
  //HORIZONTAL
  if(table[0] == currentSymbol && table[1] == currentSymbol && table[2] == currentSymbol){
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }else if(table[3] == currentSymbol && table[4] == currentSymbol && table[5] == currentSymbol){
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }else if(table[6] == currentSymbol && table[7] == currentSymbol && table[8] == currentSymbol){
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }
  //VERTICAL
  if(table[0] == currentSymbol && table[3] == currentSymbol && table[6] == currentSymbol){
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }else if(table[1] == currentSymbol && table[4] == currentSymbol && table[7] == currentSymbol){
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }else if(table[2] == currentSymbol && table[5] == currentSymbol && table[8] == currentSymbol){
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }
  //DIAGONAL
  if(table[0] == currentSymbol && table[4] == currentSymbol && table[8] == currentSymbol){
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }else if(table[2] == currentSymbol && table[4] == currentSymbol && table[6] == currentSymbol){
    std::cout << "Player 1 wins!" << std::endl;
    return true;
  }

  currentSymbol = 'O';
  if(table[0] == currentSymbol && table[1] == currentSymbol && table[2] == currentSymbol){
    std::cout << "Player 2 wins!" << std::endl;
    return true;
  }else if(table[3] == currentSymbol && table[4] == currentSymbol && table[5] == currentSymbol){
    std::cout << "Player 2 wins!" << std::endl;
    return true;
  }else if(table[6] == currentSymbol && table[7] == currentSymbol && table[8] == currentSymbol){
    std::cout << "Player 2 wins!" << std::endl;
    return true;
  }
  //VERTICAL
  if(table[0] == currentSymbol && table[3] == currentSymbol && table[6] == currentSymbol){
    std::cout << "Player 2 wins!" << std::endl;
    return true;
  }else if(table[1] == currentSymbol && table[4] == currentSymbol && table[7] == currentSymbol){
    std::cout << "Player 2 wins!" << std::endl;
    return true;
  }else if(table[2] == currentSymbol && table[5] == currentSymbol && table[8] == currentSymbol){
    std::cout << "Player 2 wins!" << std::endl;
    return true;
  }
  //DIAGONAL
  if(table[0] == currentSymbol && table[4] == currentSymbol && table[8] == currentSymbol){
    std::cout << "Player 2 wins!" << std::endl;
    return true;
  }else if(table[2] == currentSymbol && table[4] == currentSymbol && table[6] == currentSymbol){
    std::cout << "Player 2 wins!" << std::endl;
    return true;
  }

  return false;
}

bool WantToPlayAgain(){
 bool failure;  
 char answer;
 do{
  failure = false;
  std::cout << "Do you wanna continue[y/n]? ";
  std::cin >> answer;
  if(std::cin.fail()){
    std::cin.clear();
    std::cin.ignore(IGNORE_CHARS, '\n');
    std::cout << INPUT_ERROR_STRING << std::endl;
    failure = true;
  }else{
    answer = std::tolower(answer);
  }
 }while(failure);
 if(answer == 'y') {
  for(int i = 0; i < 9; i++){
    table[i] = ' ';
  }
 }
 return answer == 'y';
}
