#include <iostream>

class Fraction{
  public:
    Fraction();
    Fraction(int n, int d);

    int GetNumerator();
    int GetDenominator();

    void AddFraction(int n1, int d1, int n2, int d2, int& resultN, int& resultD);
    void SubFraction(int n1, int d1, int n2, int d2, int& resultN, int& resultD);
    void MultFraction(int n1, int d1, int n2, int d2, int& resultN, int& resultD);
    void DivFraction(int n1, int d1, int n2, int d2, int& resultN, int& resultD);
  private:
    int numerator;
    int denominator;
};

Fraction::Fraction(): Fraction(0, 1){}
Fraction::Fraction(int n, int d): numerator(n), denominator(d){}
int Fraction::GetNumerator(){
  return this->numerator;
}
int Fraction::GetDenominator(){
  return this->denominator;
}


int main( int argc , char **argv ){
  Fraction f(10, 20);
  return 0;
}

