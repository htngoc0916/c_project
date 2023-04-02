#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
#define LINES 10
#define path "data.txt"

typedef struct _personalInformation{
    char names[11];
    char addresses[256];
    char phoneNumbers[18];
    char emailAddresses[256];
}PersonalInformation;

typedef struct _addressBook{
    int count;
    PersonalInformation *personal;
} AddressBook;

void OnMenu();

int TakeOut(AddressBook *addressBook);
int TakeIn(AddressBook *addressBook);

void Create(AddressBook *addressBook);
void Destroy(AddressBook *addressBook);
void Arrange(AddressBook *addressBook);
int Record(AddressBook *addressBook, char *name, char *address, char *phoneNumber, char *emailAddress);
int FindByName(AddressBook *addressBook, char(*name), int(*lines));
int FindByEmail(AddressBook *addressBook, char(*emailAddress));
int Correct(AddressBook *addressBook, int correctLine, char (*address), char (*phoneNumber), char (*emailAddress));
int Erase(AddressBook *addressBook, int eraseLine);

#endif 