#include <iostream>

void insert(int array1[], int size, int value, int position);

int main( int argc , char **argv ){
  int array1[] = {10, 20, 30, 40, 50};
  try{
  insert(array1, 5, 25, 3);
  }catch(const char* error){
  std::cerr << error << std::endl;
  }
  return 0;
}

void insert(int array1[], int size, int value, int position){
  if(position > size + 1 || position < 1)
    throw "Impossible.";
 
  --position;
  int arrayResult[size + 1];

  //copy array1 values to arrayResult before the position
  for(int i = 0; i < position; i++){
    arrayResult[i] = array1[i];
  }

  //copy array1 values to arrayResult after the position and increments the value to array in position
  for(int i = position; i < size + 1; i++){
    if(i == position){
      arrayResult[i] = value;
    }else{
      arrayResult[i] = array1[i - 1];
   }
  }

  std::cout << "array after insert: ";
  for(int i = 0; i < size + 1; i++){
    std::cout << " " << arrayResult[i];
  }
  std::cout << std::endl;
}
