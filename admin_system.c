#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<ctype.h>
#include <stdbool.h>
#include <conio.h>
#include"Object/Movie.h"
#include "user_system.h"
#include "Object/User.h"
#include "Object/admin.h"
#include"Object/Film.h"
#include"Object/Theater.h"
#include"Object/Cinema.h"
#include"Object/Order.h"
#include"Structure File/interval_tree.h"
#include"Structure File/linked_list.h"
#include "Structure File/io_system.h"
#include "admin_system.h"

void admin_order_manage(Admin* admin_now, Theater_hash_table* theaterHashTable, Movie_hash_table* movieHashTable, Order_hash_table* orderHashTable,Order* order_list)
{
    while (1)
    {
        system("cls");
        admin_order_manage_greet(); char text[20];
        int option = get_user_input_int(2);
        switch (option)
        {
        case 1:
            admin_view_and_count_order(admin_now, theaterHashTable, movieHashTable,order_list);
            break;
        case 2:
            while (1)
            {

                printf("请输入订单号：\n");
                get_user_input_string(text, 20);
                Order* order = find_order_in_hash_table(orderHashTable, text);
                if (!order)
                {
                    printf("未找到订单,是否重新输入?(1/0)");
                    int cer = get_user_input_int(1);
                    if (!cer) break;
                }
            }
            break;
        default:
            return; break;
        }
    }

}
static Movie* for_admin_movie_filter(Movie* new_movie_list)
{
    while (1)
    {
        system("cls");
        display_admin_filter_menu();
        int option = get_user_input_int(6);
        Movie* free_temp = new_movie_list;
        //时间段，已放映，未放映，当日日期，影片类型，电影院id
        char start_time[20]; char end_time[20]; char text[20];
        switch (option)
        {
        case 1:
            printf("请分别输入起止时间\n");
            //if (get_valid_date_input(start_time) == 1 || get_valid_date_input(end_time) == 1) { break; }
            get_valid_date_input(start_time);
            get_valid_date_input(end_time);
            printf("对时间段 %s-%s 的筛选已完成", start_time, end_time);
            strcat(start_time, " 00:00:00");
            strcat(end_time, " 00:00:00");
            char* context[] = { start_time,end_time };
            new_movie_list = movie_operation_filter(new_movie_list, 1, context);
            break;

        case 2:
            new_movie_list = movie_filter_by_played(new_movie_list);
            printf("已筛选已放映场次\n");
            break;
        case 3:
            new_movie_list = movie_filter_by_not_played(new_movie_list);
            printf("已筛选未放映场次\n");
            break;
        case 4:
            new_movie_list = movie_filter_by_current_date(new_movie_list);
            printf("已筛选当日场次\n");
            break;
        case 5:
            printf("请输入影片类型:");
            scanf("%s", text);
            new_movie_list = movie_operation_filter(new_movie_list, 5, text);
            printf("已筛选影片类型: %s\n", text);
            break;
        case 6:
            printf("请输入电影院id:");
            scanf("%s", text);
            new_movie_list = movie_operation_filter(new_movie_list, 6, text);
            printf("已筛选电影院id: %s\n", text);
            break;
        default:
            return new_movie_list; //可能返回NULL
        }
        int count = 0; Movie* temp_head = new_movie_list;
        while (temp_head)
        {
            count++; temp_head = temp_head->next;
        }
        printf("当前筛选得到 %d条数据", count);
        if (count != 0)
        {
            movie_list_free(free_temp);
            free_temp = NULL;
        }
        else
        {
            printf(",已回退,请重新筛选\n");
            new_movie_list = free_temp;
        }
        press_zero_to_continue();
    }
}

static Movie* for_admin_movie_sort(Movie* new_movie_list)//进入排序子菜单
{
    while (1)
    {
        //Movie* temp = new_movie_list;
        system("cls");
        display_admin_sort_menu();
        int option = get_user_input_int(5);
        //上座率(降序），价格(升序)，场次收入(降序)，开始时间(升序)，剩余票数(升序)
        switch (option)
        {
        case 1:
            new_movie_list = movie_operation_sort(new_movie_list, 1);
            printf("按上座率排序完成");
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list, 2);
            printf("按价格排序完成");
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 3);
            printf("按场次收入排序完成");
            break;
        case 4:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("按开始时间排序完成");
            break;
        case 5:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("按剩余票数排序完成");
            break;
        default:
            return new_movie_list;
        }
        press_zero_to_continue();
    }
}
void admin_view_and_count_order(Admin* admin_now, Theater_hash_table* theaterHashTable, Movie_hash_table* movieHashTable,Order* order_list) {

    Movie* new_movie_list = movie_list_create_by_cinema(admin_now->cinema, theaterHashTable, movieHashTable);

    while (1)
    {
        system("cls");
        display_movie_operate_main_menu();
        int option = get_user_input_int(4);
        switch (option)
        {
        case 1://选择了排序
            new_movie_list = for_admin_movie_sort(new_movie_list);//进入排序界面

            break;
        case 2://选择了筛选
            new_movie_list = for_admin_movie_filter(new_movie_list);
            break;
        case 3:
            Movie * movie_choice = movie_choose(new_movie_list, movieHashTable);
            if (movie_choice == NULL) break;
            
            printf("该场次的订单是:\n\n");
            from_user_print_order(movie_choice,order_list);
            press_zero_to_continue();
            //order_show_all //然后输出所有当前场次的订单
            break;
        case 4:
            printf("当前时间区段总收入为:%.2lf", caculate_movie_income(new_movie_list));
            while (get_user_input_int(0));
            break;
        default:
            movie_list_free(new_movie_list);
            new_movie_list = NULL;
            return;
        }
    }
}

void admin_theater_manage(Admin* admin_now, Theater ** theater_list, Theater_hash_table* theaterHashTable)//theater的删除没做
{
    while (1)
    {
        system("cls");
        admin_theater_manage_greet();
        int option = get_user_input_int(3);
        switch (option)
        {
        case 1:
            int add_status = admin_add_a_theater(admin_now, theater_list, theaterHashTable);
            switch (add_status)
            {
            case 1:
                printf("影厅添加成功\n"); break;
            case 2:
                printf("数据出错...\n"); break;
            case 0:
                printf("已取消添加\n"); break;
            }
            press_zero_to_continue();
            break;
        case 2:
            Linked_string_list * head = admin_now->cinema->my_theater;
            while (head)
            {
                theater_print(find_theater_in_hash_table(theaterHashTable, head->id));
                head = head->next;
            }
            printf("已展示所有影厅\n");
            press_zero_to_continue();
            break;
        default:
            return;
        }
    }
}

void admin_movie_manage(Film* film_list, Film_hash_table* filmHashTable, Movie_hash_table* movieHashTable, Theater_hash_table* theaterHashTable, Movie ** movie_list,Admin* admin_now)//排片管理
{
    while (1)
    {
        system("cls");
        display_admin_movie_manage_greet();
        int option = get_user_input_int(3);
        switch (option)
        {
        case 1:
            Film * film_choosed2 = film_choose(film_list, filmHashTable);
            int add_status2 = admin_auto_find_movie_to_theater(admin_now->cinema, film_choosed2, theaterHashTable, movieHashTable, movie_list);
            switch (add_status2)
            {
            case 1:
                printf("场次添加成功\n"); break;
            case 2:
                printf("数据出错...\n"); break;
            case 0:
                printf("已取消添加\n"); break;
            }
            press_zero_to_continue();
            break;
        case 2:
            Movie * movie_list_new = movie_list_create_by_cinema(admin_now->cinema, theaterHashTable, movieHashTable);
            movie_list_print(movie_list_new);
            press_zero_to_continue();
            movie_list_free(movie_list_new);
            break;
        case 3:
            Film * film_choosed = film_choose(film_list, filmHashTable);
            if (!film_choosed) break;
            Theater* theater_new_list = theater_list_create_by_cinema(admin_now->cinema, theaterHashTable);
            Theater* theater_choosed = theater_choose_for_admin(theater_new_list, theaterHashTable);
            if (!theater_choosed) break;

            int add_status = admin_add_a_movie_to_theater(theater_choosed, film_choosed, movie_list, movieHashTable);
            switch (add_status)
            {
            case 1:
                printf("场次添加成功\n"); break;
            case 2:
                printf("数据出错...\n"); break;
            case 0:
                printf("已取消添加\n"); break;
            }
            press_zero_to_continue();
            theater_free_copied_list(theater_new_list);
            theater_new_list = NULL;
            break;
        default:
            return;
            break;
        }
    }
}

void admin_modify_self_info(Admin* admin_now)
{
    while (1)
    {
        system("cls");
        display_admin_modify_info_menu();
        int option = get_user_input_int(5);
        char* buffter[24];
        switch (option)
        {
        case 1:
            printf("请输入新的id：\n");
            get_user_input_string(buffter, 20);
            printf("确认将id从%s 修改为", admin_now->admin_id);
            break;
        case 2:
            printf("请输入新的姓名：\n");
            get_user_input_string(buffter, 20);
            printf("确认将姓名从%s 修改为", admin_now->admin_name);
            break;
        case 3:
            strcpy(buffter, get_valid_phone_number());
            printf("确认将电话号码从%s 修改为", admin_now->admin_telephone);
            break;
        case 4:
            while (!change_password(admin_now->admin_password, buffter));
            printf("确认将密码修改为");
            break;
        case 5:
            get_valid_email(buffter, 20);
            printf("确认将邮箱从%s 修改为", admin_now->admin_email);
            break;
        case 0:
            return;
        default:
            return;
        }
        printf(" %s\n", buffter);
        int certify = get_user_input_int(1);

        if (certify) {
            admin_modify(admin_now, option, buffter);
            printf("修改成功\n");

        }
        else printf("已取消");
        press_zero_to_continue();
    }
}
bool admin_password_check(Admin* admin, Admin* admin_list) {
    if (!admin) return 0;
    int count = 0; char password[20]; bool key = 0;
    do {
        if (count >= 5)
        {
            for (int i = 0; i < 60; ++i) {
                system("cls");
                printf("请稍后重试 您已等待 %d/60", i);
                _sleep(1000);
            }
            count -= 3;
            return 0;
        }
        printf("请输入密码:");
        if (!get_password(password, 20)) return 0;
        key = !strcmp(admin->admin_password, password);
        if (!key) {
            printf("\n密码错误!\n");
            count++;
            _sleep(500);
            system("cls");
            printf("请输入您的ID:%s\n", admin->admin_id);
        }
    } while (!key);
    return 1;
}

Theater* theater_choose_for_admin(Theater* new_theater_list, Theater_hash_table* hash_table)
{
    int count = 0;
    Theater* new_head_for_option = new_theater_list;
    while (new_theater_list)
    {
        count++;
        printf("序号 %d:\n", count);
        printf("影厅名:%s\n", new_theater_list->theater_name);
        find_free_times(new_theater_list->time_line, 0, 1440);
        new_theater_list = new_theater_list->next;
    }
    printf("请输入你的选择(输入0退出): ");
    int option = get_user_input_int(count);
    if (option == 0) return NULL;
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next;
    }
    return find_theater_in_hash_table(hash_table, new_head_for_option->theater_id);
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

    return hours * 60 + minutes; // 合法时间格式
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
        int remaining_ticket = theater->theater_capacity;
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

            if (is_overlapping(theater->time_line->root, start_min - 5, end_min + 5)) //判断是否重叠
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
                printf("未能避开人流,当前约与%d个场次有人流冲突，是否确认?(1/0)\n", status);
                int option_flow = get_user_input_int(1);
                if (!option_flow) continue;
            }
            break;
        }

        printf("输入票价: ");
        price = get_user_input_double(0, 1000);
        //getchar(); // 清除缓冲区中的换行符

        // 输入折扣
        printf("输入折扣 (例如 0.9 表示九折): ");
        discount = get_user_input_double(0, 1);
        //getchar(); // 清除缓冲区中的换行符

        char *start_date=get_current_day();
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
            sprintf(temp1_id, "%05d", movie_hash_table->count + 1);
            strcat(movie_id, temp1_id);

            char date_time_start[20]; char date_time_end[20];
            days_to_date(start_day, date_time_start);
            days_to_date(start_day, date_time_end);
            strcat(date_time_start, start_time);
            strcat(date_time_end, end_time);
            start_day++;

            strcat(date_time_start, ":00"); strcat(date_time_end, ":00");

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