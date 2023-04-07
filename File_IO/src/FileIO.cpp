#include <iostream>
#include <fstream>
#include <cstring>
#include <ostream>
#include "includes/Utils.hpp"

const int MAX_NAME_SIZE = 256;
const char* CONTACTS_FILE_NAME = "Contacts.bin"; //binary file

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
void ResizeContactsDB(ContactsDB& contactsDB, int newCapacity); 
void SaveContacts(const ContactsDB& contactsDB);
void CreateContactsFile();

int main( int argc , char **argv ){
  ContactsDB contactsDB;
  contactsDB.optrContacts = nullptr;
  contactsDB.numberOfContacts = 0;
  contactsDB.capacity = 0;

  CreateContactsFile();

  if(!LoadContacts(contactsDB)){
    std::cout << "Error reading file: " << CONTACTS_FILE_NAME << std::endl;
    return 0;
  }

  char option;

  do{
    option = GetOptionFromUser();
    ExecuteOption(option, contactsDB);


  }while(option != 'q');

  SaveContacts(contactsDB);

  if(contactsDB.optrContacts != nullptr){
    delete [] contactsDB.optrContacts;
    contactsDB.optrContacts = nullptr;
  }

  return 0;
  
}

void CreateContactsFile(){
  std::ifstream inFile;
  
  inFile.open(CONTACTS_FILE_NAME, std::fstream::binary);
  if(!inFile.is_open()){
    std::ofstream outFile;
    outFile.open(CONTACTS_FILE_NAME, std::fstream::binary);
    outFile << std::flush;
    outFile.close();
  }
}


bool LoadContacts(ContactsDB& contactsDB){
  std::ifstream inFile;

  inFile.open(CONTACTS_FILE_NAME, std::fstream::binary);
  
  if(inFile.is_open()){
    inFile.seekg(0, inFile.end); //move the cursor to the final
    int lengthOfFileInBytes = inFile.tellg(); //returns the index of the cursor 
    inFile.seekg(0, inFile.beg); //move the cursor to the beginning 

    int numberOfContacts = lengthOfFileInBytes / sizeof(Contact);
    int capacity = numberOfContacts * 2 + 10;

    contactsDB.optrContacts = new Contact[capacity];
    contactsDB.numberOfContacts = numberOfContacts;
    contactsDB.capacity = capacity;

    inFile.read((char*)contactsDB.optrContacts, lengthOfFileInBytes);

    inFile.close();

    return true;
  }

  return false;
}

void SaveContacts(const ContactsDB& contactsDB){
  std::ofstream outFile;

  outFile.open(CONTACTS_FILE_NAME, std::fstream::binary);
  if(outFile.is_open()){
    outFile.write((char*)contactsDB.optrContacts, contactsDB.numberOfContacts * sizeof(Contact));
    outFile.close();
  }
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

void ResizeContactsDB(ContactsDB& contactsDB, int newCapacity){
  Contact* newContactsPtr = new Contact[newCapacity];

  for(int i = 0; i < contactsDB.numberOfContacts; i++){
    std::strcpy(newContactsPtr[i].firstName, contactsDB.optrContacts[i].firstName);
    std::strcpy(newContactsPtr[i].lastName, contactsDB.optrContacts[i].lastName);
    newContactsPtr[i].phoneNumber = contactsDB.optrContacts[i].phoneNumber;
  }

  if(contactsDB.optrContacts != nullptr){
    delete[] contactsDB.optrContacts;
    contactsDB.optrContacts = nullptr;
  }

  contactsDB.optrContacts = newContactsPtr;
  contactsDB.capacity = newCapacity;
}
