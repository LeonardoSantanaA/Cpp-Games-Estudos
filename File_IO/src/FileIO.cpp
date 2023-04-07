#include <iostream>
#include <fstream>
#include "includes/Utils.hpp"

const int MAX_NAME_SIZE = 256;

struct Contact{
  char firstName[MAX_NAME_SIZE];
  char lastName[MAX_NAME_SIZE];
  int phoneNumber;
};

struct ContactsDB{
  Contact* optrContacts;
  int numberOfContacts;
  int capacity;
  
};

bool LoadContacts(ContactsDB& contactsDB);
char GetOptionFromUser();
void ExecuteOption(char option, ContactsDB& contactsDB);
void AddOption(ContactsDB& contactsDB);
void DisplayOption(const ContactsDB& contactsDB);

int main( int argc , char **argv ){
  ContactsDB contactsDB;
  contactsDB.optrContacts = nullptr;
  contactsDB.numberOfContacts = 0;
  contactsDB.capacity = 0;

  LoadContacts(contactsDB);

  char option;

  do{
    option = GetOptionFromUser();
    ExecuteOption(option, contactsDB);


  }while(option != 'q');

  return 0;
  
}

bool LoadContacts(ContactsDB& contactsDB){

}

char GetOptionFromUser(){
  const char options[] = {'d', 'a', 'q'};

  return GetCharacter("Please choose any option:\n\n(D)isplay Contacts\n(A)dd Contact\n(Q)uit\n\nWhat is your choice: ", Utils::INPUT_ERROR_STRING, options, 3, Utils::CC_LOWER_CASE);
}
void ExecuteOption(char option, ContactsDB& contactsDB){
  switch(option){
    case 'a':
      AddOption(contactsDB);
      break;

    case 'd':
      DisplayOption(contactsDB);
      break;
  }
}

void AddOption(ContactsDB& contactsDB){
  if(contactsDB.numberOfContacts == contactsDB.capacity){
    ResizeContactsDB(contactsDB, contactsDB.capacity * 2 + 10); //+ 10 because capacity could be zero
  }

  GetString("Please enter the first name: ", Utils::INPUT_ERROR_STRING, contactsDB.optrContacts[contactsDB.numberOfContacts].firstName, MAX_NAME_SIZE - 1);
  GetString("Please enter the last name: ", Utils::INPUT_ERROR_STRING, contactsDB.optrContacts[contactsDB.numberOfContacts].lastName, MAX_NAME_SIZE - 1);

  std::cout << "Please input the phone number: ";
  std::cin >> contactsDB.optrContacts[contactsDB.numberOfContacts].phoneNumber;

  contactsDB.numberOfContacts++;

  SaveContacts(contactsDB);

  std::cout << "Saved!" << std::endl;
}

void DisplayOption(const ContactsDB& contactsDB){
  for(int i = 0; i < contactsDB.numberOfContacts; i++){
    std::cout << "Name: " << contactsDB.optrContacts[i].firstName << " " << contactsDB.optrContacts[i].lastName << std::endl;
    std::cout << "Phone number: " << contactsDB.optrContacts[i].phoneNumber << std::endl << std::endl;
  }
}
