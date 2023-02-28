#include <iostream>

void swap(int *, int *);

int main( int argc , char **argv ){
 int num1 = 5;
 int num2 = 10;

  swap(&num1, &num2);
  std::cout << "valor num1: " << num1 << "\nvalor num2 : " << num2 << std::endl;
  return 0;
}

void swap(int * n1, int * n2){
 int temp = 0;
 temp = *n1;
 *n1 = *n2;
 *n2 = temp;
}

