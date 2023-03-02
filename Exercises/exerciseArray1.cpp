#include <iostream>

const char* reverse(char[], int);

int main( int argc , char **argv ){
  char cString[] = "Hello Good morninG bro";
  std::cout << reverse(cString, 21) << std::endl;

  return 0;
}

const char* reverse(char str[], int length){
  char* revertStr;
  int index = 0;
  //*revertStr = *(str + (length - index));
  //*(revertStr + 1) = *(str + (length - index)); 
  
  while(length >= 0){
    *(revertStr + index) = *(str + length);
    length--;
    index++;
  }

  return revertStr;
}

