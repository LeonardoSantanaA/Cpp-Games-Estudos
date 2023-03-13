#include <cstdlib>
#include <iostream>

typedef int type;

struct DynamicArray{
  type* dynamicArray;
  int capacity;
  int size;
};

type * CreateDynamicArray(int &capacity, int &size);
void DeleteDynamicArray(type* dynamicArray, int& size);
void InsertElement(type** dynamicArray, const int &element, int &size, int &capacity);
void DeleteElement(type* dynamicArray, const int &elementIndex, int &size);
void ResizeDynamicArray(type** dynamicArray, int &capacity, const int &newCapacity);
void PrintDynamicArray(type* dynamicArray, const int &capacity);

int main( int argc , char **argv ){
  int option = 0;
  DynamicArray array;

  std::cout << "Insert a capacity for your dynamic array: ";
  std::cin >> array.capacity;
  array.dynamicArray = CreateDynamicArray(array.capacity, array.size);
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
        DeleteDynamicArray(array.dynamicArray, array.size);
        std::exit(1);
        break; 
      }
      case 1:{
        type newElement = 0;
        std::cout << "Insert the value of the new element: ";
        std::cin >> newElement;
        std::cout << std::endl;
        InsertElement(&array.dynamicArray, newElement, array.size, array.capacity);
        break;  
      }
      case 2: {
        int index = 0;
        std::cout << "Insert the position of the element: ";
        std::cin >> index; 
        std::cout << std::endl; 
        DeleteElement(array.dynamicArray, index, array.size);
        break;
      }
      case 3: {
        PrintDynamicArray(array.dynamicArray, array.capacity);
        break;
      }
        default:{ 
        std::cout << "this options doesn't exists! Try again.\n";
      }
    }
  }while(option != 0);
  delete [] array.dynamicArray;

  return 0;
}

type * CreateDynamicArray(int &capacity, int &size){
  size = 0;
  type * arrayPtr = new int[capacity];
  return arrayPtr;
}

void DeleteDynamicArray(type* dynamicArray, int &size){
  size = 0;
  delete [] dynamicArray;
}

void InsertElement(type** dynamicArray, const int &element, int &size, int &capacity){
  if(capacity <= size)
    ResizeDynamicArray(dynamicArray, capacity, size + 1);
  (*dynamicArray)[size] = element;
  size++;
   
} 

void DeleteElement(type* dynamicArray, const int& elementIndex, int &size){
  for(int i = elementIndex; i < size; i++){
    if(i + 1 < size)
      dynamicArray[i] = dynamicArray[i + 1];
    else{
      size--;
      dynamicArray[i] = 0; 
    } 
  }
}

void ResizeDynamicArray(type** dynamicArray, int &capacity, const int& newCapacity){
  type * newArray = new type[newCapacity];
  capacity = newCapacity;
  for(int i = 0; i < capacity; i++){
    newArray[i] = (*dynamicArray)[i];
  }
  delete[] *dynamicArray;
  *dynamicArray = newArray;
}

void PrintDynamicArray(type* dynamicArray, const int &capacity){
  std::cout << "///////\n";
  for(int i = 0; i < capacity; i++){
    std::cout << "position[" << i << "] - " << dynamicArray[i] << ";\n";
  }
  std::cout << "///////\n";
}
