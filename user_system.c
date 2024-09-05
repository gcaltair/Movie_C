//
// Created by G on 2024/8/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
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
#include"Object/Theater.h"
#include"Object/Cinema.h"
#include"Structure File/interval_tree.h"
#include"Structure File/linked_list.h"
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
bool change_password(const char* current_password,char* new_password) {
    char input_password[20]; // 用于存储用户输入的当前密码
    char new_password1[20];  // 用于存储用户第一次输入的新密码
    char new_password2[20];  // 用于存储用户第二次输入的新密码

    // 输入当前密码
    printf("请输入当前密码: ");
    if (!getPassword(input_password, sizeof(input_password))) {
        printf("\n密码输入失败。\n");
        return false;
    }
    printf("\n");

    // 验证当前密码是否正确
    if (strcmp(input_password, current_password) != 0) {
        printf("当前密码错误！\n");
        return false;
    }

    // 输入新密码（第一次）
    printf("请输入新密码: ");
    if (!getPassword(new_password1, sizeof(new_password1))) {
        printf("\n密码输入失败。\n");
        return false;
    }
    printf("\n");

    // 输入新密码（第二次）
    printf("请再次输入新密码: ");
    if (!getPassword(new_password2, sizeof(new_password2))) {
        printf("\n密码输入失败。\n");
        return false;
    }
    printf("\n");

    // 验证两次新密码是否一致
    if (strcmp(new_password1, new_password2) != 0) {
        printf("两次输入的新密码不一致！\n");
        return false;
    }

    
    // 在这里可以保存新密码
    strcpy(new_password, new_password1);

    return true;
}

double get_user_input_double(double min, double max) {
    double option;
    char c;

    while (1) {
        printf("请输入一个数值 (范围: %.2f - %.2f): ", min, max);

        // 尝试读取一个 double 输入
        if (scanf("%lf", &option) == 1) {
            // 检查输入是否在指定范围内
            if (option >= min && option <= max) {
                // 清理输入缓冲区
                while ((c = getchar()) != '\n' && c != EOF) {}
                return option;
            }
            else {
                printf("输入无效，超出范围，请重新输入。\n");
            }
        }
        else {
            printf("输入无效，请输入一个数值。\n");

            // 清理输入缓冲区，处理非 double 输入
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
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
void movie_print_for_user(const Movie* movie)
{
    if (movie == NULL) { printf("当前信息为空"); return; }
    printf("影院名称：%s\n", movie->theater->cinema->cinema_name);
    printf("影厅名称：%s\n", movie->theater->theater_name);
    printf("影厅类型：%s\n", movie->theater->theater_type);
    printf("场次类型：%s\n", movie->film->film_language);
    printf("开始时间: %s\n", movie->start_time);
    printf("结束时间: %s\n", movie->end_time);
    printf("余票数: %d\n", movie->remaining_ticket);
    printf("价格: %.2f\n", movie->price);
    printf("折扣: %.2f\n", movie->discount);
    printf("------------\n");
}
void movie_list_print(const Movie* movie_list)
{
    while (movie_list)
    {
        movie_print(movie_list);
        movie_list = movie_list->next;
    }
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
Movie* movie_choose(Movie* new_movie_list,Movie_hash_table* hash_table)
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
    return find_movie_in_hash_table(hash_table,new_head_for_option->movie_id);
}
int for_user_movie_choose(Movie* new_movie_list, Movie* movie_hash_table)
{
    int count = 0;
    if (!new_movie_list)
    {
        printf("当天无可播放影片\n");
        return;
    }
    Movie* new_head_for_option = new_movie_list;
    while (new_movie_list)
    {
        count++;
        printf("序号 %d:\n", count);
        movie_print_for_user(new_movie_list);
        new_movie_list = new_movie_list->next;
    }
    printf("请输入你的选择(输入0退出):");
    int option = get_user_input_int(count);
    if (option == 0) return NULL;
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next;
    }
    return find_movie_in_hash_table(movie_hash_table, new_head_for_option->movie_id);
    
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
Theater* theater_choose_for_admin(Theater* new_theater_list,Theater_hash_table* hash_table)
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
    return find_theater_in_hash_table(hash_table,new_head_for_option->theater_id);  
}
int get_time_format_hours_and_minutes(const char* time_str) {
    // 检查时间字符串的长度是否为5，并且第三个字符是否为 ':'
    if (strlen(time_str) != 5 || time_str[2] != ':') {
        return -1; // 无效时间格式
    }

    // 检查小时和分钟的字符是否为数字
    for (int i = 0; i < 5; ++i) {
        if (i == 2) continue; // 跳过 ':'
        if (!isdigit(time_str[i])) {
            return -1; // 非数字字符
        }
    }

    // 将小时和分钟从字符串中提取出来
    int hours = (time_str[0] - '0') * 10 + (time_str[1] - '0');
    int minutes = (time_str[3] - '0') * 10 + (time_str[4] - '0');

    // 检查小时和分钟是否在有效范围内
    if (hours < 0 || hours > 24 || minutes < 0 || minutes > 59) {
        return -1; // 无效时间范围
    }

    return hours*60+minutes; // 合法时间格式
}
int date_to_days(const char* date) {
    struct tm tm_date = { 0 };
    // 解析日期字符串
    if (sscanf(date, "%d-%d-%d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday) != 3) printf("读取时间错误\n");

    // 将年份调整为从1900年开始
    tm_date.tm_year -= 1900;
    // 月份从0开始，所以减去1
    tm_date.tm_mon -= 1;

    // 获取时间戳并转为天数
    time_t time_since_epoch = mktime(&tm_date);
    return (int)(time_since_epoch / (60 * 60 * 24));
}
void days_to_date(int days, char* date) {
    // 确保缓冲区足够大，以防止溢出
    // 先将 days 转换为 time_t 类型
    time_t time_since_epoch = (time_t)days * 60 * 60 * 24;

    // 使用 gmtime 转换为 tm 结构体
    struct tm* tm_date = gmtime(&time_since_epoch);

    // 确保 tm_date 非空
    if (tm_date != NULL) {
        // 格式化为字符串
        strftime(date, 20, "%Y-%m-%d ", tm_date);
    }
    else {
        // 如果 tm_date 是 NULL，则处理错误情况
        strncpy(date, "Invalid Date", 20);
    }
}
int admin_add_a_movie_to_theater(Theater* theater, Film* film, Movie* movie_list, Movie_hash_table* movie_hash_table) {

    while (1) {
        char movie_id[50];
        char start_time[20];
        int remaining_ticket=theater->theater_capacity;
        double price, discount;
        
        int start_min = 0;
        int end_min = 0;
        while (1) {
            while (1) {
                printf("输入电影的开始时间 (格式: HH:MM): ");// 输入电影的开始时间
                fgets(start_time, sizeof(start_time), stdin);
                start_time[strcspn(start_time, "\n")] = 0;
                start_min = get_time_format_hours_and_minutes(start_time);
                if (start_min != -1)
                {
                    end_min = start_min + film->film_time;
                    break;
                }
                printf("输入错误,请重新输入\n");
            }

            if (is_overlapping(theater->time_line->root, start_min-5, end_min+5)) //判断是否重叠
            {
                printf("排片时间重叠或同影厅间隔时间不足!是否重新输入?(1/0)\n");
                int option_lapping = get_user_input_int(1);
                if (option_lapping) continue;
                else
                    return 0;
            }
            int status = is_avoid_flow(theater->cinema, start_min, end_min);
            
            if (status)
            {
                printf("未能避开人流,当前约与%d个场次有人流冲突，是否确认?(1/0)\n",status);
                int option_flow = get_user_input_int(1);
                if (!option_flow) continue;
            }
            break;
        }

        printf("输入票价: ");
        price=get_user_input_double(0, 1000);
        //getchar(); // 清除缓冲区中的换行符

        // 输入折扣
        printf("输入折扣 (例如 0.9 表示九折): ");
        discount = get_user_input_double(0, 1);
        //getchar(); // 清除缓冲区中的换行符

        char start_date[20]="2024-09-04";
        int start_day = date_to_days(start_date);
        
        int duration_day = 10;
        
        char end_time[20];
        minutes_to_hhmm(end_min, end_time);
        // 显示信息确认
        printf("您的信息是:\n");
        printf("开始时间: %s\n", start_time);
        printf("结束时间: %s\n", end_time);
        printf("剩余票数: %d\n", remaining_ticket);
        printf("票价: %.2lf\n", price);
        printf("折扣: %.2lf\n", discount);
        printf("开始日期：%s\n", start_date);
        printf("持续天数：%d\n", duration_day);
        printf("确认添加吗? (1:确认 0:取消添加 2:重新输入): ");
        int option = get_user_input_int(2);
        if (option == 0) return 0;
        if (option == 2) continue;
        for (int i = 0; i < duration_day; ++i)
        {
            // 确保Theater和Film存在
            if (theater == NULL || film == NULL) {
                printf("Theater或Film对象为空，无法添加电影。\n");
                return 2;
            }
            char temp1_id[10];
            strcpy(movie_id, theater->cinema->cinema_alphabet);
            sprintf(temp1_id, "%05d", movie_hash_table->count+1);
            strcat(movie_id, temp1_id);

            char date_time_start[20]; char date_time_end[20];
            days_to_date(start_day, date_time_start);
            days_to_date(start_day, date_time_end);
            strcat(date_time_start, start_time);
            strcat(date_time_end, end_time);
            start_day++;

            
            Movie* new_movie = movie_create(movie_hash_table, movie_id, film->film_id, film, theater->theater_id, theater, date_time_start, date_time_end, remaining_ticket, price, discount);
            if (new_movie == NULL) {
                return 2;
            }
            
            // 将新电影加入链表
            movie_add_to_list(&movie_list, new_movie);
        }
        return 1;
    }
}
int my_min(int a,int b)
{
    return a < b ? a : b;
}

//传入真实Film和Theater
int add_movie_to_theater_dev(Film* film, Theater* theater, char* start_time, char* end_time, Movie_hash_table* movie_hash_table, Movie* movie_list)
{
    char movie_id[50];
    int remaining_ticket = theater->theater_capacity;
    double price, discount;
    while (1)
    {
        printf("输入票价: ");
        price = get_user_input_double(0, 1000);
        //getchar(); // 清除缓冲区中的换行符

        // 输入折扣
        printf("输入折扣 (例如 0.9 表示九折): ");
        discount = get_user_input_double(0, 1);
        //getchar(); // 清除缓冲区中的换行符

        char start_date[20] = "2024-09-04";
        int start_day = date_to_days(start_date);

        int duration_day = 10;

        // 显示信息确认
        printf("您的信息是:\n");
        printf("开始时间: %s\n", start_time);
        printf("结束时间: %s\n", end_time);
        printf("剩余票数: %d\n", remaining_ticket);
        printf("票价: %.2lf\n", price);
        printf("折扣: %.2lf\n", discount);
        printf("开始日期：%s\n", start_date);
        printf("持续天数：%d\n", duration_day);
        printf("确认添加吗? (1:确认 0:取消添加 2:重新输入): ");
        int option = get_user_input_int(2);
        if (option == 0) return 0;
        if (option == 2) continue;
        for (int i = 0; i < duration_day; ++i)
        {
            // 确保Theater和Film存在
            if (theater == NULL || film == NULL) {
                printf("Theater或Film对象为空，无法添加电影。\n");
                return 2;
            }
            char temp1_id[10];
            strcpy(movie_id, theater->cinema->cinema_alphabet);
            sprintf(temp1_id, "%05d", movie_hash_table->count + 1);
            strcat(movie_id, temp1_id);

            char date_time_start[20]; char date_time_end[20];
            days_to_date(start_day, date_time_start);
            days_to_date(start_day, date_time_end);
            strcat(date_time_start, start_time);
            strcat(date_time_end, end_time);
            start_day++;


            Movie* new_movie = movie_create(movie_hash_table, movie_id, film->film_id, film, theater->theater_id, theater, date_time_start, date_time_end, remaining_ticket, price, discount);
            if (new_movie == NULL) {
                return 2;
            }

            // 将新电影加入链表
            movie_add_to_list(&movie_list, new_movie);
        }
        return 1;
    }
}
int admin_auto_find_movie_to_theater(Cinema* cinema,Film* film,Theater_hash_table* theater_hash_table,Movie_hash_table* movie_hash_table,Movie* movie_list)
{
    int time = film->film_time;
    Theater* copied_theater_list = theater_list_create_by_cinema(cinema, theater_hash_table);
    Theater* free_copied_list = copied_theater_list;
    Theater* re__iterate_head = copied_theater_list;
    int list_cout = 1;

    int start_min = 0; int end_min = 1440;//最为合适的实际空闲时段
    while (copied_theater_list) { //寻找最合适的时间
        int count = 1;
        
        int number = 0;//用于获得时间段
        interval* free_period = find_free_times_interval(copied_theater_list->time_line, 540, 1380, &number);//搜索9:00到23:00的空余时段
        for (int i = 0; i < number; ++i)
        {
            free_period[i].start += 5; free_period[i].end -= 5; //获得实际空闲时段
            int differ = free_period[i].end - free_period[i].start - time;
            if (differ>0 && (differ< end_min - start_min))//如果新的实际空闲时段比之前的大
            {
                list_cout = count;
                start_min = free_period[i].start;
                end_min = free_period[i].end;
            }
        }
        copied_theater_list = copied_theater_list->next;
        count++;
    }
    //最终得到theater以及的实际最佳时段，下面在实际最佳时段中筛选人流最小
    
    int pre_flow_theater = 20;

    for (int i = start_min; i + time <= end_min; i++)
    {
        int now_flow_theater = is_avoid_flow(cinema, start_min, start_min + time);//现在的人流场次
        if ((pre_flow_theater -now_flow_theater ) > 0) //如果之前的比现在的多
        {
            pre_flow_theater = now_flow_theater;
            start_min = i; 
        }
    }
    //最后得到pre_flow_theater和start_min


    for (int i = 1; i < list_cout; ++i) //遍历获得影厅信息
    {
        re__iterate_head = re__iterate_head->next;
    }

    printf("系统为您选择的时段是：\n");
    theater_print(re__iterate_head);
    print_start_and_end_time(start_min, end_min);
    if (pre_flow_theater)
    {
        printf("存在%d个人流冲突场次", pre_flow_theater);
    }
    printf("是否确认?(1/0)\n");
    int option = get_user_input_int(1);
    if (!option) return 0;
    //得到了电影，影厅，开始结束时段，现在排片
    char start_time[20]; char end_time[20];
    minutes_to_hhmm(start_min, start_time);
    minutes_to_hhmm(end_min, end_time);
    int status = add_movie_to_theater_dev(film, find_theater_in_hash_table(theater_hash_table, re__iterate_head->theater_id), start_time, end_time, movie_hash_table, movie_list);
    theater_free_copied_list(free_copied_list);
    if (status == 0) return 0;
    return 1;
}
void print_start_and_end_time(int start_min, int end_min)
{
    char start_time[20]; char end_time[20];
    minutes_to_hhmm(start_min, start_time);
    minutes_to_hhmm(end_min, end_time);
    printf("开始时间: %s\n", start_time);
    printf("结束时间: %s\n", end_time);
}
Film* film_choose(Film* new_film_list,Film_hash_table* hash_table)
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

    return find_film_in_hash_table_by_id(hash_table,new_head_for_option->film_id);  // 返回用户选择的 Film
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
        printf("输入影厅名字: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        printf("输入影厅容量: ");
        capacity = get_user_input_int(500);
        
        printf("输入影厅类型: ");
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
// 判断电话号码是否合法的函数
int is_valid_phone_number(const char* phone) {
    // 判断长度是否为11位
    if (strlen(phone) != 11) {
        return 0; // 长度不合法
    }

    // 判断首位是否为1
    if (phone[0] != '1') {
        return 0; // 首位不是1
    }

    // 判断是否全为数字
    for (int i = 0; i < 11; i++) {
        if (!isdigit(phone[i])) {
            return 0; // 发现非数字字符
        }
    }

    return 1; // 合法电话号码
}
// 获取合法的电话号码，并返回char*类型
char* get_valid_phone_number() {
    char* phone = (char*)malloc(12 * sizeof(char)); // 11位数字加1个结束符'\0'

    while (1) {
        printf("请输入新的电话号码: ");
        scanf("%s", phone);

        if (is_valid_phone_number(phone)) {
            return phone; // 合法，返回电话号码
        }
        else {
            printf("输入不合法，请重新输入。\n");
        }
    }
}
// 验证邮箱是否合法的函数
bool is_valid_email(const char* email) {
    int at_pos = -1;
    int dot_pos = -1;
    int len = strlen(email);

    // 邮箱长度至少需要有 5 个字符（如 a@b.co）
    if (len < 5) {
        return false;
    }

    // 遍历邮箱字符串
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            // 如果有多个 '@' 符号，则不合法
            if (at_pos != -1) {
                return false;
            }
            at_pos = i;
        }
        if (email[i] == '.') {
            // 记录最后一个 '.' 符号的位置
            dot_pos = i;
        }
    }

    // 检查 '@' 符号的位置及其后面是否有 '.'
    if (at_pos == -1 || dot_pos == -1 || at_pos == 0 || dot_pos <= at_pos + 1 || dot_pos == len - 1) {
        return false;
    }

    // 进一步检查是否包含无效字符（非字母、数字、下划线、点和连字符）
    for (int i = 0; i < len; i++) {
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.' && email[i] != '_' && email[i] != '-') {
            return false;
        }
    }

    return true;
}

// 获取合法邮箱输入的函数
void get_valid_email(char* email, int max_length) {
    while (1) {
        printf("请输入您的邮箱地址: ");
        fgets(email, max_length, stdin);

        // 去除末尾的换行符
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }

        // 验证邮箱是否合法
        if (is_valid_email(email)) {
            printf("邮箱地址合法。\n");
            break;
        }
        else {
            printf("邮箱地址不合法，请重新输入。\n");
        }
    }
}
void get_user_input_string(char* input, int max_length) {
    printf("请输入最多%d位的字符串: ", max_length);
    fgets(input, max_length + 1, stdin);  // 读取输入，最多max_length个字符

    // 去除末尾的换行符（如果有）
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
}
void display_user_greet()
{
    printf("*************************************************\n");
    printf("*               欢迎使用云上影院                *\n");
    printf("*************************************************\n");
    printf("* 1. 电影购票                                   *\n");
    printf("* 2. 正在热映                                   *\n");
    printf("* 3. 我的订单                                   *\n");
    printf("* 4. 个人中心                                   *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void display_purchase_ticket()
{
    printf("*************************************************\n");
    printf("*                 电影购票                      *\n");
    printf("*************************************************\n");
    printf("* 1. 影片查询                                   *\n");
    printf("* 2. 影片+影院查询                              *\n");
    printf("* 3. 优惠折扣                                   *\n");
    printf("* 4. 自定义查询                                 *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void admin_greet()
{
    printf("*************************************************\n");
    printf("*             欢迎使用电影院管理系统            *\n");
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
void display_admin_modify_info_menu()
{
    printf("*************************************************\n");
    printf("*               修改管理员信息                  *\n");
    printf("*************************************************\n");
    printf("* 1. 修改ID                                     *\n");
    printf("* 2. 修改姓名                                   *\n");
    printf("* 3. 修改电话                                   *\n");
    printf("* 4. 修改密码                                   *\n");
    printf("* 5. 修改邮箱                                   *\n");
    printf("*                                               *\n");
    printf("* 0. 退出                                       *\n");
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

void display_user_movie_operate_main_menu() {
    printf("\n==== 操作主菜单 ====\n");
    printf("1. 排序\n");
    printf("2. 筛选\n");
    printf("3. 查看与选择场次\n\n");
    printf("0. 返回购票（重置操作结果）\n");

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
void display_user_sort_menu() {
    printf("\n==== 排序菜单 ====\n");
    printf("1. 价格 (升序)\n");
    printf("2. 开始时间 (升序)\n");
    printf("3. 剩余票数 (升序)\n\n");
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
void display_user_filter_menu() {
    printf("\n==== 筛选菜单 ====\n");
    printf("1. 时间段\n");
    printf("2. 影片类型\n");
    printf("3. 电影院\n");
    printf("4. 影厅类型\n\n");
    printf("0. 返回操作主菜单\n");
}
