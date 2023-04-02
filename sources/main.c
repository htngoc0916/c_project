#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "addressbook.h"
#include "form.h"

int main() {
    AddressBook addressBook;
    int flag = 1;
    int options;
    Create(&addressBook);

    TakeOut(&addressBook);
    while (flag) {
        OnMenu();
        printf("\n count %d \n", addressBook.count);

        printf("메뉴를 선택하세요: ");
        scanf("%d", &options);
        getchar();
        switch (options) {
            case 1:
                //기재하기
                FormRecording(&addressBook);
                break;
            case 2:
                //찾기
                FormForFinding(&addressBook);
                break;
            case 3:
                //고치기
                FormForCorrecting(&addressBook);
                break;
            case 4:
                //지우기
                FormForErasing(&addressBook);
                break;
            case 5:
                //청리하기
                FormForArranging(&addressBook);
                break;
            case 6:
                //전체보기
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
