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

    ~String(){
      this->str = nullptr;
      delete[] str;
    }

    inline int GetLength();

    friend std::ostream& operator<<(std::ostream& consoleOut, String& string){
      for(int i = 0; i < string.GetLength() + 1; i++){
        std::cout << string.str[i];
      }
      return consoleOut;
    }

    String operator+(String& otherString);
    bool operator==(String& otherString);
    char operator[](int index);

    int substr(const char* substr);
    String substr(int indexStart, int length);
    String cpstr(String& otherStr);

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
  return i - 1;
}

int String::GetLength(){
  int i = 0;
  if(length == 0){
    i = VerifyLength();
  }else{
    return length;
  }
  return i - 1;
}

String String::operator+(String& otherString){
  int newLength = this->GetLength() + otherString.GetLength() + 1;
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

char String::operator[](int index){
  try{
    if(index > this->GetLength() || this->str[index] == '\0'){
      throw "Out of index!";
    }else{
      return this->str[index];
    }
  }catch(const char* error){
    std::cerr << error;
    return -1;
  }
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
  try{
    if(length < 0){
      throw "ERROR: The length is less than zero!";
    }

    if(length > this->GetLength()){
      throw "ERROR: The length is less than string length!";
    }

    if(indexStart > length){
      throw "ERROR: The start index is greater than length!";
    }

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
    std::cerr << e;
    return 0;
  }
}

String String::cpstr(String& otherStr){
  char* oldStr = this->str;
  oldStr = nullptr;
  delete[] oldStr;
  this->str = new char[otherStr.GetLength() + 1];
  for(int i = 0; i < this->GetLength() + 1; i++){
    this->str[i] = otherStr.str[i]; 
  }
  return *this;
}

int main( int argc , char **argv ){
  //String string((char*)"Hollba");
  String string1 = "Lekaum ";
  String string2 = "Lbkaum ";
  int indexSubstr = string2.substr("um");
  String string3 = "Santana";
  String string4 = string2.substr(4, 6);
  String string5 = string1 + string3;

  if(string1 == string2){
    std::cout << "is equal!" << std::endl;
  }else{
    std::cout << "inst equal!" << std::endl;
  }
  std::cout << string1[2] << std::endl;
  std::cout << "index of substr: " << indexSubstr << std::endl;
  std::cout << "my name: " << string5 << std::endl;

  //std::cout << nome;
  std::cout << "before copy: " << string2 << std::endl;
  string2.cpstr(string4);
  std::cout << "after copy " << string4 << ": " << string2 << std::endl;
  return 0;
}

