#include <iostream>

int main( int argc , char **argv ){
  int input = 0;

  std::cout << "Insert a number: ";
  std::cin >> input;
  
  for(int i = 0; i < input; i++){
    for(int j = 0; j < (input - i); j++){
      std::cout << ' ';
    }

    for(int j = 0; j < (2 * i + 1); j++){
      std::cout << '*';
    }
    std::cout << std::endl;
  }
  //inverto o for de cima:
  for(int i = input; i >= 0; i--){
   for(int j = 0; j < input - i; j++){
     std::cout << ' ';
   }
   
   for(int j = 0; j < 2 * i + 1; j++){
    std::cout << '*';
   }
    
    std::cout << std::endl;
  }

  return 0;
}

