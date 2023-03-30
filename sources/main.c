#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINES 10
#define path "address.txt"

typedef struct _addressBook{
    char names[11];
    char addresses[256];
    char phoneNumbers[18];
    char emailAddresses[256];
} AddressBook;

int TakeOut(AddressBook *addressBook);
int TakeIn(AddressBook *addressBook);

int Record(AddressBook *addressBook, char *name, char *address, char *phoneNumber, char *emailAddress);
int FindByName(AddressBook *addressBook, char(*name), int(*lines));
int FindByEmail(AddressBook *addressBook, char(*emailAddress));
int Correct(AddressBook *addressBook, int correctLine, char (*address), char (*phoneNumber), char (*emailAddress));
int Erase(AddressBook *addressBook, int eraseLine);
void Arrange(AddressBook *addressBook);

void FormRecording(AddressBook *addressBook);
void FormForFinding(AddressBook *addressBook);
void FormForErasing(AddressBook *addressBook);
void FormForCorrecting(AddressBook *addressBook);
void FormForAllView(AddressBook *addressBook);
void FormForByEmailAddressses(AddressBook *addressBook);
void FormForByName(AddressBook *addressBook);

int main(){
    AddressBook addressBook[LINES] = {0};
    char name[11];
    char emailAddress[256];
    char address[256];
    char phoneNumber[18];

    TakeOut(addressBook);

    printf("input: ");
    scanf("%s %s %s %s", name,address, phoneNumber, emailAddress);
    Record(addressBook, name, address, phoneNumber, emailAddress);
    FormForAllView(addressBook);

    TakeIn(addressBook);

    return 0;
}
//꺼내다
int TakeOut(AddressBook *addressBook){
    int i=0;
    int count=0;
    FILE *fp = fopen(path,"rb");
    if(fp != NULL){
        // while (i<LINES && !feof(fp) && fscanf(fp,"%s %s %s %s",addressBook[i].names, addressBook[i].addresses , addressBook[i].phoneNumbers,addressBook[i].emailAddresses)){
        //     i++;
        //     count++;
        // }
        // fclose(fp);

        while (fread(&addressBook[i], sizeof(AddressBook), 1, fp) > 0)
        {
            i++;
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
        while (i<LINES && strcmp(addressBook[i].names,"\0")!=0){
            count++;
            i++;
        }
        //마지막 공백을 빼주는 로직
        if(count>0){
            for(i=0; i<count; i++){
                //fprintf(fp,"%s \t %s \t %s \t %s\n",addressBook[i].names,addressBook[i].addresses,addressBook[i].phoneNumbers,addressBook[i].emailAddresses);
                fwrite(&addressBook[i], sizeof(addressBook), 1, fp);
            }
        }
        fclose(fp);
    }
    return count;
}

//기재하다
int Record(AddressBook *addressBook, char *name, char *address, char *phoneNumber, char *emailAddress){
    int i=0;
    int line = -1;

    while(i < LINES && strcmp(addressBook[i].names,"\0")!=0) {
        i++;
    }
    printf("\n line %d \n ", i);
    if(i < LINES) {
        strcpy(addressBook[i].names, name);
        strcpy(addressBook[i].addresses, address);
        strcpy(addressBook[i].phoneNumbers, phoneNumber);
        strcpy(addressBook[i].emailAddresses, emailAddress);
        line = i + 1;
    }
    return line;
}
//성명으로 찾다
int FindByName(AddressBook *addressBook, char(*name), int(*lines)){
    int count=0;
    int i=0;

    while (i<LINES && strcmp(addressBook[i].names,"\0")!=0){ 
        if(strcmp(addressBook[i].names,name)==0){ 
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

    while(i<LINES && strcmp(addressBook[i].names,"\0")!=0 && strcmp(addressBook[i].emailAddresses,emailAddress)!=0){
        i++;
    }
    if(i<LINES && strcmp(addressBook[i].names,"\0")!=0){
        line = i;
    }else{
        line = -1;
    }
    
    return line;
}
//고치다
int Correct(AddressBook *addressBook, int correctLine, char (*address), char (*phoneNumber), char (*emailAddress)){
    int i=0;
    int line =-1;

    if(0 <= correctLine && correctLine < LINES && strcmp(addressBook[correctLine].names,"")!=0){
        line=correctLine;
        strcpy(addressBook[line].addresses,address);
        strcpy(addressBook[line].phoneNumbers,phoneNumber);
        strcpy(addressBook[line].emailAddresses,emailAddress);
    }
    return line;
}
//지우다
int Erase(AddressBook *addressBook, int eraseLine){
    int i=0;
    int line=-1;
    int j;

    if(0 <= eraseLine && eraseLine < LINES && strcmp(addressBook[eraseLine].names,"")!=0){
        line= eraseLine;
        i=line;
        //전체 내용을 판별
        while(i<LINES && strcmp(addressBook[i].names,"\0")!=0){
            i=i+1;
        }   
        //내가 지울려고 하는 줄에 다음 줄에 내용이 있는지 없는지 판별
        if(line < LINES && strcmp(addressBook[line].names,"\0")!=0){
            //내가 끝에번호가 아니니 뒤에 정보를 앞으로 끌어온다.
            for(j=line; j<i; j++){
                strcpy(addressBook[j].names, addressBook[j+1].names);
                strcpy(addressBook[j].addresses, addressBook[j+1].addresses);
                strcpy(addressBook[j].phoneNumbers, addressBook[j+1].phoneNumbers);
                strcpy(addressBook[j].emailAddresses, addressBook[j+1].emailAddresses);
            }
        }
        //내가 지울려고 하는 줄이 끝에 번지이니 나만 삭제한다.
        strcpy(addressBook[i-1].names,"");
        strcpy(addressBook[i-1].addresses,"");
        strcpy(addressBook[i-1].phoneNumbers,"");
        strcpy(addressBook[i-1].emailAddresses,"");
    }
    return line;
}
//정렬하다.
void Arrange(AddressBook *addressBook){
    int i=0;
    int j=0;
    int min;
    char nameTemp[11];
    char addressTemp[256];
    char phoneNumberTemp[18];
    char emailAddressTemp[256];
    while (i < LINES) {
        if (strcmp(addressBook[i].names, "") == 0) {
            i++;
            continue;
        }
        
        min = i;
        j = i + 1;
        
        while (j < LINES && strcmp(addressBook[j].names, "") != 0) {
            if (strcmp(addressBook[min].names, addressBook[j].names) > 0) {
                min = j;
            }
            j++;
        }

        if (i != min) {
            strcpy(nameTemp, addressBook[min].names);
            strcpy(addressBook[min].names, addressBook[i].names);
            strcpy(addressBook[i].names, nameTemp);

            strcpy(addressTemp, addressBook[min].addresses);
            strcpy(addressBook[min].addresses, addressBook[i].addresses);
            strcpy(addressBook[i].addresses, addressTemp);

            strcpy(phoneNumberTemp, addressBook[min].phoneNumbers);
            strcpy(addressBook[min].phoneNumbers, addressBook[i].phoneNumbers);
            strcpy(addressBook[i].phoneNumbers, phoneNumberTemp);

            strcpy(emailAddressTemp, addressBook[min].emailAddresses);
            strcpy(addressBook[min].emailAddresses, addressBook[i].emailAddresses);
            strcpy(addressBook[i].emailAddresses, emailAddressTemp);
        }
        i++;
    }
}

void FormForAllView(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    
    system("cls");
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%25s %s","", "주소록 - 전체보기\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    length+=sprintf(buffer+length,"%-5s %-15s %-15s %-15s %s \n", "Line", "Name", "Address", "Phone", "Email");
    for(int i=0; i < LINES; i++){
        length+=sprintf(buffer +length, "%-5d %-15s %-15s %-15s %s \n", (i+1), addressBook[i].names, addressBook[i].addresses, addressBook[i].phoneNumbers, addressBook[i].emailAddresses);
    }
    length+=sprintf(buffer+length, "-----------------------------------------------------------------------------\n");
    length+=sprintf(buffer+length, "전 화면에 돌아갑니다. \n");
    length+=sprintf(buffer+length, "=> Enter키 누르세요. \n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    free(buffer); 
    char c = getc(stdin); 
}
void FormRecording(AddressBook *addressBook){
     /* Record */
    //char buffer[1024];
    char* buffer = (char*) malloc(1024);

    int length;
    char name[11];
    char emailAddress[255];
    char address[256];
    char phoneNumber[18];
    int line = -1; //result = -1: 공간이 없음, result > 0 성공
    char ynFlag;
    int flag = 1;
    int flagEmail = 1;

    while(flag){
        //system("cls"); //windows
        system("cls"); //macbook
        length=sprintf(buffer,"\n");
        length+=sprintf(buffer + length, "%25s %s","", "기재하다 \n");
        length+=sprintf(buffer + length, "%24s %s","", "[정보 기재] \n");
        length+=sprintf(buffer + length, "====================================================================\n");
        printf("%s",buffer);
        //이메일
        do{
            printf("\n 기재할 이메일을 입력: ");
            fgets(emailAddress, sizeof(emailAddress), stdin);   //scanf 쓰면 '\n' 포함 저장하기 때문에 안됩니다. fgets() 쎠야됩니다.
            emailAddress[strcspn(emailAddress, "\n")] = '\0'; // enter 해제
            printf("\n 개재하실 이메일이 맛습니까? (y/n) : ");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장      
            getchar();
        }while (toupper(ynFlag) != 'Y');
        printf("--------------------------------------------------------------------\n");

        //이메일 중복
        if(toupper(ynFlag) == 'Y'){
            line = FindByEmail(addressBook, emailAddress);
            if(line >=0){
                system("cls"); //macbook
                length=sprintf(buffer,"\n");
                length+=sprintf(buffer + length, "%25s %s","", "기재하다 \n");
                length+=sprintf(buffer + length, "%24s %s","", "[정보 기재] \n");
                length+=sprintf(buffer + length, "====================================================================\n\n");
                length+=sprintf(buffer + length, "%5s 입력하 신 %s 이메일을 중복되었습니다.\n","", emailAddress);
                length+=sprintf(buffer + length, "====================================================================\n");
                length+=sprintf(buffer + length, "%5s %s","", "N는 뒤로 돌아가기.\n");
                printf("%s",buffer);
                printf("%5s %s","", "계속 입력하겠습니까? (y/n): ");
                scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장      
                getchar();
                if(toupper(ynFlag) != 'Y'){
                    return;
                }else{
                    continue;
                }
            }
        }

        //이름
        do{
            printf("\n 기재할 성명을 입력: ");
            //scanf("%s",name); scanf 쓰면 '\n' 포함 저장하기 때문에 안됩니다. fgets() 쎠야됩니다.
            fgets(name, sizeof(name), stdin);   
            name[strcspn(name, "\n")] = '\0'; // enter 해제
            printf("\n 개재하실 성명이 맛습니까? (y/n) : ");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장      
            getchar();
        }while (toupper(ynFlag) != 'Y');
        printf("--------------------------------------------------------------------\n");

        //주소
        do{
            printf("\n 기재할 주소를 입력: ");
            fgets(address, sizeof(address), stdin);   //scanf 쓰면 '\n' 포함 저장하기 때문에 안됩니다. fgets() 쎠야됩니다.
            address[strcspn(address, "\n")] = '\0'; // enter 해제
            printf("\n 개재하실 조소가 맛습니까? (y/n) : ");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장          
            getchar();
        }while (toupper(ynFlag) != 'Y');
        printf("--------------------------------------------------------------------\n");

        //전화번호
        do{
            printf("\n 기재할 전화번호를 입력: ");
            fgets(phoneNumber, sizeof(phoneNumber), stdin);   //scanf 쓰면 '\n' 포함 저장하기 때문에 안됩니다. fgets() 쎠야됩니다.
            phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; // enter 해제
            printf("\n 개재하실 전화번호가 맛습니까? (y/n) : ");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장        
            getchar();
        }while (toupper(ynFlag) != 'Y');
        printf("--------------------------------------------------------------------\n");

        line = Record(addressBook, name, address, phoneNumber, emailAddress);

        if(line != -1){
            getchar(); 
            system("cls"); //macbook
            length=sprintf(buffer,"\n");
            length+=sprintf(buffer + length, "%25s %s","", "기재하다 \n");
            length+=sprintf(buffer + length, "%24s %s","", "[정보 기재] \n");
            length+=sprintf(buffer + length, "====================================================================\n");
            length+=sprintf(buffer + length, "%3s %s \n\n","", "기재 성공되였습니다.");
            length+=sprintf(buffer + length, "%s \n","입력정보");
            length+=sprintf(buffer + length, "%5s %-10s : %s \n","","성명",name);
            length+=sprintf(buffer + length, "%5s %-10s : %s \n","","조수", address);
            length+=sprintf(buffer + length, "%5s %-10s : %s \n","","전화번호", phoneNumber);
            length+=sprintf(buffer + length, "%5s %-10s : %s \n","","이메일", emailAddress);
            length+=sprintf(buffer + length, "--------------------------------------------------------------------\n");
            length+=sprintf(buffer + length, "%15s: %d/%d \n\n","기재된 내용", line, LINES);
            length+=sprintf(buffer + length, "%s: %d %s \n\n", "입력하신 정보를", line, "줄에 기재하였습니다.");
            length += sprintf(buffer+length, "%3s %-5s %-8s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
            length+=sprintf(buffer + length, "%3s %-5d %-8s %-15s %-15s %s\n", "", line, name, address, phoneNumber, emailAddress);
            length+=sprintf(buffer + length, "--------------------------------------------------------------------\n");
            printf("%s", buffer);   
            printf("계속 입력하겠습니까? (y/n): ");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장 
            getchar();
            if(toupper(ynFlag) != 'Y') flag = 0;
        } else { 
            getchar(); 
            system("cls"); //macbook
            length=sprintf(buffer,"\n");
            length+=sprintf(buffer + length, "%25s %s","", "기재하다 \n");
            length+=sprintf(buffer + length, "%24s %s","", "[정보 기재] \n");
            length+=sprintf(buffer + length, "====================================================================\n\n");
            length+=sprintf(buffer + length, "%1s %s","", "기재할 공간이 없습니다. \n");
            length+=sprintf(buffer + length, "--------------------------------------------------------------------\n\n");
            length+=sprintf(buffer + length, "%1s %s","", "기재할 공간이 없습니다. \n\n");
            length+=sprintf(buffer + length, "%3s %s","", "주메뉴로 이동합니다. \n");
            length+=sprintf(buffer + length, "%3s %s","", "=> Enter키를 누르세요. \n");
            printf("%s", buffer);   
            getchar();
            free(buffer);
            return;
        }
    }
    free(buffer);
}
void FormForFinding(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    int flag = 1;
    int options;

    while (flag){
        //system("cls");
        system("cls");
        length=sprintf(buffer,"\n");
        length+=sprintf(buffer+length, "%30s %s","", "찾다\n");
        length+=sprintf(buffer+length, "%28s %s","", "메뉴 - 선택\n");
        length+=sprintf(buffer+length, "=============================================================================\n\n");
        length+=sprintf(buffer+length, "%24s %s","", "1. 성명으로 찾다.\n");
        length+=sprintf(buffer+length, "%24s %s","", "2. 이메일로 찾다.\n");
        length+=sprintf(buffer+length, "%24s %s","", "0. 뒤로 돌아가기.\n");
        length+=sprintf(buffer+length, "\n\n");
        length+=sprintf(buffer+length, "=============================================================================\n\n");
        printf("%s", buffer);
        printf("메뉴를 선택하세요: ");
        scanf("%d", &options);
        getchar();
        switch(options){
            case 1:
                //성명
                FormForByName(addressBook);
                break;
            case 2:
                //이메일
                FormForByEmailAddressses(addressBook);
                break;
            case 0:
                flag = 0;
                break;
        }
    }
    free(buffer); 
}
void FormForErasing(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    char name[11];
    int line, count, maxLine;
    int lines[LINES];
    int flag = 1;
    char checkLine = 'N'; //사제번호가 안맛을데
    char ynFlag;

    while(flag){
        system("cls");
        length=sprintf(buffer,"\n");
        length+=sprintf(buffer+length, "%30s %s","", "지우기\n");
        length+=sprintf(buffer+length, "=============================================================================\n");
        printf("%s", buffer);
        printf("%3s %s", "", "지우고 싶은 성명을 입력해주세요. \n");
        printf("%s", "-----------------------------------------------------------------------------\n");
        
        do{
            printf("%10s %s", "", "성명: ");
            fgets(name, sizeof(name), stdin);   
            name[strcspn(name, "\n")] = '\0'; // enter 해제
            printf("\n");
            printf("찾으시겠습니까? (y/n): ");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장  
            getchar();    
            printf("-----------------------------------------------------------------------------\n");
        } while (toupper(ynFlag) != 'Y');
        
        count = FindByName(addressBook, name, lines);
        if(count > 0){
            while (checkLine != '\0'){
                system("cls");
                if(checkLine == 'N'){
                    length += sprintf(buffer + length, "검색 결과: \n");
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i + 1;
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook[lines[i]].names, addressBook[lines[i]].addresses, addressBook[lines[i]].phoneNumbers, addressBook[lines[i]].emailAddresses);
                    }
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length, "지울 줄 번호를 입력해주세요 (%d ~ %d  사이의 숫자만 입력하세요). \n\n", 1, count);
                }else{
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "지우기\n");
                    length += sprintf(buffer + length, "=============================================================================\n");
                    length += sprintf(buffer + length, "%s", "지울 줄 번호가 유효하지 않습니다. \n");
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i+1;
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook[lines[i]].names, addressBook[lines[i]].addresses, addressBook[lines[i]].phoneNumbers, addressBook[lines[i]].emailAddresses);
                    }
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length, "지울 줄 번호를 다시 입력해주세요. (%d ~ %d  사이의 숫자만 입력하세요). \n\n", 1, count);
                }
                printf("%s", buffer);
                do{
                    printf("줄: ");
                    scanf("%d",&line);
                    getchar();

                    printf("지우실 줄 번호가 맞습니까? (y/n): ");
                    scanf("%c",&ynFlag);
                    getchar();
                }
                while(toupper(ynFlag) != 'Y');

                //줄을 잘못입력 체크
                system("cls");
                if(line <= 0 || line > maxLine){
                    //번호 잘못입했음
                    checkLine = 'Y';
                }else{
                    //번호 맞음
                    checkLine = 'N';
                    count = Erase(addressBook, lines[line - 1]);
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "지우기\n");
                    length += sprintf(buffer + length, "=============================================================================\n\n");
                    length += sprintf(buffer + length, "%d번쨰 줄이 삭제되었습니다. \n", count + 1);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
                    printf("%s", buffer);
                    printf("N을 누르면 메인메뉴로 돌아갑니다. \n");
                    printf("계속 지우시겠습니까? (y/n): ");
                    scanf("%c",&ynFlag);
                    getchar();
                    if(toupper(ynFlag) != 'Y'){
                        ynFlag = '\0';
                        return;
                    }else{
                        //반복끝내기
                        ynFlag = '\0';
                        break;
                    }
                }
            }
        }else{
            system("cls");
            length += sprintf(buffer + length, "%3s %s을(를) 못 찾았습니다.\n", "", name);
            length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
            printf("%s", buffer);
            printf("N을 입력하시면 메인메뉴로 돌아갑니다. \n 다시 입력하시겠습니까? (y/n): ");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장  
            getchar();    
            printf("-----------------------------------------------------------------------------\n");
            if(toupper(ynFlag) != 'Y'){
                return;
            }
        }
    }
}
void FormForCorrecting(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    char name[11];
    char address[256];
    char phoneNumber[18];
    char emailAddress[256];
    int lines[LINES];
    int line;
    char ynFlag;
    int count, maxLine;
    int flag = 1;
    char checkLine = 'N';
    
    while (flag){
        system("cls");
        length=sprintf(buffer,"\n");
        length+=sprintf(buffer+length, "%30s %s","", "고치기\n");
        length+=sprintf(buffer+length, "=============================================================================\n");
        printf("%s", buffer);
        printf("%3s %s", "", "고치고 싶은 성명을 입력해주세요. \n");
        printf("%s", "-----------------------------------------------------------------------------\n");
        do{
            printf("%10s %s", "", "성명: ");
            fgets(name, sizeof(name), stdin);   
            name[strcspn(name, "\n")] = '\0'; // enter 해제
            printf("\n");
            printf("고치 성명이 맞습니까? (y/n): ");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장  
            getchar();    
            printf("-----------------------------------------------------------------------------\n");
            if(ynFlag == '0') return;
        } while (toupper(ynFlag) != 'Y');

        count = FindByName(addressBook, name, lines);
        if(count > 0){
            while (checkLine != '\0'){
                system("cls");
                if(checkLine == 'N'){
                    length += sprintf(buffer + length, "고칠 %s를(을) %d건 찾았습니다.\n", name, count);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
                    length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i+1; //line 입력 체크 시 필요
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook[lines[i]].names, addressBook[lines[i]].addresses, addressBook[lines[i]].phoneNumbers, addressBook[lines[i]].emailAddresses);
                    }
                }
                else{
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "지우기\n");
                    length += sprintf(buffer + length, "=============================================================================\n");
                    length += sprintf(buffer + length, "%s", "지울 줄 번호가 유효하지 않습니다. \n");
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i+1; //line 입력 체크 시 필요
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook[lines[i]].names, addressBook[lines[i]].addresses, addressBook[lines[i]].phoneNumbers, addressBook[lines[i]].emailAddresses);
                    }
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length, "지울 줄 번호를 다시 입력해주세요. (%d ~ %d  사이의 숫자만 입력하세요). \n\n", 1, count);
                }
                length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                printf("%s", buffer);
                do{
                    
                    printf("고칠 줄 번호를 입력해주세요. \n");
                    printf("줄: ");
                    scanf("%d",&line);
                    getchar();

                    printf("고칠 줄 번호가 맞습니까? (y/n): ");
                    scanf("%c",&ynFlag);
                    getchar();
                    printf("\n");
                    printf("-----------------------------------------------------------------------------\n");
                }
                while(toupper(ynFlag) != 'Y');

                //줄을 잘못입력 체크
                system("cls");
                if(line <= 0 || line > maxLine){
                    //번호 잘못입했음
                    checkLine = 'Y';
                }else{
                    //번호 맞음
                    checkLine = 'N';
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "고치기\n");
                    length += sprintf(buffer + length, "=============================================================================\n\n");
                    length += sprintf(buffer + length, "고칠 줄 번호: %d \n\n", line);
                    length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", line, addressBook[lines[line - 1]].names, addressBook[lines[line - 1]].addresses, addressBook[lines[line - 1]].phoneNumbers, addressBook[lines[line - 1]].emailAddresses);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    printf("%s", buffer);
                    //주소
                    do{
                        printf("%10s %s", "", "주소: ");
                        fgets(address, sizeof(address), stdin);   
                        address[strcspn(address, "\n")] = '\0'; // enter 해제
                        printf("\n");
                        printf("고치 주소가 맞습니까? (y/n): ");
                        scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장  
                        getchar();    
                        printf("-----------------------------------------------------------------------------\n");
                        if(ynFlag == '0') return;
                    } while (toupper(ynFlag) != 'Y');
                    //전화번호
                    do{
                        printf("%10s %s", "", "전화번호: ");
                        fgets(phoneNumber, sizeof(phoneNumber), stdin);   
                        phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; // enter 해제
                        printf("\n");
                        printf("고치 전화번호가 맞습니까? (y/n): ");
                        scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장  
                        getchar();    
                        printf("-----------------------------------------------------------------------------\n");
                        if(ynFlag == '0') return;
                    } while (toupper(ynFlag) != 'Y');
                    //이메일
                    do{
                        printf("%10s %s", "", "이메일: ");
                        fgets(emailAddress, sizeof(emailAddress), stdin);   
                        emailAddress[strcspn(emailAddress, "\n")] = '\0'; // enter 해제
                        printf("\n");
                        printf("고치 이메일이 맞습니까? (y/n): ");
                        scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장  
                        getchar();    
                        printf("-----------------------------------------------------------------------------\n");
                        if(ynFlag == '0') return;
                    } while (toupper(ynFlag) != 'Y');

                    system("cls");
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "고치기\n");
                    length += sprintf(buffer + length, "=============================================================================\n\n");
                    length += sprintf(buffer + length, "고칠 줄 번호: %d \n", line);
                    length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", line, addressBook[lines[line - 1]].names, addressBook[lines[line - 1]].addresses, addressBook[lines[line - 1]].phoneNumbers, addressBook[lines[line - 1]].emailAddresses);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length, "%5s 주소: %s \n","", address);
                    length += sprintf(buffer + length, "%5s 전화번호: %s \n","", phoneNumber);
                    length += sprintf(buffer + length, "%5s 이메일: %s \n","", emailAddress);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    printf("%s", buffer);
                    printf("고치시겠습니까? (y/n): ");
                    scanf("%c",&ynFlag);
                    getchar();
                    if(toupper(ynFlag) != 'Y'){
                         //반복끝내기
                        break;
                    }else{
                        system("cls");
                        count = Correct(addressBook, lines[line-1], address, phoneNumber, emailAddress);
                        length = sprintf(buffer, "\n");
                        length += sprintf(buffer + length, "%30s %s","", "고치기\n");
                        length += sprintf(buffer + length, "=============================================================================\n\n");
                        length += sprintf(buffer + length, "%d줄을 고쳤습니다. \n", count + 1);
                        length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                        length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", count + 1, addressBook[count].names, addressBook[count].addresses, addressBook[count].phoneNumbers, addressBook[count].emailAddresses);
                        length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                        printf("%s",buffer);
                        //끝
                        printf("계속 고치시겠습니까? (y/n): ");
                        scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장  
                        getchar();    
                        if(toupper(ynFlag) == 'Y'){
                            break;
                        }
                        else{
                            return;
                        }
                    }
                }
            }
        }
        else{
            system("cls");
            length += sprintf(buffer + length, "%3s %s을(를) 못 찾았습니다.\n", "", name);
            length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
            printf("%s", buffer);
            printf("Enter키 입력하세요.");
            scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장  
        }
    }
    free(buffer); 
}
void FormForArranging(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;

    //system("cls");
    system("cls");
    Arrange(addressBook);
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%25s %s","", "정렬하기 \n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    length+=sprintf(buffer+length,"%-5s %-15s %-15s %-15s %s \n", "Line", "Name", "Address", "Phone", "Email");
    for(int i=0; i < LINES; i++){
        length+=sprintf(buffer +length, "%-5d %-15s %-15s %-15s %s \n", (i+1), addressBook[i].names, addressBook[i].addresses, addressBook[i].phoneNumbers, addressBook[i].emailAddresses);
    }
    length+=sprintf(buffer+length, "-----------------------------------------------------------------------------\n");
    length+=sprintf(buffer+length, "전 화면에 돌아갑니다. \n");
    length+=sprintf(buffer+length, "=> Enter키 누르세요. \n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    getchar();
    free(buffer); 
}

void FormForByEmailAddressses(AddressBook *addressBook){
   char* buffer = (char*) malloc(1024);
    int length;
    char email[256];
    char ynFlag;
    int count;
    int flag = 1;
    //system("cls");
    system("cls");
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%30s %s","", "찾다\n");
    length+=sprintf(buffer+length, "%22s %s","", "[이메일으로 찾기]\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    while (flag)
    {
        printf("%20s %s", "", "이메일: ");
        fgets(email, sizeof(email), stdin);   
        email[strcspn(email, "\n")] = '\0'; // enter 해제
        printf("\n");
        printf("찾으시겠습니까? (y/n): ");
        scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장      
        getchar();
        printf("-----------------------------------------------------------------------------\n");
        if(toupper(ynFlag) == 'N'){
            return;
        }else if(toupper(ynFlag) == 'Y'){
            flag = 0; 
        }
    }

    system("cls");
    length += sprintf(buffer + length,"\n");
    count = FindByEmail(addressBook, email);
    if(count >= 0){
        length += sprintf(buffer + length, "%3s %s을(를) 찾았습니다.\n", "", email);
        length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
        length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
        length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", (count + 1), addressBook[count].names, addressBook[count].addresses, addressBook[count].phoneNumbers, addressBook[count].emailAddresses);
    }else{
        length += sprintf(buffer + length, "%3s %s을(를) 못 찾았습니다.\n", "", email);
    }
    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
    length += sprintf(buffer + length, "%s \n", "찾다 메뉴로 돌아갑니다.");
    length += sprintf(buffer + length, "%s \n", " => Enter키 눌러주세요...");
    printf("%s", buffer);
    free(buffer); 
    getchar();
}

void FormForByName(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    char name[11];
    char ynFlag;
    int line, count;
    int lines[LINES];
    int flag = 1;
    //system("cls");
    system("cls");
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%30s %s","", "찾다\n");
    length+=sprintf(buffer+length, "%22s %s","", "[성명으로 찾기]\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    while (flag)
    {
        printf("%20s %s", "", "성명:");
        fgets(name, sizeof(name), stdin);   
        name[strcspn(name, "\n")] = '\0'; // enter 해제
        printf("\n");
        printf("찾으시겠습니까? (y/n): ");
        scanf("%c", &ynFlag);    // 문자를 입력받아서 변수에 저장      
        getchar();
        printf("-----------------------------------------------------------------------------\n");
        if(toupper(ynFlag) == 'N'){
            return;
        }else if(toupper(ynFlag) == 'Y'){
            flag = 0; 
        }
    }

    system("cls");
    length += sprintf(buffer + length,"\n");
    count = FindByName(addressBook, name,lines);
    if(count > 0){
        length += sprintf(buffer + length, "%3s %s을(를) %d건 찾았습니다.\n", "", name, count);
        length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
        length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
        for(int i=0; i<count; i++){
            length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", lines[i]+1, addressBook[lines[i]].names, addressBook[lines[i]].addresses, addressBook[lines[i]].phoneNumbers, addressBook[lines[i]].emailAddresses);
        }
    }else{
        length += sprintf(buffer + length, "%3s %s을(를) 못 찾았습니다.\n", "", name);
    }
    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
    length += sprintf(buffer + length, "%s \n", "찾다 메뉴로 돌아갑니다.");
    length += sprintf(buffer + length, "%s \n", " => Enter키 눌러주세요...");
    printf("%s", buffer);
    free(buffer); 
    getchar();
}

