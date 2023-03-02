#include <iostream>

void deleteElement(int array1[], int size, int position);

int main( int argc , char **argv ){
  int array1[] = {10, 20, 30, 40, 50};
  try{
    deleteElement(array1, 5, 3);
  }catch(const char* error){
    std::cerr << error << std::endl;
  }
  return 0;
}

void deleteElement(int array1[], int size, int position){
  if(position > size || position < 1)
    throw "Impossible.";
 
  --position;
  int arrayResult[size - 1];

  //copy array1 values to arrayResult before the position
  for(int i = 0; i < position; i++){
    arrayResult[i] = array1[i];
  }

  for(int i = position + 1; i < size; i++){
      arrayResult[i - 1] = array1[i];
  }

  std::cout << "array after insert: ";
  for(int i = 0; i < size - 1; i++){
    std::cout << " " << arrayResult[i];
  }
  std::cout << std::endl;
}
