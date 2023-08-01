#include <iostream>

class String{
  public:
    String(char* str){
      this->str = (char*)str;
      this->length = GetLength();
    }
    String():str((char*)"Hello"), length(5){}
    String(int length){
      str = new char[length];
    }
    //~String(){
      //delete str;
    //}

    inline int GetLength();

    friend void operator<<(std::ostream& consoleOut, String& string){
      for(int i = 0; i < string.GetLength() + 1; i++){
        consoleOut << string.str[i];
      }
    }

    String operator+(String& otherString);


  private:
    char* str;
    int length = 0;
};

int String::GetLength(){
  int i = 0;
  if(length == 0){
    while(str[i] != '\0'){
      i++;
    }
  }else{
    return length;
  }
  return i;
}

String String::operator+(String& otherString){
  int newLength = this->GetLength() + otherString.GetLength();
  std::cout << "tamanho novo: " << newLength << std::endl;
  int lastIndex = 0;
  String newString(newLength);
  
  std::cout << *this;
  std::cout << " + ";
  std::cout << otherString;
  std::cout << " = ";
  std::cout << std::endl;

  for(int i = 0; i < newLength; i++){
    if(i <= this->GetLength()){
      newString.str[i] = this->str[i];
   }else{
      lastIndex = i;
      std::cout << "lastIndex: " << lastIndex << std::endl;
      break;
    }
  }
  int index = 0;
  for(int i = lastIndex; i <= newLength; i++){
    newString.str[i] = otherString.str[index];
    //std::cout << newString.str[i];
    index++;
  }
  return newString;
}


int main( int argc , char **argv ){
  String string((char*)"Holla");
  String string2;
  String newString = string + string2;
  //std::cout << string;
  //std::cout << std::endl;
  //std::cout << string2;
  //std::cout << std::endl;
  std::cout << "tamanho: " << newString.GetLength() << std::endl;
  std::cout << newString;
  return 0;
}

