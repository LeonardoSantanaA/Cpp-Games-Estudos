#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> //for swap and sort functions
#include "includes/Utils.hpp"

const int MAX_NAME_SIZE = 256;
const char* CONTACTS_FILE_NAME = "Contacts.txt"; //binary file

struct Contact{
  std::string firstName;
  std::string lastName;
  int phoneNumber;
};

struct ContactsDB{
  std::vector<Contact> contacts;
};

bool LoadContacts(ContactsDB& contactsDB);
char GetOptionFromUser();
void ExecuteOption(char option, ContactsDB& contactsDB);
void AddOption(ContactsDB& contactsDB);
void DisplayOption(ContactsDB& contactsDB);
void ResizeContactsDB(ContactsDB& contactsDB, int newCapacity); 
void SaveContacts(const ContactsDB& contactsDB);
void RemoveOption(ContactsDB& contactsDB);
bool CompareFirstName(const Contact& c1, const Contact& c2);
bool CompareLastName(const Contact& c1, const Contact& c2);


int main( int argc , char **argv ){
  ContactsDB contactsDB;

  LoadContacts(contactsDB);

  char option;

  do{
    option = GetOptionFromUser();
    ExecuteOption(option, contactsDB);


  }while(option != 'q');

  SaveContacts(contactsDB);

  return 0;
}


bool LoadContacts(ContactsDB& contactsDB){
  std::ifstream inFile;

  inFile.open(CONTACTS_FILE_NAME);
  
  if(inFile.is_open()){
      Contact newContact;

      while(!inFile.eof()){ //eof = end of file
        inFile >> std::ws;

        if(inFile.eof())
          break;

        inFile >> newContact.firstName >> newContact.lastName >> newContact.phoneNumber;
        contactsDB.contacts.push_back(newContact);
      }

      inFile.close();

    return true;
  }

  return false;
}

void SaveContacts(const ContactsDB& contactsDB){
  std::ofstream outFile;

  outFile.open(CONTACTS_FILE_NAME, std::fstream::binary);
  if(outFile.is_open()){
    for(int i = 0; i < contactsDB.contacts.size(); i++){
      outFile << contactsDB.contacts[i].firstName << " " << contactsDB.contacts[i].lastName << " " << contactsDB.contacts[i].phoneNumber;

      //making sure that is no newline at the end of the file
      if(i < contactsDB.contacts.size() - 1){
        outFile << std::endl;
      }
    }

    outFile.close();
  }
}

char GetOptionFromUser(){
  const char options[] = {'d', 'a', 'r', 'q'};

  return GetCharacter("Please choose any option:\n\n(D)isplay Contacts\n(A)dd Contact\n(R)emove Contact\n(Q)uit\n\nWhat is your choice: ", Utils::INPUT_ERROR_STRING, options, 3, Utils::CC_LOWER_CASE);
}

void ExecuteOption(char option, ContactsDB& contactsDB){
  switch(option){
    case 'a':
      AddOption(contactsDB);
      break;

    case 'd':
      DisplayOption(contactsDB);
      break;

    case 'r':
      RemoveOption(contactsDB);
      break;
  }
}

void AddOption(ContactsDB& contactsDB){

  Contact newContact;

  GetString("Please enter the first name: ", Utils::INPUT_ERROR_STRING, newContact.firstName);
  GetString("Please enter the last name: ", Utils::INPUT_ERROR_STRING, newContact.lastName);

  std::cout << "Please input the phone number: ";
  std::cin >> newContact.phoneNumber;

  contactsDB.contacts.push_back(newContact);

  SaveContacts(contactsDB);

  std::cout << "Saved!" << std::endl;
}

void RemoveOption(ContactsDB& contactsDB){
  if(contactsDB.contacts.size() <= 0){
    std::cout << "No contacts in the list!" << std::endl;
    return;
  }

  std::string firstName;
  std::string lastName;

  GetString("Please enter the first name: ", Utils::INPUT_ERROR_STRING, firstName);
  GetString("Please enter the last name: ", Utils::INPUT_ERROR_STRING, lastName);

  bool found = false;
  int foundIndex = -1;

  for(int i = 0; i < contactsDB.contacts.size() && !found; i++){
    if(contactsDB.contacts[i].firstName == firstName && contactsDB.contacts[i].lastName == lastName){
      found = true;
      foundIndex = i;
    }
  }

  if(found){
    std::swap(contactsDB.contacts[foundIndex], contactsDB.contacts[contactsDB.contacts.size() - 1]); //put the found index at the end
    contactsDB.contacts.pop_back();

    std::cout << "Removed " << firstName << " " << lastName << " from contacts." << std::endl;
  }else{
    std::cout << "Could not find: " << firstName << " " << lastName << " in contacts." << std::endl;
  }
}

void DisplayOption(ContactsDB& contactsDB){
  if(contactsDB.contacts.size() <= 0){
    std::cout << "You have no contacts!" << std::endl;
    return;
  }

  const char sortOptions[] = {'f', 'l'};
  char option;
  option = GetCharacter("Please choose a sort options:\n(F)irst Name\n(L)ast Name\n\nWhat is your choice: ", Utils::INPUT_ERROR_STRING, sortOptions, 2, Utils::CC_LOWER_CASE);

  if(option == sortOptions[0]){
    //first name 
    std::sort(contactsDB.contacts.begin(), contactsDB.contacts.end(), CompareFirstName);
  }else{
    //last name 
    std::sort(contactsDB.contacts.begin(), contactsDB.contacts.end(), CompareLastName);
  }

  for(int i = 0; i < contactsDB.contacts.size(); i++){
    std::cout << "Name: " << contactsDB.contacts[i].firstName << " " << contactsDB.contacts[i].lastName << std::endl;
    std::cout << "Phone number: " << contactsDB.contacts[i].phoneNumber << std::endl << std::endl;
  }
}

bool CompareFirstName(const Contact& c1, const Contact& c2){
  return c1.firstName < c2.firstName;
}

bool CompareLastName(const Contact& c1, const Contact& c2){
  return c1.lastName < c2.lastName;
}
