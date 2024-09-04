//
// Created by G on 2024/8/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include <stdbool.h>
#include <conio.h>
//#include <unistd.h>
//#include <synchapi.h>
#include"Object/Movie.h"
#include "user_system.h"
#include "Object/User.h"
#include "Object/admin.h"
#include"Object/Film.h"
#include"Structure File/interval_tree.h"
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
        if(max!=0)
        printf("enter your option 0-%d:", max);
        else
            printf("输入0以继续...\n");
        

        // 尝试读取一个整数输入
        if (scanf("%d", &option) == 1) {
            // 检查输入是否在指定范围内
            if (option >= 0 && option <= max) {
                // 清理输入缓冲区
                while ((c = getchar()) != '\n' && c != EOF) {}
                return option;
            }
            else {
                printf("invalid input,"); 
            }
        }
        else {
            printf("invalid input,");
            
            // 清理输入缓冲区，处理非整数输入
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
}
// 检查日期格式是否为 YYYY-MM-DD
bool is_valid_date_format(const char* date) {
    // 长度必须为 10
    if (strlen(date) != 10) {
        return false;
    }

    // 检查每一部分是否符合要求
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') {
                return false;
            }
        }
        else {
            if (!isdigit(date[i])) {
                return false;
            }
        }
    }

    return true;
}

// 获取用户输入并确保格式正确
int get_valid_date_input(char* date) {
    while (true) {
        printf("请输入日期（格式: YYYY-MM-DD）：");
        scanf("%s", date);

        if (is_valid_date_format(date)) {
            break;
        }
        //else if (strcmp(date, "exit") == 0)
        //{
        //    return 1;
        //}
        else {
            printf("输入格式错误，请重新输入。\n");
        }
    }
    return 0;
}
void movie_print(const Movie* movie) {
    if (movie == NULL) { printf("当前信息为空"); return; }
    printf("场次ID: %s\n", movie->movie_id);
    printf("电影ID: %s\n", movie->film_id);
    printf("影厅ID: %s\n", movie->theater_id);
    printf("开始时间: %s\n", movie->start_time);
    printf("结束时间: %s\n", movie->end_time);
    printf("余票数: %d\n", movie->remaining_ticket);
    printf("价格: %.2f\n", movie->price);
    printf("折扣: %.2f\n", movie->discount);
    printf("------------\n");
}
void film_print(const Film* film) {
    if (film) {
        printf("Film ID: %s\n", film->film_id);
        printf("Name: %s\n", film->film_name);
        printf("Type: %s\n", film->film_type);
        printf("Language: %s\n", film->film_language);
        printf("Summary: %s\n", film->film_summary);
        printf("Rating: %d\n", film->film_rating);
    }
}
Movie* movie_choose(Movie* new_movie_list)
{
    int count = 0;
    Movie* new_head_for_option = new_movie_list;
    while (new_movie_list)
    {
        count++;
        printf("序号 %d:\n", count);
        movie_print(new_movie_list);
        new_movie_list = new_movie_list->next;
    }
    printf("请输入你的选择(输入0退出):");
    int option = get_user_input_int(count);
    if (option == 0) return NULL;
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next;
    }
    return new_head_for_option;
}
void theater_print(const Theater* theater) {
    if (theater == NULL) {
        printf("Theater Data is NULL.\n");
        return;
    }

    printf("Theater ID: %s\n", theater->theater_id);
    printf("Theater Name: %s\n", theater->theater_name);
    printf("Capacity: %d\n", theater->theater_capacity);
    printf("Cinema ID: %s\n", theater->cinema_id);
    printf("Theater Type: %s\n", theater->theater_type);
    printf("------------\n");
}
Theater* theater_choose_for_admin(Theater* new_theater_list)
{
    int count = 0;
    Theater* new_head_for_option = new_theater_list;
    while (new_theater_list)
    {
        count++;
        printf("序号 %d:\n", count);
        printf("影厅名:%s\n", new_theater_list->theater_name);  
        find_free_times(new_theater_list->time_line,0,1440);
        new_theater_list = new_theater_list->next;
    }
    printf("请输入你的选择(输入0退出): ");
    int option = get_user_input_int(count);  
    if (option == 0) return NULL;  
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next; 
    }
    return new_head_for_option;  
}
int admin_add_a_movie_to_theater(Theater* theater,Film* film);

Film* film_choose(Film* new_film_list)
{
    int count = 0;
    Film* new_head_for_option = new_film_list;

    // 打印所有 Film 的信息，并计算总数
    while (new_film_list)
    {
        count++;
        printf("序号 %d:\n", count);
        film_print(new_film_list);  // 打印每个 Film 的详细信息
        new_film_list = new_film_list->next;
    }

    // 获取用户输入的选择
    printf("请输入你的选择(输入0退出): ");
    int option = get_user_input_int(count);  // 获取用户输入的整数
    if (option == 0) return NULL;  // 如果用户选择退出，则返回 NULL

    // 根据用户的选择找到对应的 Film
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next;
    }

    return new_head_for_option;  // 返回用户选择的 Film
}

void minutes_to_hhmm(int minutes, char* buffer) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    sprintf(buffer, "%02d:%02d", hours, mins);
}
int hhmm_to_minutes(const char* hhmm) {
    int hours, minutes;
    sscanf(hhmm, "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}
void press_zero_to_continue()
{
    while (get_user_input_int(0));
    return;
}
int admin_add_a_theater(Admin* admin_now, Theater* theater_list, Theater_hash_table* theater_hash_table) {
    while (1) {
        char theater_id[50];
        char name[100];
        int capacity;
        char* cinema_id = admin_now->cinema_id;
        char type[50];
        int temp_count = theater_hash_table->count + 1;
        sprintf(theater_id, "T%05d", temp_count);
        printf("Enter Theater Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        printf("Enter Theater Capacity: ");
        capacity = get_user_input_int(500);
        
        printf("Enter Theater Type:");
        fgets(type, sizeof(type), stdin);
        type[strcspn(type, "\n")] = 0;

        printf("您的信息是:\n");
        printf("%s\n", name);
        printf("%d\n", capacity);
        printf("%s\n", type);
        printf("确认添加吗? (1:确认 0:取消添加 2:重新输入):");
        int option = get_user_input_int(2);
        if (option == 0) return 0;
        if (option == 2) continue;
        // 获取 Cinema 结构体的指针，根据 Cinema ID 查找
        Cinema* cinema = admin_now->cinema;
        if (cinema == NULL) {
            return 2;
        }

        // 创建新 Theater 并加入链表和哈希表
        Theater* new_theater = theater_create(theater_hash_table, theater_id, name, capacity, cinema, cinema_id, type);
        if (new_theater == NULL) {        
            return 2;
        }

        theater_add_to_list(&theater_list, new_theater);
        return 1;
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
    printf("*                  订单管理                     *\n");
    printf("*************************************************\n");
    printf("* 1. 查看与统计用户订单                         *\n");
    printf("* 2. 订单搜索                                   *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void admin_theater_manage_greet()
{
    printf("*************************************************\n");
    printf("*                  影厅管理                     *\n");
    printf("*************************************************\n");
    printf("* 1. 添加影厅                                   *\n");
    printf("* 2. 查看影厅                                   *\n");
    //printf("* 3. 删除影厅                                   *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void display_admin_movie_manage_greet()
{
    printf("*************************************************\n");
    printf("*                  场次管理                     *\n");
    printf("*************************************************\n");
    printf("* 1. 智能排片                                   *\n");
    printf("* 2. 查看排片                                   *\n");
    printf("* 3. 自定义排片                                 *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
//场次操作菜单
void display_movie_operate_main_menu() {
    printf("\n==== 操作主菜单 ====\n");
    printf("1. 排序\n");
    printf("2. 筛选\n");
    printf("3. 查看与选择场次\n");
    printf("4. 查看影院在当前结果的收入\n\n");
    printf("0. 返回订单管理（重置操作结果）\n");
    
}
//管理员排序菜单
void display_admin_sort_menu() {
    printf("\n==== 排序菜单 ====\n");
    printf("1. 上座率 (降序)\n");
    printf("2. 价格 (升序)\n");
    printf("3. 场次收入 (降序)\n");
    printf("4. 开始时间 (升序)\n");
    printf("5. 剩余票数 (升序)\n\n");
    printf("0. 返回操作主菜单\n");
}
void display_admin_filter_menu() {
    printf("\n==== 筛选菜单 ====\n");
    printf("1. 时间段\n");
    printf("2. 已放映\n");
    printf("3. 未放映\n");
    printf("4. 当日日期\n");
    printf("5. 影片类型\n");
    printf("6. 电影院ID\n\n");
    printf("0. 返回操作主菜单\n");
}

