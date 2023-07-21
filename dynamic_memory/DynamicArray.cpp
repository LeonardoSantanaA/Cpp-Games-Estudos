#include <iostream>
#include <cassert>

class DynamicIntArray{
public:
  DynamicIntArray():moptrData(nullptr), mSize(0), mCapacity(0){}
  DynamicIntArray(const DynamicIntArray& otherArray);
  //should clean up the memory
  ~DynamicIntArray();

  inline size_t Size() const {return mSize;}
  inline size_t Capacity() const {return mCapacity;}

  //Allocates the dynamic array 
  bool Init(size_t capacity = INITIAL_CAPACITY);

  bool Reserve(size_t capacity);

  bool Resize(size_t newSize);

  bool PushBack(int newVal);
  bool PopBack(int& value);

  const int& operator[](size_t index) const;
  int& operator[](size_t index);

private:
  int* moptrData;
  size_t mSize;
  size_t mCapacity;

  static const size_t INITIAL_CAPACITY = 10;
};

DynamicIntArray::DynamicIntArray(const DynamicIntArray& otherArray){
  bool result = Init(otherArray.mCapacity);
  assert(result);

  mSize = otherArray.mSize;

  for(size_t i = 0; i < mSize; i++){
    moptrData[i] = otherArray.moptrData[i];
  }
}

int main( int argc , char **argv ){
  return 0;
}

