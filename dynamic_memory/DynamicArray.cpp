#include <exception>
#include <iostream>
#include <cassert>
#include <new>

class DynamicIntArray{
public:
  DynamicIntArray():moptrData(nullptr), mSize(0), mCapacity(0){}
  DynamicIntArray(const DynamicIntArray& otherArray);
  DynamicIntArray& operator=(const DynamicIntArray& otherArray);
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
  static const size_t RESIZE_MULTIPLIER = 2;
};

DynamicIntArray::~DynamicIntArray(){
  delete [] moptrData;
  moptrData = nullptr;
}

DynamicIntArray::DynamicIntArray(const DynamicIntArray& otherArray){
  bool result = Init(otherArray.mCapacity);
  assert(result);

  mSize = otherArray.mSize;

  for(size_t i = 0; i < mSize; i++){
    moptrData[i] = otherArray.moptrData[i];
  }
}

DynamicIntArray& DynamicIntArray::operator=(const DynamicIntArray& otherArray){
  if(this == &otherArray){
    return *this;
  }
  if(moptrData != nullptr){
    delete [] moptrData;
  }

  bool result = Init(otherArray.mCapacity);
  assert(result);

  for(size_t i = 0; i < mSize; i++){
    moptrData[i] = otherArray.moptrData[i];
  }

  return *this;
}

bool DynamicIntArray::Init(size_t capacity){
  if(capacity == 0){
    return false;
  }

  if(mCapacity == capacity){
    return true;
  }

  if(moptrData){
    delete [] moptrData;
    moptrData = nullptr;
    mSize = 0;
    mCapacity = 0;
  }

  moptrData = new (std::nothrow) int[capacity];
  if(!moptrData){
    return false;
  }
  mSize = 0;
  mCapacity = capacity;
  return true;
}

bool DynamicIntArray::Reserve(size_t capacity){
  if(mCapacity < capacity){
    //do the re-allocation
    int *oldData = moptrData;

    moptrData = new (std::nothrow) int[capacity];
    if(!moptrData){
      moptrData = oldData;
      return false;
    }

    mCapacity = capacity;

    for(size_t i = 0; i < mSize; ++i){
      moptrData[i] = oldData[i];
    }

    delete [] oldData;
  }

  return true;
}

bool DynamicIntArray::Resize(size_t newSize){
  if(mCapacity < newSize){
    //need to reallocate
    bool reserveSucceeded = Reserve(newSize);
    if(!reserveSucceeded){
      return reserveSucceeded;
    }
  }

  for(size_t i = mSize; i < newSize; ++i){
    moptrData[i] = 0;
  }

  mSize = newSize;

  return true;
}

bool DynamicIntArray::PushBack(int newVal){
  assert(moptrData && "Has not been Initialized - call Init()");
  if(!moptrData){
    return false;
  }

  if(mSize + 1 > mCapacity){
    bool reserveResult = Reserve(mCapacity * RESIZE_MULTIPLIER);
    if(!reserveResult){
      return false;
    }
  }

  moptrData[mSize++] = newVal;

  return true;
}

bool DynamicIntArray::PopBack(int& value){
  assert(moptrData && "Has not been Initialized - call Init()");
  if(!moptrData){
    return false;
  }

  if(mSize > 0){
    value = moptrData[--mSize];
    return true;
  }

  return false;
}

const int& DynamicIntArray::operator[](size_t index) const{
  assert(moptrData && index < mSize);
  return moptrData[index];
}

int& DynamicIntArray::operator[](size_t index){
  assert(moptrData && index < mSize);
  return moptrData[index];
}

int main( int argc , char **argv ){
  DynamicIntArray *intArray = new DynamicIntArray;
  delete intArray;

  std::cout << "Dynamic Memory!" << std::endl;

  return 0;
}

