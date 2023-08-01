#include <iostream>

class String{
  public:
    String(char* str){
      this->str = (char*)str;
    }
    String():str((char*)"Hello"){}

    inline int GetLength();

    friend void operator<<(std::ostream& consoleOut, String& string){
      for(int i = 0; i < string.GetLength(); i++){
        consoleOut << string.str[i];
      }
    }

  private:
    char* str;
};

int String::GetLength(){
  int i = 0;
  while(str[i] != '\0'){
    i++;
  }
  return i;
}

int main( int argc , char **argv ){
  //String string((char*)"Holla");
  String string;
  std::cout << string;
  return 0;
}

