#include <iostream>
#include <algorithm>

//pega a primeira consoante ou encontro consonantal de uma palavra, move pro fim da palavra e coloca um "ay", ou se uma palavra comeca com vogal só adiciona "ay" no fim.

std::string PigLatinify(std::string& str);
bool isVowel(const std::string& stri, const int index);

int main( int argc , char **argv ){
  std::string word;

  std::cout << "type a word: ";
  std::cin >> word;
  std::cout << std::endl;

  std::cout << "Pig Latin version: " << PigLatinify(word) << std::endl;

  return 0;
}

std::string PigLatinify(std::string& str){

  if(isVowel(str, 0)){
    str.insert(str.size(), "ay");
    return str;
  }

  if(!isVowel(str, 0))
    str = str.substr(1, str.length() - 1) + str.front();
    //std::cout << "process 1: " << str << std::endl;
  if(!isVowel(str, 0))
    str = str.substr(1, str.length() - 1) + str.front();
    //std::cout << "process 2: " << str << std::endl;

  str += "ay"; //same that str.insert()
  return str;
}

bool isVowel(const std::string& str, const int index){
  char vowels[] = {'a', 'e', 'i', 'o', 'u'};

  if(index > str.size())
    return false;

  for(int i = 0; i < 4; i++){
    if(str[index] == vowels[i])
      return true;
  }

  return false;
}
