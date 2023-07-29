#include <iostream>

class String{
  public:
  String():str(""), size(0){}
  String(const String& otherStr);
  String& operator+(const String& otherStr);

  private:
  int size = 0;
  char* str;
};


int main( int argc , char **argv ){
  std::cout << "Olá, Mundo!" << '\n';
  return 0;
}

