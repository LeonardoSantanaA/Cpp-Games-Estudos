#include <iostream>
#include "Utils.hpp"
#include <cctype>

char GetCharacter(const char *prompt, const char *error)
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

char GetCharacter(const char *prompt, const char *error, const char validInput[], int validInputLength, Utils::CharacterCaseType charCase)
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
