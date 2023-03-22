#ifndef __UTILS_H__
#define __UTILS_H__

namespace Utils
{
  const int IGNORE_CHARS = 256;
  const char *INPUT_ERROR_STRING = "Input error! Please try again.";

  enum CharacterCaseType{
    CC_UPPER_CASE = 0,
    CC_LOWER_CASE,
    CC_EITHER
  };
};

char GetCharacter(const char *prompt, const char *error);
char GetCharacter(const char *prompt, const char *error, const char validInput[], int validInputLength, Utils::CharacterCaseType charCase);
int GetInteger(const char *prompt, const char *error, const int validInput[], int validInputLength);
void ClearScreen();
void WaitForKeyPress();
#endif
