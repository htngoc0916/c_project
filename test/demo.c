#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct _addressBook{
    char names[11];
    char addresses[256];
    char phoneNumbers[18];
    char emailAddresses[256];
} AddressBook;

int TakeOut(AddressBook *addressBook){
    int count=0;
    FILE *fp = fopen("data.txt","rb");
    if(fp != NULL){
        while (fread(&addressBook[count], sizeof(AddressBook), 1, fp) > 0)
        {
            count++;
        }
        fclose(fp);
    }
    return count;
}



int main(){
    AddressBook addressBook[10] = {0};
    TakeOut(addressBook);
    
    printf("%-5s %-15s %-15s %-15s %s \n", "Line", "Name", "Address", "Phone", "Email");
    for(int i=0; i < 10; i++){
        printf("%-5d %-50s %-50s %-50s %s \n", (i+1), addressBook[i].names, addressBook[i].addresses, addressBook[i].phoneNumbers, addressBook[i].emailAddresses);
    }

}



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct _addressBook{
//     char names[11];
//     char addresses[256];
//     char phoneNumbers[18];
//     char emailAddresses[256];
// } AddressBook;

// int main(){
//     AddressBook addressBook[5] = {
//         {"Alice", "123 Main St, Anytown, USA", "123-456-7890", "alice@example.com"},
//         {"Bob", "456 Elm St, Anytown, USA", "234-567-8901", "bob@example.com"},
//         {"Charlie", "789 Oak St, Anytown, USA", "345-678-9012", "charlie@example.com"},
//         {"David", "987 Pine St, Anytown, USA", "456-789-0123", "david@example.com"},
//         {"Eve", "654 Birch St, Anytown, USA", "567-890-1234", "eve@example.com"}
//     };
    
//     FILE *fp = fopen("data.txt","wb");
//     if(fp != NULL){
//         fwrite(addressBook, sizeof(AddressBook), 5, fp);
//         fclose(fp);
//     }
    
//     return 0;
// }
