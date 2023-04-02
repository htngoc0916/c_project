#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "addressbook.h"
#include "form.h"

void FormForAllView(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    
    system("clear");
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%25s %s","", "주소록 - 전체보기\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    length+=sprintf(buffer+length,"%-5s %-15s %-15s %-15s %s \n", "Line", "Name", "Address", "Phone", "Email");
    for(int i=0; i < LINES; i++){
        length+=sprintf(buffer +length, "%-5d %-15s %-15s %-15s %s \n", (i+1), addressBook->personal[i].names, addressBook->personal[i].addresses, addressBook->personal[i].phoneNumbers, addressBook->personal[i].emailAddresses);
    }
    length+=sprintf(buffer+length, "-----------------------------------------------------------------------------\n");
    length+=sprintf(buffer+length, "전 화면에 돌아갑니다. \n");
    length+=sprintf(buffer+length, "=> Enter키 누르세요. \n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    free(buffer); 
    getchar();
    //char c = getc(stdin); 
}
void FormRecording(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);

    int length;
    char name[11];
    char emailAddress[255];
    char address[256];
    char phoneNumber[18];
    int line = -1; //result = -1: 공간이 없음, result > 0 성공
    char ynFlag;
    int flag = 1;

    while(flag){
        //system("clear"); //windows
        system("clear"); //macbook
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
                system("clear"); //macbook
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
            //getchar(); 
            system("clear"); //macbook
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
            system("clear"); //macbook
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
        //system("clear");
        system("clear");
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
        system("clear");
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
                system("clear");
                if(checkLine == 'N'){
                    length += sprintf(buffer + length, "검색 결과: \n");
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i + 1;
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
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
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
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
                system("clear");
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
            system("clear");
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
        system("clear");
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
                system("clear");
                if(checkLine == 'N'){
                    length += sprintf(buffer + length, "고칠 %s를(을) %d건 찾았습니다.\n", name, count);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
                    length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i+1; //line 입력 체크 시 필요
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
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
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
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
                system("clear");
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
                    length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", line, addressBook->personal[lines[line - 1]].names, addressBook->personal[lines[line - 1]].addresses, addressBook->personal[lines[line - 1]].phoneNumbers, addressBook->personal[lines[line - 1]].emailAddresses);
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

                    system("clear");
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "고치기\n");
                    length += sprintf(buffer + length, "=============================================================================\n\n");
                    length += sprintf(buffer + length, "고칠 줄 번호: %d \n", line);
                    length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", line, addressBook->personal[lines[line - 1]].names, addressBook->personal[lines[line - 1]].addresses, addressBook->personal[lines[line - 1]].phoneNumbers, addressBook->personal[lines[line - 1]].emailAddresses);
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
                        system("clear");
                        count = Correct(addressBook, lines[line-1], address, phoneNumber, emailAddress);
                        length = sprintf(buffer, "\n");
                        length += sprintf(buffer + length, "%30s %s","", "고치기\n");
                        length += sprintf(buffer + length, "=============================================================================\n\n");
                        length += sprintf(buffer + length, "%d줄을 고쳤습니다. \n", count + 1);
                        length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                        length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", count + 1, addressBook->personal[count].names, addressBook->personal[count].addresses, addressBook->personal[count].phoneNumbers, addressBook->personal[count].emailAddresses);
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
            system("clear");
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

    //system("clear");
    system("clear");
    Arrange(addressBook);
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%25s %s","", "정렬하기 \n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    length+=sprintf(buffer+length,"%-5s %-15s %-15s %-15s %s \n", "Line", "Name", "Address", "Phone", "Email");
    for(int i=0; i < LINES; i++){
        length+=sprintf(buffer +length, "%-5d %-15s %-15s %-15s %s \n", (i+1), addressBook->personal[i].names, addressBook->personal[i].addresses, addressBook->personal[i].phoneNumbers, addressBook->personal[i].emailAddresses);
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
    //system("clear");
    system("clear");
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

    system("clear");
    length += sprintf(buffer + length,"\n");
    count = FindByEmail(addressBook, email);
    if(count >= 0){
        length += sprintf(buffer + length, "%3s %s을(를) 찾았습니다.\n", "", email);
        length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
        length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
        length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", (count + 1), addressBook->personal[count].names, addressBook->personal[count].addresses, addressBook->personal[count].phoneNumbers, addressBook->personal[count].emailAddresses);
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
    int count;
    int lines[LINES];
    int flag = 1;
    //system("clear");
    system("clear");
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

    system("clear");
    length += sprintf(buffer + length,"\n");
    count = FindByName(addressBook, name,lines);
    if(count > 0){
        length += sprintf(buffer + length, "%3s %s을(를) %d건 찾았습니다.\n", "", name, count);
        length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
        length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
        for(int i=0; i<count; i++){
            length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", lines[i]+1, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
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

