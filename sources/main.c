#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
// #include "addressbook.h"
// #include "form.h"

#include "../headers/addressbook.h"
#include "../headers/form.h"

int main() {
    AddressBook addressBook;
    int flag = 1;
    int options;
    Create(&addressBook);

    TakeOut(&addressBook);
    while (flag) {
        OnMenu();

        printf("????? ?????????: ");
        scanf("%d", &options);
        getchar();
        switch (options) {
            case 1:
                //???????
                FormRecording(&addressBook);
                break;
            case 2:
                //???
                FormForFinding(&addressBook);
                break;
            case 3:
                //?????
                FormForCorrecting(&addressBook);
                break;
            case 4:
                //?????
                FormForErasing(&addressBook);
                break;
            case 5:
                //??????
                FormForArranging(&addressBook);
                break;
            case 6:
                //???????
                FormForAllView(&addressBook);
                break;
            case 0:
                flag = 0;
                break;
            default:
                break;
        }
    }
    
    TakeIn(&addressBook);
    Destroy(&addressBook);

    return 0;
}