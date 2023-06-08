#include <iostream>

class Fraction{
  public:
    Fraction();
    Fraction(int n, int d);

    int GetNumerator();
    int GetDenominator();
    void SetNumerator(int n);
    void SetDenominator(int d);

    void AddFraction(Fraction& f1, Fraction& f2);
    void SubFraction(Fraction& f1, Fraction& f2);
    void MultFraction(Fraction& f1, Fraction& f2);
    void DivFraction(Fraction& f1, Fraction& f2);
    void PrintFraction();

  private:
    int numerator;
    int denominator;
    void SimpFraction(Fraction& f);
    void CompareFraction(Fraction& f1, Fraction& f2); 
};

Fraction::Fraction(): Fraction(0, 1){}

Fraction::Fraction(int n, int d): numerator(n), denominator(d){}

int Fraction::GetNumerator(){
  return this->numerator;
}
int Fraction::GetDenominator(){
  return this->denominator;
}
void Fraction::SetNumerator(int n){
  this->numerator = n;
}
void Fraction::SetDenominator(int d){
  this->denominator = d;
}

void Fraction::AddFraction(Fraction& f1, Fraction& f2){
  Fraction resultF;
  if(f1.GetDenominator() == f2.GetDenominator()){
    resultF.SetNumerator(f1.GetNumerator() + f2.GetNumerator());
    resultF.SetDenominator(f1.GetDenominator());
  }else{
    resultF.SetNumerator((f1.GetNumerator() * f2.GetDenominator()) + (f2.GetNumerator() * f1.GetDenominator()));
    resultF.SetDenominator(f1.GetDenominator() * f2.GetDenominator());
  }
  f1.PrintFraction();
  std::cout << " + ";
  f2.PrintFraction();
  std::cout << " = ";
  resultF.PrintFraction();

  SimpFraction(resultF);
  std::cout << " -> ";
  resultF.PrintFraction();
  std::cout << std::endl;
  CompareFraction(f1, f2);
}

void Fraction::SubFraction(Fraction& f1, Fraction& f2){
   Fraction resultF;
  if(f1.GetDenominator() == f2.GetDenominator()){
    resultF.SetNumerator(f1.GetNumerator() - f2.GetNumerator());
    resultF.SetDenominator(f1.GetDenominator());
  }else{
    resultF.SetNumerator((f1.GetNumerator() * f2.GetDenominator()) - (f2.GetNumerator() * f1.GetDenominator()));
    resultF.SetDenominator(f1.GetDenominator() * f2.GetDenominator());
  }
  f1.PrintFraction();
  std::cout << " - ";
  f2.PrintFraction();
  std::cout << " = ";
  resultF.PrintFraction();

  SimpFraction(resultF);
  std::cout << " -> ";
  resultF.PrintFraction();
  std::cout << std::endl;
  CompareFraction(f1, f2);
}

void Fraction::MultFraction(Fraction& f1, Fraction& f2){
  Fraction resultF;
  resultF.SetNumerator(f1.GetNumerator() * f2.GetNumerator());
  resultF.SetDenominator(f1.GetDenominator() * f2.GetDenominator());

  f1.PrintFraction();
  std::cout << " * ";
  f2.PrintFraction();
  std::cout << " = ";
  resultF.PrintFraction();

  SimpFraction(resultF);
  std::cout << " -> ";
  resultF.PrintFraction();
  std::cout << std::endl;
  CompareFraction(f1, f2);

}

void Fraction::DivFraction(Fraction& f1, Fraction& f2){
 // CompareFraction(n1, d1, n2, d2);
  Fraction tempF = {f2.GetDenominator(), f2.GetNumerator()};
  Fraction resultF;
    
  f1.PrintFraction();
  std::cout << " % ";
  f2.PrintFraction();
  std::cout << " => ";

  resultF.MultFraction(f1, tempF);
}

void Fraction::SimpFraction(Fraction& f){
  for(int i = 2; i <= 9; i++){
    if(f.GetNumerator() % i == 0 && f.GetDenominator() % i == 0){
      f.SetNumerator(f.GetNumerator() / i);
      f.SetDenominator(f.GetDenominator() / i);
      SimpFraction(f);
    }
  }
}

void Fraction::CompareFraction(Fraction& f1, Fraction& f2){
  int valueFraction1 = 0, valueFraction2 = 0;

  valueFraction1 = f1.GetNumerator() / f1.GetDenominator();
  valueFraction2 = f2.GetNumerator() / f2.GetDenominator();

  if(valueFraction1 > valueFraction2){
    std::cout << "The first fraction is greater than second one!" << std::endl;
  }else if(valueFraction1 == valueFraction2){
    std::cout << "The first fraction is equal to second one!" << std::endl;
  }else{
    std::cout << "The first fraction is less than second one!" << std::endl;
  }
}

void Fraction::PrintFraction(){
  
  std::cout << this->GetNumerator() << "/" << this->GetDenominator();
}


int main( int argc , char **argv ){
  int n1 = 0, d1 = 0, n2 = 0, d2 = 0;
  char op = ' ';
  std::cout << "Choose the first numerator: ";
  std::cin >> n1;
  std::cout << "\nChoose the first denominator: ";
  std::cin >> d1;
  std::cout << "\nChoose the operation{+, -, *, /} : ";
  std::cin >> op;
  std::cout << "\nChoose the second numerator: ";
  std::cin >> n2;
  std::cout << "\nChoose the second denominator: ";
  std::cin >> d2;

  Fraction f1 = {n1, d1};
  Fraction f2(n2, d2);

  switch(op){
    case '+':
      {
        f1.AddFraction(f1, f2);
      }
      break;
    
    case '-':
      {
        f1.SubFraction(f1, f2);
      }
      break;

    case '*':
      {
        f1.MultFraction(f1, f2);
      }
      break;

    case '/':
      {
        f1.DivFraction(f1, f2);
      }
      break;
  }

  return 0;
}

