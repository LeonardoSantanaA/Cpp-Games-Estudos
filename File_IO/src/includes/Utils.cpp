#include "Utils.hpp"
#include <iostream>
#include <cctype>
#include <cstring>

char GetCharacter(const char* prompt, const char* error)
{
  char input;
  bool failure;

  do
  {
    failure = false;

    std::cout << prompt;
    std::cin >> input;

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(Utils::IGNORE_CHARS, '\n');
      std::cout << error << std::endl;
    }
    else
    {
      std::cin.ignore(Utils::IGNORE_CHARS, '\n');
      if (std::isalpha(input))
      {
        input = std::tolower(input);
      }
      else
      {
        std::cout << error << std::endl;
      }
    }
    break;
  } while (failure);

  return input;
}

char GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength, Utils::CharacterCaseType charCase)
{
  char input;
  bool failure;

  do
  {
    failure = false;

    std::cout << prompt;
    std::cin >> input;

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(Utils::IGNORE_CHARS, '\n');
      std::cout << error << std::endl;
      failure = true;
    }
    else
    {
      std::cin.ignore(Utils::IGNORE_CHARS, '\n');
      if (std::isalpha(input))
      {
        if(charCase == Utils::CC_UPPER_CASE){
          input = std::toupper(input);
        }else if(charCase == Utils::CC_LOWER_CASE){
          input = std::tolower(input);
        }
      }
      for (int i = 0; i < validInputLength; i++)
      {
        if (input == validInput[i])
        {
          return input;
        }
      }
    }

  } while (failure);

  return input;
}

int GetString(const char* prompt, const char* error, std::string& aString){
  bool failure;
  int length;
  
  do{
    failure = false;

    std::cout << prompt;
    std::cin >> aString;

    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(Utils::IGNORE_CHARS, '\n');
      std::cout << error << std::endl;
      failure = true;
    }else{
      std::cin.ignore(Utils::IGNORE_CHARS, '\n');
      length = aString.length();

      if(length == 0){
        std::cout << "You must enter a word that's longer than 0 characters! Please try again." << std::endl;
        failure = true;
      }
    }
  }while(failure);
  
  return length;
}

int GetInteger(const char* prompt, const char* error, const int validInput[], int validInputLength){
  int input;
  bool inputFailure;

  do{
    inputFailure = false;
    std::cout << prompt;
    std::cin >> input;
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(Utils::IGNORE_CHARS, '\n');
      std::cout << error << std::endl;
    }else{
      for(int i = 0; i < validInputLength; i++){
        if(input == validInput[i])
          return input;
      }
    }
    std::cout << error << std::endl;
    inputFailure = true;
  }while(inputFailure);

  return -1;
}

void ClearScreen(){
  system("clear");
}

void WaitForKeyPress(){
  char key = '\0';
  do{
    std::cout << "Press a key to continue...";
    std::cin >> key;
  }while(key == '\0');
}
