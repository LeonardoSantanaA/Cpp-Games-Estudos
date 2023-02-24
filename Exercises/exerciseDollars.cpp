#include <iostream>

int main( int argc , char **argv ){

  float input;

  std::cout << "Write a number!" << '\n';
  std::cin >> input;
  std::cout << "Writed number: " << input << '\n';

  int hundredBills = input / 100;
  input -= (hundredBills * 100);
  std::cout << hundredBills << " hundred dollar bills\n";

  int tenBills = input / 10;
  input -= (tenBills * 10);
  std::cout << tenBills << " ten dollar bills\n";

  int fiveBills = input / 5;
  input -= (fiveBills * 5);
  std::cout << fiveBills << " five dollar bills\n";

  int twoBills = input / 2;
  input -= (twoBills * 2);
  std::cout << twoBills << " two dollar bills\n";

  int oneBills = input / 1;
  input-= (oneBills);
  std::cout << oneBills << " one dollar bills\n";

  int twentyFiveCent = input / 0.25;
  input -= (twentyFiveCent * 0.25);
  std::cout << twentyFiveCent << " twenty five cent pieces\n";

  int tenCent = input / 0.1;
  input -= (tenCent * 0.1);
  std::cout << tenCent << " ten cent pieces\n";

  int fiveCent = input / 0.05;
  input -= (fiveCent * 0.05);
  std::cout << fiveCent << " five cent pieces\n";

  int oneCent = (input / 0.01) + 1;
  input -= (oneCent * 0.01);
  std::cout << oneCent << " one cent pieces\n";

  return 0;
}

