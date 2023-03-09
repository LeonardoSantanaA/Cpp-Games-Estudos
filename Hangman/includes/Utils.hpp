#ifndef __UTILS_H__
#define __UTILS_H__

namespace Utils
{
  const int IGNORE_CHARS = 256;
  const char *INPUT_ERROR_STRING = "Input error! Please try again.";
};

char GetCharacter(const char *prompt, const char *error);
char GetCharacter(const char *prompt, const char *error, const char validInput[], int validInputLength);
#endif
