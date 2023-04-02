
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "addressbook.h"

//메인 Form
void OnMenu(){
    //char buffer[1024];
    char* buffer = (char*) malloc(1024);
    int length;
    int menuOptions = 7;
    int count = 0;
    char *menu[20] = {"기재하기", "찾기", "고치기", "지우기", "정리하기", "전체보기", "끝내기"}; 
   
    //system("cls"); windows
    system("clear"); //macbook
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%31s %s","", "주소록 v.01\n");
    length+=sprintf(buffer+length, "=============================================================================\n\n");
    for(int i=0; i< menuOptions; i++){
        count++;
        if(count == menuOptions) count =0; //0. 끝내기 샛팅
        length+=sprintf(buffer + length,"%32d . %s\n", count, menu[i]);
    }
    length+=sprintf(buffer+length,"\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s",buffer);
    free(buffer);
}
//선언
void Create(AddressBook *addressBook){
    #if 1
        addressBook->personal =(PersonalInformation(*))malloc(sizeof(PersonalInformation)*LINES);
        memset(addressBook->personal, 0, sizeof(PersonalInformation)*LINES);
    #endif
        //addressBook->personal = (PersonalInformation(*))calloc(LINES, sizeof(PersonalInformation));

    if(addressBook->personal !=NULL){
        addressBook->count = 0;
    }
}
//메모리 해제
void Destroy(AddressBook *addressBook){
    if(addressBook->personal != NULL){
        free(addressBook->personal);
        addressBook->count = 0;
    }
}
//졍령
void Arrange(AddressBook *addressBook){
    // int i, j;
    // int emptyCount = 0;
    // PersonalInformation temp;

    // for (i = 1; i < LINES; i++) {
    //     if (addressBook->personal[i].names[0] == '\0') {
    //         // Nếu dòng đang xét là rỗng, đưa nó xuống phía dưới
    //         temp = addressBook->personal[i];
    //         for (j = i; j < LINES - 1 - emptyCount; j++) {
    //             addressBook->personal[j] = addressBook->personal[j+1];
    //         }
    //         addressBook->personal[j] = temp;
    //         emptyCount++;
    //     } else {
    //         // Nếu không phải dòng rỗng, thực hiện sắp xếp như bình thường
    //         temp = addressBook->personal[i];
    //         j = i-1;
    //         while (j >= 0 && strcmp(addressBook->personal[j].names, temp.names) > 0) {
    //             addressBook->personal[j+1] = addressBook->personal[j];
    //             j--;
    //         }
    //         addressBook->personal[j+1] = temp;
    //     }
    // }
    int i, j;
    PersonalInformation temp;
    for (i = 1; i < LINES; i++) {
        if (addressBook->personal[i].names[0] == '\0') {
            continue; // bỏ qua dòng rỗng
        }
        temp = addressBook->personal[i];
        j = i - 1;
        while (j >= 0 && strcmp(addressBook->personal[j].names, temp.names) > 0) {
            addressBook->personal[j + 1] = addressBook->personal[j];
            j--;
        }
        addressBook->personal[j + 1] = temp;
    }
}
//꺼내다
int TakeOut(AddressBook *addressBook){
    int count=0;
    
    FILE *fp = fopen(path,"rb");
    if(fp != NULL){
        while (fread(&addressBook->personal[count], sizeof(PersonalInformation), 1, fp) > 0){
            count++;
        }
        fclose(fp);
    }
    return count;
}
//넣다.
int TakeIn(AddressBook *addressBook){
    int i=0;
    int count=0;
    
    //없으면 파일이 생성 있으면 현재 있는 txt 파일에 넣을 내용이 출력됨.
    FILE *fp = fopen(path,"wb");
    if(fp != NULL){
        while (i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0){
            count++;
            i++;
        }

        printf("\n ddd %d \n", count);
        if(count>0){
            if(fp != NULL){
                fwrite(addressBook->personal, sizeof(PersonalInformation), count, fp);
            }
        }
        fclose(fp);

        addressBook->count = count;
    }
    return count;
}
//기재하다
int Record(AddressBook *addressBook, char *name, char *address, char *phoneNumber, char *emailAddress){
    int line;
    line = addressBook->count;
    if(line >= 0 && line < LINES){
        strcpy(addressBook->personal[line].names, name);
        strcpy(addressBook->personal[line].addresses, address);
        strcpy(addressBook->personal[line].phoneNumbers, phoneNumber);
        strcpy(addressBook->personal[line].emailAddresses, emailAddress);
        addressBook->count++;
        line++;
    }else{
        line = -1;
    }
    return line;
}
//성명으로 찾다
int FindByName(AddressBook *addressBook, char(*name), int(*lines)){
    int count=0;
    int i=0;

    while (i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0){ 
        if(strcmp(addressBook->personal[i].names,name)==0){ 
            lines[count]=i; 
            count++;
        }
        i++;
    }
    
    return count;
}
//이메일로 찾다
int FindByEmail(AddressBook *addressBook, char(*emailAddress)){
    int line = -1;
    int i=0;

    while(i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0 && strcmp(addressBook->personal[i].emailAddresses,emailAddress)!=0){
        i++;
    }
    if(i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0){
        line = i;
    }
    
    return line;
}
//고치다
int Correct(AddressBook *addressBook, int correctLine, char (*address), char (*phoneNumber), char (*emailAddress)){
    int line =-1;

    if(0 <= correctLine && correctLine < LINES && strcmp(addressBook->personal[correctLine].names,"")!=0){
        line=correctLine;
        strcpy(addressBook->personal[line].addresses,address);
        strcpy(addressBook->personal[line].phoneNumbers,phoneNumber);
        strcpy(addressBook->personal[line].emailAddresses,emailAddress);
    }
    return line;
}
//지우다
int Erase(AddressBook *addressBook, int eraseLine){
    int i=0;
    int line=-1;
    int j;

    if(0 <= eraseLine && eraseLine < LINES && strcmp(addressBook->personal[eraseLine].names,"")!=0){
        line= eraseLine;
        i=line;
        //전체 내용을 판별
        while(i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0){
            i++;
        }   
        //내가 지울려고 하는 줄에 다음 줄에 내용이 있는지 없는지 판별
        if(line < LINES && strcmp(addressBook->personal[line].names,"\0")!=0){
            //내가 끝에번호가 아니니 뒤에 정보를 앞으로 끌어온다.
            for(j=line; j<i; j++){
                strcpy(addressBook->personal[j].names, addressBook->personal[j+1].names);
                strcpy(addressBook->personal[j].addresses, addressBook->personal[j+1].addresses);
                strcpy(addressBook->personal[j].phoneNumbers, addressBook->personal[j+1].phoneNumbers);
                strcpy(addressBook->personal[j].emailAddresses, addressBook->personal[j+1].emailAddresses);
            }
        }
        //내가 지울려고 하는 줄이 끝에 번지이니 나만 삭제한다.
        strcpy(addressBook->personal[i-1].names,"");
        strcpy(addressBook->personal[i-1].addresses,"");
        strcpy(addressBook->personal[i-1].phoneNumbers,"");
        strcpy(addressBook->personal[i-1].emailAddresses,"");
        addressBook->count--;
    }
    return line;
}