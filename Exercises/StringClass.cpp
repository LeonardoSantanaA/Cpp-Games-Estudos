#include <iostream>

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
        consoleOut << string.str[i];
      }
    }

    String operator+(String& otherString);
    bool operator==(String& otherString);

    int substr(const String& substr);

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
  std::cout << "tamanho novo: " << newLength << std::endl;
  int lastIndex = 0;
  String newString(newLength);
  
  for(int i = 0; i < newLength; i++){
    if(this->str[i] != '\0'){
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
    index++;
  }

  return newString;
}


bool String::operator==(String& otherString){
  if(this->GetLength() == otherString.GetLength()){
    for(int i = 0; i < this->GetLength(); i++){
      if((this->str[i] == otherString.str[i]) && this->str[i] != '\0'){
        //std::cout << this->str[i] << " é igual de " << otherString.str[i] << std::endl;
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

int String::substr(const String& substr){

}

int main( int argc , char **argv ){
  String string((char*)"Hollba");
  String string2 = "Lekaum ";
  String string3 = "Santana";
  String nome = string2 + string3;
  if(string == string2){
    std::cout << "is equal!" << std::endl;
  }else{
    std::cout << "inst equal!" << std::endl;
  }
  std::cout << nome;
  //std::cout << std::endl;
  //std::cout << string2;
  //std::cout << std::endl;
  //std::cout << string;
  return 0;
}

