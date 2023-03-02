#include <iostream>

void copyArray(int array1[], int array2[], int);

int main( int argc , char **argv ){
  int array1[] = {1, 2, 3, 4, 5};
  int array2[5];
  copyArray(array1, array2, 5);
  return 0;
}

void copyArray(int a1[], int a2[], int size){
  int temp[size];

  std::cout << "array 2 values before copy: ";
  for(int i = 0; i < size; i++){
  std::cout << " " << a2[i];
  }
  std::cout << std::endl;

  for(int i = 0; i < size; i++){
   temp[i] = a1[i];
   a2[i] = a1[i];
   a1[i] = temp[i];
  }

  std::cout << "array 1 values: ";
  for(int i = 0; i < size; i++){
  std::cout << " " << a1[i];
  }
  std::cout << std::endl;

  std::cout << "array 2 values after copy: ";
  for(int i = 0; i < size; i++){
  std::cout << " " << a2[i];
  }
  std::cout << std::endl;
}
