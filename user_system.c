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
#include"Object/Order.h"
#include"Structure File/interval_tree.h"
#include"Structure File/linked_list.h"
#include"Structure File/io_system.h"
#include"data_process.h"
//取消订单
//return 0 ： 输入无效订单或用户信息获取失败
//       1 ： 取消成功
//       2 ： 取消失败  
int order_cancle_main(Order_hash_table* orderHashTable) {
    printf("请输入您要取消的orderID.\n");
    char orderID[20];
    while (1) {
        if (scanf("%s", orderID) != 1) {
            printf("输入无效，请重新输入。\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("您输入的订单号无效.\n");
        return 0;
    }
    else {
        Order* order = find_order_in_hash_table(orderHashTable, orderID);
        if (order->status != 2) {
            printf("订单状态不合法,取消失败.\n");// 检查订单状态并尝试取消  
            return 2;
        }
        else {
            order_cancel(order);
            printf("取消成功.\n");
            return 1;
        }
    }
}
//退款
//return 0 ： 输入无效订单或用户信息获取失败
//       1 ： 退款成功
//       2 ： 退款失败  
int ticket_refund_main(Order_hash_table* orderHashTable) {
    printf("请输入您退款的orderID.\n");
    char orderID[30];
    while (1) {
        if (scanf("%s", orderID) != 1) {
            printf("输入无效，请重新输入。\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("您输入的订单号无效.\n");
        return 0;
    }
    else {
        Order* order = find_order_in_hash_table(orderHashTable, orderID);
        if (order->status != 1) {    // 检查订单状态并尝试退款
            printf("订单状态不合法.\n");
            return 2;
        }
        if (order->status != 1) {
            printf("退款失败.\n");
            return 2;
        }
        else {
            return ticket_refund(order, order->movie->seat_map, orderHashTable);
        }
    }
}
void order_system_for_user(User* user_now,Order_hash_table* orderHashTable, Order** order_list)
{
    while (1)
    {
        system("cls");
        display_user_order_menu();
        int cer = get_user_input_int(4);
        switch (cer) {
        case 1:
            order_list_show_by_user(user_now, orderHashTable);
            press_zero_to_continue();
            break;
            
        case 2:
            order_list_show_by_user(user_now, orderHashTable);
            process_pay_main(orderHashTable);
            press_zero_to_continue();
            break;
        case 3:
            order_list_show_by_user(user_now, orderHashTable);
            order_cancle_main(orderHashTable);
            press_zero_to_continue();
            break;
        case 4:
            order_list_show_by_user(user_now, orderHashTable);
            ticket_refund_main(orderHashTable);
            press_zero_to_continue();
            break;
        case 0:
            write_orders_to_csv("Data\\orders.csv", *order_list);
            return;
            break;
        }
    }
}
//用户根据订单付款
int process_pay_main(Order_hash_table* orderHashTable) {
    char orderID[100]; // 假设订单ID不会超过99个字符  
    printf("请输入您要付款的orderID.\n");
    while (1) {
        if (scanf("%99s", orderID) != 1) { // 使用宽度限制来防止缓冲区溢出  
            printf("输入无效，请重新输入。\n");
            while (getchar() != '\n'); // 清除输入缓冲区中的剩余字符  
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("您输入的订单号无效.\n");
        return 0;
    }
    Order* order = find_order_in_hash_table(orderHashTable, orderID);
    return process_pay_main_order(order,orderHashTable);
}
void order_list_show_by_user(User* usr, Order_hash_table* hashTable) {
    if (usr == NULL) {
        printf("找不到用户.\n");
    }
    Linked_string_list* order = usr->my_order;
    while (order != NULL) {
        order_print_for_user(find_order_in_hash_table(hashTable, order->id));
        order = order->next;
    }
}
void Film_recommend(Film* film_list,Movie_hash_table* movieHashTable,User* user_now,Order** order_list,Order_hash_table* orderHashTable, Film_hash_table* filmHashTable)
{
    printf("推荐影片:\n");
    Film* hot_film = hot_films(film_list,filmHashTable);
    film_print(hot_film);
    printf("是否进入购票>(1/0)");
    if (!get_user_input_int(1)) return;
    Movie* choosed_movie = search_target_film_and_choose_movie(hot_film, movieHashTable, user_now);
    if (!choosed_movie) return;
    user_buy_ticket_by_movie(user_now, order_list, orderHashTable, choosed_movie);
}
//处理用户对订单付款的行为
//return 1 ： 付款成功
//       2 ： 付款失败
int process_pay_main_order(Order* order, Order_hash_table* orderHashTable) {
    if (order->status != 2) {// 检查订单状态并尝试付款
        printf("订单状态不合法.\n");
        return 2;
    }
    if (balance_check(order) == 1) { // 检查余额并付款  
        if (process_pay(order, order->movie->seat_map) == 0) {
            printf("订单查询失败.\n");
            return 0;
        }
        else {
            printf("付款成功,您的票据信息是：\n");
            char* token = strtok(strdup(order->seats), "-"); //strdup可能导致内存泄露
            int token_count = 0;
            while (token&&token_count++<=3)
            {
                movie_print_for_user_ticket(order->movie,token);
                token = strtok(NULL, "-");
            }
            
            return 1;
        }
    }
    else 
    {
        while (balance_check(order) == 0) 
        {
            printf("余额不足,您还需充值%.2f元.继续充值请按1，放弃充值请按0\n", get_debt(order, orderHashTable));
            int cer = get_user_input_int(1);
            if (cer)
            {
                recharge_main(order->usr);
                if (balance_check(order) == 0) {
                    continue;
                }
                else {
                    process_pay(order, order->movie->seat_map);
                    printf("付款成功,您的票据信息是：\n");
                    char* token = strtok(strdup(order->seats), "-");
                    int token_count = 0;
                    while (token && token_count++ <= 3)
                    {
                        movie_print_for_user_ticket(order->movie, token);
                        token = strtok(NULL, "-");
                    }
                    
                    return 1;
                }
            }
            else
            { 
                printf("付款失败\n");
                return 2; 
            }
        }
    }
}
void user_buy_ticket_by_movie(User* user_now,Order** order_list,Order_hash_table* orderHashTable,Movie* target_movie)
{
    Order* order_new = order_generate_main(user_now, target_movie, order_list, orderHashTable);

    if (order_new == 0) { printf("订单生成失败\n"); press_zero_to_continue(); }
    else {
        printf("订单生成成功！是否现在付款?(未付款将不会锁定座位)\n");
        if (get_user_input_int(1)) process_pay_main_order(order_new, orderHashTable);
        write_orders_to_csv("Data\\orders.csv", *order_list);
        press_zero_to_continue();
    }
    return;
}
//充值
void recharge_main(User* user_now) {


    printf("请输入金额:");
    double money = get_user_input_double(50, 5000);

    if(recharge(user_now, money)) printf("充值成功！已充值%.2lf元\n",money);

}
void user_purchase_system(Film_hash_table* filmHashTable, Movie_hash_table* movieHashTable,Order_hash_table* orderHashTable, User* user_now, Cinema* cinema_list, Movie* movie_list,Order** order_list)
{
    while (1)
    {
        system("cls");
        display_purchase_ticket();
        int option = get_user_input_int(4);
        Movie* target_movie = NULL;
        switch (option)
        {
        case 1:
            target_movie=sub_purchase_by_name(filmHashTable, movieHashTable,user_now);
            //购买
            break;
        case 2:
            target_movie=sub_purchase_by_name_and_cinema(cinema_list, filmHashTable, movieHashTable, user_now);
            break;

        case 3://自定义查找
            target_movie=user_view_and_count_movie(movie_list, movieHashTable, user_now);
            break;

        default:
            return;

        }
        if (!target_movie) continue;
        user_buy_ticket_by_movie(user_now, order_list, orderHashTable, target_movie);
    }
}
Movie* user_view_and_count_movie(Movie* movie_list, Movie_hash_table* movieHashTable, User* user_now)
{
    Movie* new_movie_list = movie_filter_by_not_played(movie_list); //筛选并复制一条未播放场次的链表
    if (!new_movie_list)
    {
        printf("当前无可用场\n");
        press_zero_to_continue();
    }
    while (1)
    {
        system("cls");

        display_user_movie_operate_main_menu();

        int option = get_user_input_int(3);
        switch (option)
        {
        case 1://选择了排序
            new_movie_list = for_user_movie_sort(new_movie_list);//进入排序界面

            break;
        case 2://选择了筛选
            new_movie_list = for_user_movie_filter(new_movie_list);
            break;
        case 3:

            Movie * movie_choice = movie_choose(new_movie_list, movieHashTable);

            if (movie_choice == NULL) break;
            return movie_choice;
            break;
        default:
            movie_list_free(new_movie_list);
            new_movie_list = NULL;
            return;
        }
    }
}

Movie* for_user_movie_sort(Movie* new_movie_list)
{
    while (1)
    {

        system("cls");
        display_user_sort_menu();
        int option = get_user_input_int(3);
        //价格，开始时间，余票数
        switch (option)
        {
        case 1:
            new_movie_list = movie_operation_sort(new_movie_list, 2);
            //movie_print(new_movie_list);
            printf("按价格排序完成");
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("按开始时间排序完成");
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("按剩余票数排序完成");
            break;
        case 0:

            return new_movie_list;
        }
        press_zero_to_continue();
    }
}
Movie* for_user_movie_filter(Movie* new_movie_list)
{
    while (1)
    {
        system("cls");
        display_user_filter_menu();
        int option = get_user_input_int(6);
        Movie* free_temp = new_movie_list;
        //时间段，影片类型，电影院，影厅类型
        char start_time[20]; char end_time[20]; char text[20];
        switch (option)
        {
        case 1:
            printf("请分别输入起止时间\n");
            get_valid_date_input(start_time);
            get_valid_date_input(end_time);
            printf("对时间段 %s-%s 的筛选已完成", start_time, end_time);
            strcat(start_time, " 00:00:00");
            strcat(end_time, " 00:00:00");
            char* context[] = { start_time,end_time };
            new_movie_list = movie_operation_filter(new_movie_list, 1, context);
            break;
        case 2:
            printf("请输入影片类型:");
            scanf("%s", text);
            new_movie_list = movie_operation_filter(new_movie_list, 5, text);
            printf("已筛选影片类型: %s\n", text);
            break;
        case 3:
            printf("请输入电影院:");
            scanf("%s", text);
            new_movie_list = movie_filter_by_cinema_name(text, new_movie_list);
            printf("已筛选电影院: %s\n", text);
            break;
        case 4:
            printf("请输入影厅类型：");
            get_user_input_string(text, 20);
            new_movie_list = movie_filter_by_theater_type(text, new_movie_list);
            printf("已筛选影厅类型：%s\n", text);
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
Movie* sub_purchase_by_name_and_cinema(Cinema* cinema_list, Film_hash_table* filmHashTable, Movie_hash_table* movieHashTable, User* user_now)
{
    char cinema_name[20]; char film_name[20]; Cinema* target_cinema; Film* target_film;
    while (1)
    {
        printf("请输入电影院名称：\n");
        get_user_input_string(cinema_name, 15);
        target_cinema = cinema_find_by_name(cinema_list, cinema_name);
        if (!target_cinema)
        {
            printf("未找到电影院，是否重新输入?(1/0)");
            if (!get_user_input_int(1)) return;
        }
        if (target_cinema) break;
    }
    while (1)
    {
        printf("请输入电影名称：\n");
        get_user_input_string(film_name, 15);
        target_film = find_film_in_hash_table_by_name(filmHashTable, film_name);
        if (!target_film)
        {
            printf("未找到电影，是否重新输入?(1/0)");
            if (!get_user_input_int(1)) return;
        }
        if (target_film) break;
    }

    Movie* raw_movie_list = movie_list_create_by_film(target_film, movieHashTable);
    Movie* cinema_film_movie_list = movie_filter_by_cinema_name(cinema_name, raw_movie_list);
    Movie* cinema_film_movie_list_date = movie_filter_by_current_date(cinema_film_movie_list);
    Movie* choosed_movie = for_user_movie_choose(cinema_film_movie_list_date, movieHashTable);
    movie_list_free(choosed_movie);
    movie_list_free(raw_movie_list);
    movie_list_free(cinema_film_movie_list_date);
    return choosed_movie;
}

Movie* sub_purchase_by_name(Film_hash_table* filmHashTable, Movie* movieHashTable, User* user_now)
{
    Film* target_film;
    while (1) {
        printf("请输入电影名称：");
        char scanf_movie_name[30]; 
        get_user_input_string(scanf_movie_name, 20);
        target_film = find_film_in_hash_table_by_name(filmHashTable, scanf_movie_name);
        if (target_film == NULL) {
            printf("无法找到当前影片,是否重新输入?(1/0)");
            if (!get_user_input_int(1)) return;  //如果输入0退出循环
        }
        if (target_film != NULL) break;
    }
    Movie* target_movie = search_target_film_and_choose_movie(target_film, movieHashTable, user_now); //得到target movie然后购买
    return target_movie;
}

bool user_password_check(User *usr,User_hash_table*userHashTable)
{
    if(!usr) return 0;
    int count=0;char password[20];bool key=0;
    do {
        if(count>=5)
        {
            for (int i = 0; i < 60; ++i) {
                system("cls");
                printf("请稍后重试 您已等待 %d/60",i);
                _sleep(1000);
            }
            count-=3;
            return 0;
        }
        printf("请输入密码:");
        if (!get_password(password, 20)) return 0;
        
        key=!strcmp(usr->password,password);
        if(!key) {
            printf("\n密码错误!\n");
            count++;
            _sleep(500);
            system("cls");
            printf("请输入您的ID:%s\n",usr->userID);
        }
    } while (!key);
    return 1;
}
bool change_password(const char* current_password,char* new_password) {
    char input_password[20]; // 用于存储用户输入的当前密码
    char new_password1[20];  // 用于存储用户第一次输入的新密码
    char new_password2[20];  // 用于存储用户第二次输入的新密码

    // 输入当前密码
    printf("请输入当前密码: ");
    if (!get_password(input_password, sizeof(input_password))) {
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
    if (!get_password(new_password1, sizeof(new_password1))) {
        printf("\n密码输入失败。\n");
        return false;
    }
    printf("\n");

    // 输入新密码（第二次）
    printf("请再次输入新密码: ");
    if (!get_password(new_password2, sizeof(new_password2))) {
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
Movie* movie_choose(Movie* new_movie_list,Movie_hash_table* hash_table)
{
    int count = 0;
    Movie* new_head_for_option = new_movie_list;
    if (!new_movie_list)
    {
        printf("当前无可选择的场次");
        press_zero_to_continue();
        return NULL;
    }
    while (new_movie_list)
    {
        count++;
        printf("选项 %d:\n", count);
        movie_print_for_user(new_movie_list);
        new_movie_list = new_movie_list->next;
    }
    int option = get_user_input_int(count);
    if (option == 0) return NULL;
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next;
    }
    return find_movie_in_hash_table(hash_table,new_head_for_option->movie_id);
}
Movie* search_target_film_and_choose_movie(Film* target_film, Movie_hash_table* movieHashTable, User* user_now)
{
    Movie* movie_raw_list = movie_list_create_by_film(target_film, movieHashTable);
    Movie* movie_filtered_list_temp = movie_filter_by_current_date(movie_raw_list);
    Movie* movie_filtered_list = movie_filter_by_not_played(movie_filtered_list_temp);//得到当天未放映场次
    if (movie_filtered_list == NULL)
    {
        printf("暂无当日场次\n");
        press_zero_to_continue();
        movie_list_free(movie_raw_list);
        movie_list_free(movie_filtered_list_temp);
        return;
    }
    Movie* target_movie = for_user_movie_choose(movie_filtered_list, movieHashTable); //得到target_movie
    movie_print_for_user(target_movie);
    
    
    //order_generate_main(user_now, target_movie);

    return target_movie;
}

Movie* for_user_movie_choose(Movie* new_movie_list, Movie* movie_hash_table)
{
    int count = 0;
    if (!new_movie_list)
    {
        printf("当天无可播放影片\n");
        return NULL;
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
    Movie* returned_movie= find_movie_in_hash_table(movie_hash_table, new_head_for_option->movie_id);
    if (!returned_movie) return NULL;
    return returned_movie;
    
}

int my_min(int a,int b)
{
    return a < b ? a : b;
}

//传入真实Film和Theater
int add_movie_to_theater_dev(Film* film, Theater* theater, char* start_time, char* end_time, Movie_hash_table* movie_hash_table, Movie ** movie_list)
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

        char* start_date=get_current_day();
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

            strcat(date_time_start, ":00"); strcat(date_time_end, ":00");


            Movie* new_movie = movie_create(movie_hash_table, movie_id, film->film_id, film, theater->theater_id, theater, date_time_start, date_time_end, remaining_ticket, price, discount);
            if (new_movie == NULL) {
                return 2;
            }

            // 将新电影加入链表
            movie_add_to_list(movie_list, new_movie);
        }
        return 1;
    }
}
int admin_auto_find_movie_to_theater(Cinema* cinema,Film* film,Theater_hash_table* theater_hash_table,Movie_hash_table* movie_hash_table, Movie ** movie_list)
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
    end_min = start_min + time;
    theater_print(re__iterate_head);
    print_start_and_end_time(start_min, start_min+time);
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
        printf("选项 %d:\n", count);
        film_print(new_film_list);  // 打印每个 Film 的详细信息
        new_film_list = new_film_list->next;
    }

    // 获取用户输入的选择
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
int admin_add_a_theater(Admin* admin_now, Theater ** theater_list, Theater_hash_table* theater_hash_table) {
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

        theater_add_to_list(theater_list, new_theater);
        return 1;
    }
}
//Order main
//判断是否符合生成订单的条件，是则生成订单
//生成订单
//return 0 : 生成失败
//       1 : 生成成功，支付成功
//       2 : 生成成功，支付失败
Order* order_generate_main(User* usr, Movie* movie, Order** order_list, Order_hash_table* orderHashTable) //判断当前时间是否早于电影开始时间
{
    char *seats=(char*)malloc(sizeof(char)*30);
    while (1) {
        while (true)
        {
            seat_map_show(movie->seat_map);
            printf("请输入您想购买的座位号(形如A1-B1-C1).\n");
            strcpy(seats, seats_input_check());
            if (seats == NULL) {
                printf("输入无效，请重新输入.\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        int judge = strcmp(get_current_time(), movie->start_time);
        if (judge <= 0) {
            int check = order_generation(usr, seats, movie, movie->seat_map, orderHashTable);
            switch (check) { //根据生成订单的结果进行不同处理  
            case 0:
                printf("查询失败.\n");
                return 0;
            case 1:
                break;
            case 2:
                printf("您输入的座位数超过了最大购票限额.\n");
                return 0;
            case 3:
                printf("您输入了两个相同的座位号.\n");
                return 0;
            case 4:
                printf("您输入的座位号不在影院座次范围内.\n");
                return 0;
            case 5:
                printf("座位已经售出.\n");
                return 0;
            case 6:
                printf("座位与已售出的座位仅间隔一个座位.\n");
                return 0;
            case 7:
                printf("您已经购买过该场次的票,请确认是否继续购买,继续购买请按1,放弃购买请按0\n");
                int cer = get_user_input_int(1);
                if (cer) {
                    break;
                }
                return 0;
            case 8:
                printf("当天已购买过五个场次的票,请明日再行购买.\n");
                return 0;
            case 9:
                printf("该场次和您已经购买的场次时间冲突,请确认是否继续购买,继续购买请按1,放弃购买请按0\n");
                int cer1 = get_user_input_int(1);
                if (cer1) {
                    break;
                }
                return 0;
            case 10:
                printf("已购买过该场次的票且购买多个影片场次时间冲突,请确认是否继续购买,继续购买请按1,放弃购买请按0\n");
                int cer2 = get_user_input_int(1);
                if (cer2) {
                    break;
                }
                return 0;
            }
            // 订单生成并添加到列表中  

            Order* new_order = order_create(orderHashTable, get_orderID(orderHashTable->count+1), usr, usr->userID, movie, movie->movie_id, movie->theater, movie->theater->cinema, seats, get_seat_number(seats), 2, get_current_time());
            order_add_to_list(order_list, new_order);
            return new_order;
            //printf("订单生成成功，您的orderID是:%s\n是否付款，确认付款请按1，放弃付款请按0.\n", new_order->orderID);
            //int cer = get_user_input_int(1);
            //if (cer) {
            //    return process_pay_main_order(new_order);
            //}
            //else {
            //    return 2;
            //}
        }
        else {
            printf("您购买的影片已经开始.\n");
            return 0;// 影片已开始，无法购买  
        }
    }
}




