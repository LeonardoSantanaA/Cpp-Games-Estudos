#include <iostream>

class Fraction{
  public:
    static Fraction aHalf;
    static Fraction aThird;
    static Fraction aFourth;
    static Fraction aFifth;

    Fraction();
    Fraction(int n, int d);

    inline float GetNumerator() const{
      return this->numerator;
    }
    inline float GetDenominator() const{
      return this->denominator;
    }

    inline void SetNumerator(int n){
      this->numerator = n;
    }
    inline void SetNumerator(float n){
      this->numerator = n;
    }
    inline void SetDenominator(int d){
      this->denominator = d;
    }
    inline void SetDenominator(float d){
      this->denominator = d;
    }

    void AddFraction(Fraction& otherFraction);
    void SubFraction(Fraction& otherFraction);
    void MultFraction(Fraction& otherFraction);
    void DivFraction(Fraction& otherFraction);

    void PrintFraction() const{
      std::cout << this->GetNumerator() << "/" << this->GetDenominator();
    }

  private:
    float numerator;
    float denominator;
    void SimpFraction(Fraction& f);
    void CompareFraction(Fraction& otherFraction); 
};

Fraction Fraction::aHalf = Fraction(1, 2);
Fraction Fraction::aThird = Fraction(1, 3);
Fraction Fraction::aFourth = Fraction(1, 4);
Fraction Fraction::aFifth = Fraction(1, 5);

Fraction::Fraction(): Fraction(0, 1){}

Fraction::Fraction(int n, int d): numerator(n), denominator(d){}



void Fraction::AddFraction(Fraction& otherFraction){
  Fraction resultF;
  if(this->GetDenominator() == otherFraction.GetDenominator()){
    resultF.SetNumerator(this->GetNumerator() + otherFraction.GetNumerator());
    resultF.SetDenominator(this->GetDenominator());
  }else{
    resultF.SetNumerator((this->GetNumerator() * otherFraction.GetDenominator()) + (otherFraction.GetNumerator() * this->GetDenominator()));
    resultF.SetDenominator(this->GetDenominator() * otherFraction.GetDenominator());
  }
  this->PrintFraction();
  std::cout << " + ";
  otherFraction.PrintFraction();
  std::cout << " = ";
  resultF.PrintFraction();

  SimpFraction(resultF);
  std::cout << " -> ";
  resultF.PrintFraction();
  std::cout << std::endl;
  CompareFraction(otherFraction);
}

void Fraction::SubFraction(Fraction& otherFraction){
   Fraction resultF;
  if(this->GetDenominator() == otherFraction.GetDenominator()){
    resultF.SetNumerator(this->GetNumerator() - otherFraction.GetNumerator());
    resultF.SetDenominator(this->GetDenominator());
  }else{
    resultF.SetNumerator((this->GetNumerator() * otherFraction.GetDenominator()) - (otherFraction.GetNumerator() * this->GetDenominator()));
    resultF.SetDenominator(this->GetDenominator() * otherFraction.GetDenominator());
  }
  this->PrintFraction();
  std::cout << " - ";
  otherFraction.PrintFraction();
  std::cout << " = ";
  resultF.PrintFraction();

  SimpFraction(resultF);
  std::cout << " -> ";
  resultF.PrintFraction();
  std::cout << std::endl;
  CompareFraction(otherFraction);
}

void Fraction::MultFraction(Fraction& otherFraction){
  Fraction resultF;
  resultF.SetNumerator(this->GetNumerator() * otherFraction.GetNumerator());
  resultF.SetDenominator(this->GetDenominator() * otherFraction.GetDenominator());

  this->PrintFraction();
  std::cout << " * ";
  otherFraction.PrintFraction();
  std::cout << " = ";
  resultF.PrintFraction();

  SimpFraction(resultF);
  std::cout << " -> ";
  resultF.PrintFraction();
  std::cout << std::endl;
  CompareFraction(otherFraction);

}

void Fraction::DivFraction(Fraction& otherFraction){
  Fraction tempF = {int(otherFraction.GetDenominator()), int(otherFraction.GetNumerator())};
  Fraction resultF;
    
  this->PrintFraction();
  std::cout << " % ";
  otherFraction.PrintFraction();
  std::cout << " => ";

  resultF.SetNumerator(this->GetNumerator() * tempF.GetNumerator());
  resultF.SetDenominator(this->GetDenominator() * tempF.GetDenominator());

  this->PrintFraction();
  std::cout << " * ";
  tempF.PrintFraction();
  std::cout << " = ";
  resultF.PrintFraction();

  SimpFraction(resultF);
  std::cout << " -> ";
  resultF.PrintFraction();
  std::cout << std::endl;
  CompareFraction(otherFraction);
}

void Fraction::SimpFraction(Fraction& f){
  for(int i = 2; i <= 9; i++){
    if(static_cast<int>(f.GetNumerator()) % i == 0 && static_cast<int>(f.GetDenominator()) % i == 0){
      f.SetNumerator(f.GetNumerator() / i);
      f.SetDenominator(f.GetDenominator() / i);
      return SimpFraction(f);
    }
  }
}

void Fraction::CompareFraction(Fraction& otherFraction){
  float valueFraction1 = 0, valueFraction2 = 0;

  valueFraction1 = static_cast<float>(this->GetNumerator() / this->GetDenominator());
  valueFraction2 = static_cast<float>(otherFraction.GetNumerator() / otherFraction.GetDenominator());
  if(valueFraction1 > valueFraction2){
    std::cout << "The first fraction is greater than second one!" << std::endl;
  }else if(valueFraction1 == valueFraction2){
    std::cout << "The first fraction is equal to second one!" << std::endl;
  }else{
    std::cout << "The first fraction is less than second one!" << std::endl;
  }
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
  Fraction otherFraction(n2, d2);

  switch(op){
    case '+':
      {
        f1.AddFraction(otherFraction);
      }
      break;
    
    case '-':
      {
        f1.SubFraction(otherFraction);
      }
      break;

    case '*':
      {
        f1.MultFraction(otherFraction);
      }
      break;

    case '/':
      {
        f1.DivFraction(otherFraction);
      }
      break;
  }
  return 0;
}

