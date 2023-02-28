#include <cctype>
#include <iostream>

void play();
void changePlayer();
void showAvailableNumbers();
bool wantPlayAgain();
void verifyNumberGame();
void gameWin(bool &);
void reset();
int numberChoosed, lastNumber, numberGame = 8;
bool player2, playAgain = true;

const int IGNORE_CHARS = 256;

int main( int argc , char **argv ){

  do{
    play();
  }while(playAgain);

  std::cout << "Goodbye!" << std::endl;

  return 0;
}

void play(){
  bool failure;

  do{
    failure = false;

    std::cout << "Choose a number from 1 to 3: ";
    std::cin >> numberChoosed;

    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(IGNORE_CHARS, '\n');
      std::cout << "Input error! Please try again.\n";
      failure = true;
    }else{
      if(numberChoosed < 1 || numberChoosed > 3){
        std::cout << "You must choose a number from 1 to 3!\n";
        failure = true;
      }else if(numberChoosed == lastNumber){
        std::cout << "You must choose a different number of " << lastNumber << "!\n";
        failure = true;
      }else{
        changePlayer();
        showAvailableNumbers();
        verifyNumberGame();
      }
    }
  }while(failure);
}

void changePlayer(){
  player2 = !player2;
  std::cout << "_________\n";
  if(player2){
    std::cout << "Current player: 2\n";
  }else{
    std::cout << "Current player: 1\n";
  }
  std::cout << "---------\n";
}

void showAvailableNumbers(){
  std::string numbersStr;
  lastNumber = numberChoosed;
  switch(numberChoosed){
    case 1:
      numbersStr = "2, 3";
      break;

    case 2:
      numbersStr = "1, 3";
      break;

    case 3:
      numbersStr = "1, 2";
      break;
    default:
      numbersStr = "1, 2, 3";
      break;
  }
  std::cout << "//Numbers Available: " << numbersStr << "//\n";
}

void verifyNumberGame(){
  numberGame -= numberChoosed;
  if(numberGame == 0){
    gameWin(player2);
  } 
  if(numberGame < 0){
    player2 = !player2;
    gameWin(player2);
  } 
}

void gameWin(bool &player2){
  if(player2){
    std::cout << "\n\n*****Player 2 wins!*****\n\n";
  }else{
    std::cout << "\n\n****Player 1 wins!****\n\n";
  }
  reset();
  wantPlayAgain();
}

bool wantPlayAgain(){
  bool failure = false;
  char answer = ' ';
  do{
    failure = false;

    std::cout << "Do you wanna play again? (y/n)\n";
    std::cin >> answer;

    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(IGNORE_CHARS, '\n');
      std::cout << "Input error! Please try again.\n";
      failure = true;
    }else{
      std::cin.ignore(IGNORE_CHARS, '\n');
      answer = std::tolower(answer);
      answer == 'y'? playAgain = true : playAgain = false;
    }
  }while(failure);
  return playAgain;
}

void reset(){
  numberGame = 8;
  numberChoosed = 0;
  lastNumber = 0;
  changePlayer();
}
