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

        char start_date[20] = "2024-09-04";
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