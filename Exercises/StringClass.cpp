#include <iostream>

namespace UtilsStr{
  int CheckLength(const char* str);
};

int UtilsStr::CheckLength(const char* str){
int i = 0;
  while(str[i] != '\0'){
    i++;
  }
  return i;
}

class String{
  public:
    String(const char* str){
      this->str = (char*)str;
      this->length = VerifyLength();
    }

    String():str((char*)"Hello"), length(5){}

    String(int length){
      str = new char[length];
      this->length = length;
    }

    inline int GetLength();

    friend void operator<<(std::ostream& consoleOut, String& string){
      for(int i = 0; i < string.GetLength() + 1; i++){
        std::cout << string.str[i];
      }
    }

    String operator+(String& otherString);
    bool operator==(String& otherString);

    int substr(const char* substr);
    String substr(int indexStart, int length);

  private:
    char* str;
    int length = 0;

    inline int VerifyLength();
};

inline int String::VerifyLength(){
  int i = 0;
  while(str[i] != '\0'){
    i++;
  }
  return i;
}

int String::GetLength(){
  int i = 0;
  if(length == 0){
    i = VerifyLength();
  }else{
    return length;
  }
  return i;
}

String String::operator+(String& otherString){
  int newLength = this->GetLength() + otherString.GetLength();
  //std::cout << "tamanho novo: " << newLength << std::endl;
  int lastIndex = 0;
  String newString(newLength);
  
  for(int i = 0; i < newLength; i++){
    if(this->str[i] != '\0'){
      newString.str[i] = this->str[i];
   }else{
      lastIndex = i;
      //std::cout << "lastIndex: " << lastIndex << std::endl;
      break;
    }
  }
  int index = 0;
  for(int i = lastIndex; i <= newLength; i++){
    newString.str[i] = otherString.str[index];
    index++;
  }

  return newString;
}


bool String::operator==(String& otherString){
  if(this->GetLength() == otherString.GetLength()){
    for(int i = 0; i < this->GetLength(); i++){
      if((this->str[i] == otherString.str[i]) && this->str[i] != '\0'){
        continue;
      }else{
        return false;
      }
    }
  }else{
    return false;
  }

   return true; 
}

int String::substr(const char* substr){
  int indexStr = 0;
  int indexSubStr = 0;
  int firstIndexSubStr = 0;
  int lastIndexSubStr = UtilsStr::CheckLength(substr);

  while(this->str[indexStr] != '\0'){
    if(this->str[indexStr] == substr[indexSubStr]){
      if(indexSubStr == 0){
        firstIndexSubStr = indexStr;
      }
      indexSubStr++;
      if(indexSubStr == lastIndexSubStr){
        return firstIndexSubStr;
      }
    }else{
      indexSubStr = 0;
    }
    indexStr++;
  }
  return -1;
}

String String::substr(int indexStart, int length){
  if(this->GetLength() < length){
    std::cout << "ERROR: The length is less than string length!" << std::endl;
    return *this;
  }
  try{
    String newString(length);
    int indexNewString = 0;
    for(int i = indexStart; i <= length; i++){
        newString.str[indexNewString] = this->str[i];  
        if(indexNewString > newString.GetLength()){
          break;
        }
        indexNewString++;
    }
    return newString;
  }catch(const char* e){
    std::cout << "ERROR! Look at the substr function!" << std::endl;
    return *this;
  }
}

int main( int argc , char **argv ){
  String string((char*)"Hollba");
  String string2 = "Lekaum ";
  //int indexSubstr = string2.substr("um");
  String string3 = "Santana";
  String string4 = string3.substr(1, 7);
  //if(string == string2){
    //std::cout << "is equal!" << std::endl;
  //}else{
    //std::cout << "inst equal!" << std::endl;
  //}
  //std::cout << nome;
  std::cout << string4;
  //std::cout << std::endl;
  //std::cout << string2;
  //std::cout << std::endl;
  //std::cout << string;
  return 0;
}

