#include <cmath>
#include <iostream>

typedef int (*ArithmeticFunction)(int, int);

int Add(int x, int y);
int Sub(int x, int y);
int Mult(int x, int y);
int Div(int x, int y);
int Mod(int x, int y);
int Power(int x, int y);
ArithmeticFunction GetArithmeticFunction(char op);

int main( int argc , char **argv ){
  int x1 = 0, x2 = 0;
  char op;

  std::cout << "Please input the 2 operands with a space between: ";
  std::cin >> x1 >> x2;

  std::cout << "Plaease enter the operation ('+', '-', '*', '/', '%', '^'): ";
  std::cin >> op;

  ArithmeticFunction opFcn = GetArithmeticFunction(op);

  std::cout << x1 << " " << op << " " << x2 << " = " << opFcn(x1, x2) << std::endl;

  return 0;
}

int Add(int x, int y){
  return x + y;
}

int Sub(int x, int y){
  return x - y;
}

int Mult(int x, int y){
  return x * y;
}
int Div(int x, int y){
  return x / y;
}

int Mod(int x, int y){
  return x % y;
}

int Power(int x, int y){
  return std::pow(x, y);
}

ArithmeticFunction GetArithmeticFunction(char op){
  switch (op){
    case '+' : return Add;
    case '-' : return Sub;
    case '*' : return Mult;
    case '/' : return Div;
    case '%' : return Mod;
    case '^' : return Power;
  }

  return Add;
}


