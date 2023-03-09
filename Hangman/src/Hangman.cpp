#include <iostream>
#include <cstring>
#include "Utils.hpp"

void PlayGame();
bool WantToPlayAgain();
int GetSecretPhrase(char secretPhrase[], int maxLength);
char *MakeHiddenPhrase(const char *secretPhrase, int secretPhraseLength);
void DrawBoard(int numberOfGuessesLeft, const char *noptrHiddenPhrase);
char GetGuess();
void UpdateBoard(char guess, char *noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int &numberOfGuessesLeft);
bool IsGameOver(int numberOfGuessesLeft, const char *noptrHiddenPhrase, int secretPhraseLength);
void DisplayResult(const char *secretPhrase, int numberOfGuessesLeft);

int main(int argc, char **argv)
{
  do
  {
    PlayGame();
  } while (WantToPlayAgain());
  return 0;
}

void PlayGame()
{
  const int MAX_LENGTH_OF_SECRET_PHRASE = 256;
  const int MAX_NUMBER_OF_GUESSES = 6;

  char secretPhrase[MAX_LENGTH_OF_SECRET_PHRASE];
  char *optrHiddenPhrase = nullptr;
  int numberOfGuessesLeft = MAX_NUMBER_OF_GUESSES;

  int secretPhraseLength = GetSecretPhrase(secretPhrase, MAX_LENGTH_OF_SECRET_PHRASE);

  optrHiddenPhrase = MakeHiddenPhrase(secretPhrase, secretPhraseLength);

  DrawBoard(numberOfGuessesLeft, optrHiddenPhrase);

  char guess;

  do
  {
    guess = GetGuess();

    UpdateBoard(guess, optrHiddenPhrase, secretPhrase, secretPhraseLength, numberOfGuessesLeft);

    DrawBoard(numberOfGuessesLeft, optrHiddenPhrase);
  } while (!IsGameOver(numberOfGuessesLeft, optrHiddenPhrase, secretPhraseLength));

  DisplayResult(secretPhrase, numberOfGuessesLeft);

  delete[] optrHiddenPhrase;
}

bool WantToPlayAgain()
{
  const char validInputs[] = {'y', 'n'};
  char response = GetCharacter("Would you like to play again? (y/n)", Utils::INPUT_ERROR_STRING, validInputs, 2);
  return response == 'y';
}

char GetGuess()
{
  return GetCharacter("Please input your guess: ", Utils::INPUT_ERROR_STRING);
}

void UpdateBoard(char guess, char *noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int &numberOfGuessesLeft)
{
  bool found = false;

  for (int i = 0; i < secretPhraseLength; i++)
  {
    if (std::tolower(secretPhrase[i]) == guess)
    {
      noptrHiddenPhrase[i] = secretPhrase[i];
      found = true;
    }
  }
  if (!found)
  {
    numberOfGuessesLeft--;
  }
}

bool IsGameOver(int numberOfGuessesLeft, const char *noptrHiddenPhrase, int secretPhraseLength)
{
  bool hasDash = false;
  for (int i = 0; i < secretPhraseLength; i++)
  {
    if (noptrHiddenPhrase[i] == '-')
    {
      hasDash = true;
      break;
    }
  }
  return numberOfGuessesLeft == 0 || !hasDash;
}

void DisplayResult(const char *secretPhrase, int numberOfGuessesLeft)
{
  if (numberOfGuessesLeft > 0)
  {
    std::cout << "You got it! The phrase was: " << secretPhrase << std::endl;
  }
  else
  {
    std::cout << "You didn't get it... The phrase was: " << secretPhrase << std::endl;
  }
}

int GetSecretPhrase(char secretPhrase[], int maxLength)
{
  bool failure;
  int length;

  do
  {
    failure = false;

    std::cout << "Please enter the secret phrase: ";
    std::cin.get(secretPhrase, maxLength);

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(Utils::IGNORE_CHARS, '\n');
      std::cout << Utils::INPUT_ERROR_STRING << std::endl;
      failure = true;
    }
    else
    {
      length = std::strlen(secretPhrase);
      if (length == 0)
      {
        std::cout << "You must enter a word that's longer than 0 characters! Please try again." << std::endl;
        failure = true;
      }
    }

  } while (failure);

  return length;
}

char *MakeHiddenPhrase(const char *secretPhrase, int secretPhraseLength)
{
  char *hiddenPhrase = new char[secretPhraseLength + 1]; //+1 because de null character

  for (int i = 0; i < secretPhraseLength; i++)
  {
    if (secretPhrase[i] != ' ')
    {
      hiddenPhrase[i] = '-';
    }
    else
    {
      hiddenPhrase[i] = ' ';
    }
    hiddenPhrase[secretPhraseLength] = '\0';
  }
  return hiddenPhrase;
}

void DrawBoard(int numberOfGuessesLeft, const char *noptrHiddenPhrase)
{
  switch (numberOfGuessesLeft)
  {
  case 0:
  {
    std::cout << " +---+" << std::endl;
    std::cout << " |   |" << std::endl;
    std::cout << " |   O" << std::endl;
    std::cout << " |  /|\\" << std::endl;
    std::cout << " |  / \\" << std::endl;
    std::cout << "-+-" << std::endl
              << std::endl;
  }
  break;
  case 1:
  {
    std::cout << " +---+" << std::endl;
    std::cout << " |   |" << std::endl;
    std::cout << " |   O" << std::endl;
    std::cout << " |  /|\\" << std::endl;
    std::cout << " |  / " << std::endl;
    std::cout << "-+-" << std::endl
              << std::endl;
  }
  break;
  case 2:
  {
    std::cout << " +---+" << std::endl;
    std::cout << " |   |" << std::endl;
    std::cout << " |   O" << std::endl;
    std::cout << " |  /|\\" << std::endl;
    std::cout << " |" << std::endl;
    std::cout << "-+-" << std::endl
              << std::endl;
  }
  break;
  case 3:
  {
    std::cout << " +---+" << std::endl;
    std::cout << " |   |" << std::endl;
    std::cout << " |   O" << std::endl;
    std::cout << " |  /|" << std::endl;
    std::cout << " |" << std::endl;
    std::cout << "-+-" << std::endl
              << std::endl;
  }
  break;
  case 4:
  {
    std::cout << " +---+" << std::endl;
    std::cout << " |   |" << std::endl;
    std::cout << " |   O" << std::endl;
    std::cout << " |   |" << std::endl;
    std::cout << " |" << std::endl;
    std::cout << "-+-" << std::endl
              << std::endl;
    ;
  }
  break;
  case 5:
  {
    std::cout << " +---+" << std::endl;
    std::cout << " |   |" << std::endl;
    std::cout << " |   O" << std::endl;
    std::cout << " |" << std::endl;
    std::cout << " |" << std::endl;
    std::cout << "-+-" << std::endl
              << std::endl;
    ;
  }
  break;
  case 6:
  {
    std::cout << " +---+" << std::endl;
    std::cout << " |   |" << std::endl;
    std::cout << " |" << std::endl;
    std::cout << " |" << std::endl;
    std::cout << " |" << std::endl;
    std::cout << "-+-" << std::endl
              << std::endl;
  }
  break;
  }
  std::cout << "Secret Phrase: " << noptrHiddenPhrase << std::endl
            << std::endl;
}
