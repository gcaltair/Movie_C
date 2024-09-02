//
// Created by G on 2024/8/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
//#include <unistd.h>
//#include <synchapi.h>
#include "user_system.h"
#include "Object/User.h"
#include "Object/admin.h"

static bool getPassword(char *password, int maxLen);

bool user_password_check(User *usr,User_hash_table*userHashTable)
{
    if(!usr) return 0;
    int count=0;char password[20];bool key=0;
    do {
        if(count>=5)
        {
            for (int i = 0; i < 60; ++i) {
                system("cls");
                printf("Your need to wait %d seconds(total 60)",i);
                _sleep(1000);
            }
            count-=3;
            return 0;
        }
        printf("Enter your password:");
        if (!getPassword(password, 20)) return 0;
        
        key=!strcmp(usr->password,password);
        if(!key) {
            printf("\nPassword wrong!\n");
            count++;
            _sleep(500);
            system("cls");
            printf("Enter your ID:%s\n",usr->userID);
        }
    } while (!key);
    return 1;
}
bool admin_password_check(Admin* admin,Admin* admin_list){
    if(!admin) return 0;
    int count=0;char password[20];bool key=0;
    do {
        if(count>=5)
        {
            for (int i = 0; i < 60; ++i) {
                system("cls");
                printf("Your need to wait %d seconds(total 60)",i);
                _sleep(1000);
            }
            count-=3;
            return 0;
        }
        printf("Enter your password:");
        getPassword(password, 20);
        if(!getPassword(password, 20)) return 0;
        key=!strcmp(admin->admin_password,password);
        if(!key) {
            printf("\nPassword wrong!\n");
            count++;
            _sleep(500);
            system("cls");
            printf("Enter your ID:%s\n",admin->admin_id);
        }
    } while (!key);
    return 1;
}



static bool getPassword(char *password, int maxLen) {
    int i = 0;
    char ch;
    while (i < maxLen - 1) {
        ch =getch(); // 读取一个字符但不显示
        if(ch==26||ch==3) return 0;
        if (ch == '\r') { // 检测到回车符（Enter键）
            break;
        } else if (ch == '\b') { // 处理退格键
            if (i > 0) {
                i--;
                printf("\b \b"); // 删除一个字符
            }
        } else {
            password[i++] = ch;

            printf("*"); // 显示星号
        }
    }
    password[i] = '\0'; // 字符串末尾添加终止符
    return 1;
}