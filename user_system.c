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
#include"Object/Movie.h"
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
        ch =_getch(); // 读取一个字符但不显示
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
int get_user_input_int(int max) {
    int option;
    char c;

    while (1) {
        printf("enter your option 0-%d:", max);

        // 尝试读取一个整数输入
        if (scanf("%d", &option) == 1) {
            // 检查输入是否在指定范围内
            if (option >= 0 && option <= max) {
                // 清理输入缓冲区
                while ((c = getchar()) != '\n' && c != EOF) {}
                return option;
            }
            else {
                printf("invalid input please enter number between 0 to %d.", max);
                
            }
        }
        else {
            printf("invalid input please enter number between 0 to %d.\n",max);
            
            // 清理输入缓冲区，处理非整数输入
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
}

void admin_greet()
{
    printf("*************************************************\n");
    printf("*               欢迎使用电影院管理系统          *\n");
    printf("*************************************************\n");
    printf("* 1. 订单管理                                   *\n");
    printf("* 2. 影厅管理                                   *\n");
    printf("* 3. 场次管理                                   *\n");
    printf("* 4. 个人信息管理                               *\n");
    printf("* 5. 用户信息管理                               *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void admin_order_manage_greet()
{
    printf("*************************************************\n");
    printf("*                 订单管理                      *\n");
    printf("*************************************************\n");
    printf("* 1. 查看用户订单                               *\n");
    printf("* 2. 统计用户订单                               *\n");
    printf("* 3. 订单搜索                                   *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
//场次操作菜单
void display_movie_operate_main_menu() {
    printf("\n==== 操作主菜单 ====\n");
    printf("1. Sort\n");
    printf("2. Filter\n");
    printf("3. 选择场次\n\n");
    printf("0. 返回订单管理（reset排序结果）\n");
    
}
//管理员排序菜单
void display_admin_sort_menu() {
    printf("\n==== 排序菜单 ====\n");
    printf("1. 上座率 (降序)\n");
    printf("2. 价格 (升序)\n");
    printf("3. 场次收入 (降序)\n");
    printf("4. 开始时间 (升序)\n");
    printf("5. 剩余票数 (升序)\n\n");
    printf("0. 返回主菜单\n");
}