#include <cstdlib>
#include <iostream>

int * CreateDynamicArray(int &capacity, int &size);
void DeleteDynamicArray(int* dynamicArray, int& size);
void InsertElement(int** dynamicArray, int element, int &size, int &capacity);
void DeleteElement(int* dynamicArray, int elementIndex, int &size);
void ResizeDynamicArray(int** dynamicArray, int &capacity, int newCapacity);
void PrintDynamicArray(int* dynamicArray, int &capacity);

int main( int argc , char **argv ){
  int capacity = 0, size = 0, option = 0;

  std::cout << "Insert a capacity for your dynamic array: ";
  std::cin >> capacity;
  int * dynamicArray = CreateDynamicArray(capacity, size);
  std::cout << std::endl;
  std::cout << "Dynamic Array created! Tell me what you wanna do:\n";
  do{
    std::cout << "0 - exit\n";
    std::cout << "1 - insert an element\n";
    std::cout << "2 - delete an element\n";
    std::cout << "3 - print array\n";
    std::cout << "Your option: ";
    std::cin >> option;
    std::cout << std::endl;
    switch(option){
      case 0:{
        DeleteDynamicArray(dynamicArray, size);
        std::exit(1);
        break; 
      }
      case 1:{
        int newElement = 0;
        std::cout << "Insert the value of the new element: ";
        std::cin >> newElement;
        std::cout << std::endl;
        InsertElement(&dynamicArray, newElement, size, capacity);
        break;  
      }
      case 2: {
        int index = 0;
        std::cout << "Insert the position of the element: ";
        std::cin >> index; 
        std::cout << std::endl; 
        DeleteElement(dynamicArray, index, size);
        break;
      }
      case 3: {
        PrintDynamicArray(dynamicArray, capacity);
        break;
      }
        default:{ 
        std::cout << "this options doesn't exists! Try again.\n";
      }
    }
  }while(option != 0);
  delete [] dynamicArray;

  return 0;
}

int * CreateDynamicArray(int &capacity, int &size){
  size = 0;
  int * arrayPtr = new int[capacity];
  return arrayPtr;
}

void DeleteDynamicArray(int* dynamicArray, int &size){
  size = 0;
  delete [] dynamicArray;
}

void InsertElement(int** dynamicArray, int element, int &size, int &capacity){
  if(capacity <= size)
    ResizeDynamicArray(dynamicArray, capacity, size + 1);
  (*dynamicArray)[size] = element;
  size++;
   
} 

void DeleteElement(int* dynamicArray, int elementIndex, int &size){
  for(int i = elementIndex; i < size; i++){
    if(i + 1 < size)
      dynamicArray[i] = dynamicArray[i + 1];
    else{
      size--;
      dynamicArray[i] = 0; 
    } 
  }
}

void ResizeDynamicArray(int** dynamicArray, int &capacity,int newCapacity){
  int * newArray = new int[newCapacity];
  capacity = newCapacity;
  for(int i = 0; i < capacity; i++){
    newArray[i] = (*dynamicArray)[i];
  }
  delete[] *dynamicArray;
  *dynamicArray = newArray;
}

void PrintDynamicArray(int* dynamicArray, int &capacity){
  std::cout << "///////\n";
  for(int i = 0; i < capacity; i++){
    std::cout << "position[" << i << "] - " << dynamicArray[i] << ";\n";
  }
  std::cout << "///////\n";
}
