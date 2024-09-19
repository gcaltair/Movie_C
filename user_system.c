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
//ȡ������
//return 0 �� ������Ч�������û���Ϣ��ȡʧ��
//       1 �� ȡ���ɹ�
//       2 �� ȡ��ʧ��  
int order_cancle_main(Order_hash_table* orderHashTable) {
    printf("��������Ҫȡ����orderID.\n");
    char orderID[20];
    while (1) {
        if (scanf("%s", orderID) != 1) {
            printf("������Ч�����������롣\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("������Ķ�������Ч.\n");
        return 0;
    }
    else {
        Order* order = find_order_in_hash_table(orderHashTable, orderID);
        if (order->status != 2) {
            printf("����״̬���Ϸ�,ȡ��ʧ��.\n");// ��鶩��״̬������ȡ��  
            return 2;
        }
        else {
            order_cancel(order);
            printf("ȡ���ɹ�.\n");
            return 1;
        }
    }
}
//�˿�
//return 0 �� ������Ч�������û���Ϣ��ȡʧ��
//       1 �� �˿�ɹ�
//       2 �� �˿�ʧ��  
int ticket_refund_main(Order_hash_table* orderHashTable) {
    printf("���������˿��orderID.\n");
    char orderID[30];
    while (1) {
        if (scanf("%s", orderID) != 1) {
            printf("������Ч�����������롣\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("������Ķ�������Ч.\n");
        return 0;
    }
    else {
        Order* order = find_order_in_hash_table(orderHashTable, orderID);
        if (order->status != 1) {    // ��鶩��״̬�������˿�
            printf("����״̬���Ϸ�.\n");
            return 2;
        }
        if (order->status != 1) {
            printf("�˿�ʧ��.\n");
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
//�û����ݶ�������
int process_pay_main(Order_hash_table* orderHashTable) {
    char orderID[100]; // ���趩��ID���ᳬ��99���ַ�  
    printf("��������Ҫ�����orderID.\n");
    while (1) {
        if (scanf("%99s", orderID) != 1) { // ʹ�ÿ����������ֹ���������  
            printf("������Ч�����������롣\n");
            while (getchar() != '\n'); // ������뻺�����е�ʣ���ַ�  
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("������Ķ�������Ч.\n");
        return 0;
    }
    Order* order = find_order_in_hash_table(orderHashTable, orderID);
    return process_pay_main_order(order,orderHashTable);
}
void order_list_show_by_user(User* usr, Order_hash_table* hashTable) {
    if (usr == NULL) {
        printf("�Ҳ����û�.\n");
    }
    Linked_string_list* order = usr->my_order;
    while (order != NULL) {
        order_print_for_user(find_order_in_hash_table(hashTable, order->id));
        order = order->next;
    }
}
void Film_recommend(Film* film_list,Movie_hash_table* movieHashTable,User* user_now,Order** order_list,Order_hash_table* orderHashTable, Film_hash_table* filmHashTable)
{
    printf("�Ƽ�ӰƬ:\n");
    Film* hot_film = hot_films(film_list,filmHashTable);
    film_print(hot_film);
    printf("�Ƿ���빺Ʊ>(1/0)");
    if (!get_user_input_int(1)) return;
    Movie* choosed_movie = search_target_film_and_choose_movie(hot_film, movieHashTable, user_now);
    if (!choosed_movie) return;
    user_buy_ticket_by_movie(user_now, order_list, orderHashTable, choosed_movie);
}
//�����û��Զ����������Ϊ
//return 1 �� ����ɹ�
//       2 �� ����ʧ��
int process_pay_main_order(Order* order, Order_hash_table* orderHashTable) {
    if (order->status != 2) {// ��鶩��״̬�����Ը���
        printf("����״̬���Ϸ�.\n");
        return 2;
    }
    if (balance_check(order) == 1) { // ���������  
        if (process_pay(order, order->movie->seat_map) == 0) {
            printf("������ѯʧ��.\n");
            return 0;
        }
        else {
            printf("����ɹ�,����Ʊ����Ϣ�ǣ�\n");
            char* token = strtok(strdup(order->seats), "-"); //strdup���ܵ����ڴ�й¶
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
            printf("����,�������ֵ%.2fԪ.������ֵ�밴1��������ֵ�밴0\n", get_debt(order, orderHashTable));
            int cer = get_user_input_int(1);
            if (cer)
            {
                recharge_main(order->usr);
                if (balance_check(order) == 0) {
                    continue;
                }
                else {
                    process_pay(order, order->movie->seat_map);
                    printf("����ɹ�,����Ʊ����Ϣ�ǣ�\n");
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
                printf("����ʧ��\n");
                return 2; 
            }
        }
    }
}
void user_buy_ticket_by_movie(User* user_now,Order** order_list,Order_hash_table* orderHashTable,Movie* target_movie)
{
    Order* order_new = order_generate_main(user_now, target_movie, order_list, orderHashTable);

    if (order_new == 0) { printf("��������ʧ��\n"); press_zero_to_continue(); }
    else {
        printf("�������ɳɹ����Ƿ����ڸ���?(δ�������������λ)\n");
        if (get_user_input_int(1)) process_pay_main_order(order_new, orderHashTable);
        write_orders_to_csv("Data\\orders.csv", *order_list);
        press_zero_to_continue();
    }
    return;
}
//��ֵ
void recharge_main(User* user_now) {


    printf("��������:");
    double money = get_user_input_double(50, 5000);

    if(recharge(user_now, money)) printf("��ֵ�ɹ����ѳ�ֵ%.2lfԪ\n",money);

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
            //����
            break;
        case 2:
            target_movie=sub_purchase_by_name_and_cinema(cinema_list, filmHashTable, movieHashTable, user_now);
            break;

        case 3://�Զ������
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
    Movie* new_movie_list = movie_filter_by_not_played(movie_list); //ɸѡ������һ��δ���ų��ε�����
    if (!new_movie_list)
    {
        printf("��ǰ�޿��ó�\n");
        press_zero_to_continue();
    }
    while (1)
    {
        system("cls");

        display_user_movie_operate_main_menu();

        int option = get_user_input_int(3);
        switch (option)
        {
        case 1://ѡ��������
            new_movie_list = for_user_movie_sort(new_movie_list);//�����������

            break;
        case 2://ѡ����ɸѡ
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
        //�۸񣬿�ʼʱ�䣬��Ʊ��
        switch (option)
        {
        case 1:
            new_movie_list = movie_operation_sort(new_movie_list, 2);
            //movie_print(new_movie_list);
            printf("���۸��������");
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("����ʼʱ���������");
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("��ʣ��Ʊ���������");
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
        //ʱ��Σ�ӰƬ���ͣ���ӰԺ��Ӱ������
        char start_time[20]; char end_time[20]; char text[20];
        switch (option)
        {
        case 1:
            printf("��ֱ�������ֹʱ��\n");
            get_valid_date_input(start_time);
            get_valid_date_input(end_time);
            printf("��ʱ��� %s-%s ��ɸѡ�����", start_time, end_time);
            strcat(start_time, " 00:00:00");
            strcat(end_time, " 00:00:00");
            char* context[] = { start_time,end_time };
            new_movie_list = movie_operation_filter(new_movie_list, 1, context);
            break;
        case 2:
            printf("������ӰƬ����:");
            scanf("%s", text);
            new_movie_list = movie_operation_filter(new_movie_list, 5, text);
            printf("��ɸѡӰƬ����: %s\n", text);
            break;
        case 3:
            printf("�������ӰԺ:");
            scanf("%s", text);
            new_movie_list = movie_filter_by_cinema_name(text, new_movie_list);
            printf("��ɸѡ��ӰԺ: %s\n", text);
            break;
        case 4:
            printf("������Ӱ�����ͣ�");
            get_user_input_string(text, 20);
            new_movie_list = movie_filter_by_theater_type(text, new_movie_list);
            printf("��ɸѡӰ�����ͣ�%s\n", text);
            break;
        default:
            return new_movie_list; //���ܷ���NULL
        }
        int count = 0; Movie* temp_head = new_movie_list;
        while (temp_head)
        {
            count++; temp_head = temp_head->next;
        }
        printf("��ǰɸѡ�õ� %d������", count);
        if (count != 0)
        {
            movie_list_free(free_temp);
            free_temp = NULL;
        }
        else
        {
            printf(",�ѻ���,������ɸѡ\n");
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
        printf("�������ӰԺ���ƣ�\n");
        get_user_input_string(cinema_name, 15);
        target_cinema = cinema_find_by_name(cinema_list, cinema_name);
        if (!target_cinema)
        {
            printf("δ�ҵ���ӰԺ���Ƿ���������?(1/0)");
            if (!get_user_input_int(1)) return;
        }
        if (target_cinema) break;
    }
    while (1)
    {
        printf("�������Ӱ���ƣ�\n");
        get_user_input_string(film_name, 15);
        target_film = find_film_in_hash_table_by_name(filmHashTable, film_name);
        if (!target_film)
        {
            printf("δ�ҵ���Ӱ���Ƿ���������?(1/0)");
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
        printf("�������Ӱ���ƣ�");
        char scanf_movie_name[30]; 
        get_user_input_string(scanf_movie_name, 20);
        target_film = find_film_in_hash_table_by_name(filmHashTable, scanf_movie_name);
        if (target_film == NULL) {
            printf("�޷��ҵ���ǰӰƬ,�Ƿ���������?(1/0)");
            if (!get_user_input_int(1)) return;  //�������0�˳�ѭ��
        }
        if (target_film != NULL) break;
    }
    Movie* target_movie = search_target_film_and_choose_movie(target_film, movieHashTable, user_now); //�õ�target movieȻ����
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
                printf("���Ժ����� ���ѵȴ� %d/60",i);
                _sleep(1000);
            }
            count-=3;
            return 0;
        }
        printf("����������:");
        if (!get_password(password, 20)) return 0;
        
        key=!strcmp(usr->password,password);
        if(!key) {
            printf("\n�������!\n");
            count++;
            _sleep(500);
            system("cls");
            printf("����������ID:%s\n",usr->userID);
        }
    } while (!key);
    return 1;
}
bool change_password(const char* current_password,char* new_password) {
    char input_password[20]; // ���ڴ洢�û�����ĵ�ǰ����
    char new_password1[20];  // ���ڴ洢�û���һ�������������
    char new_password2[20];  // ���ڴ洢�û��ڶ��������������

    // ���뵱ǰ����
    printf("�����뵱ǰ����: ");
    if (!get_password(input_password, sizeof(input_password))) {
        printf("\n��������ʧ�ܡ�\n");
        return false;
    }
    printf("\n");

    // ��֤��ǰ�����Ƿ���ȷ
    if (strcmp(input_password, current_password) != 0) {
        printf("��ǰ�������\n");
        return false;
    }

    // ���������루��һ�Σ�
    printf("������������: ");
    if (!get_password(new_password1, sizeof(new_password1))) {
        printf("\n��������ʧ�ܡ�\n");
        return false;
    }
    printf("\n");

    // ���������루�ڶ��Σ�
    printf("���ٴ�����������: ");
    if (!get_password(new_password2, sizeof(new_password2))) {
        printf("\n��������ʧ�ܡ�\n");
        return false;
    }
    printf("\n");

    // ��֤�����������Ƿ�һ��
    if (strcmp(new_password1, new_password2) != 0) {
        printf("��������������벻һ�£�\n");
        return false;
    }

    
    // ��������Ա���������
    strcpy(new_password, new_password1);

    return true;
}
Movie* movie_choose(Movie* new_movie_list,Movie_hash_table* hash_table)
{
    int count = 0;
    Movie* new_head_for_option = new_movie_list;
    if (!new_movie_list)
    {
        printf("��ǰ�޿�ѡ��ĳ���");
        press_zero_to_continue();
        return NULL;
    }
    while (new_movie_list)
    {
        count++;
        printf("ѡ�� %d:\n", count);
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
    Movie* movie_filtered_list = movie_filter_by_not_played(movie_filtered_list_temp);//�õ�����δ��ӳ����
    if (movie_filtered_list == NULL)
    {
        printf("���޵��ճ���\n");
        press_zero_to_continue();
        movie_list_free(movie_raw_list);
        movie_list_free(movie_filtered_list_temp);
        return;
    }
    Movie* target_movie = for_user_movie_choose(movie_filtered_list, movieHashTable); //�õ�target_movie
    movie_print_for_user(target_movie);
    
    
    //order_generate_main(user_now, target_movie);

    return target_movie;
}

Movie* for_user_movie_choose(Movie* new_movie_list, Movie* movie_hash_table)
{
    int count = 0;
    if (!new_movie_list)
    {
        printf("�����޿ɲ���ӰƬ\n");
        return NULL;
    }
    Movie* new_head_for_option = new_movie_list;
    while (new_movie_list)
    {
        count++;
        printf("��� %d:\n", count);
        movie_print_for_user(new_movie_list);
        new_movie_list = new_movie_list->next;
    }
    printf("���������ѡ��(����0�˳�):");
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

//������ʵFilm��Theater
int add_movie_to_theater_dev(Film* film, Theater* theater, char* start_time, char* end_time, Movie_hash_table* movie_hash_table, Movie ** movie_list)
{
    char movie_id[50];
    int remaining_ticket = theater->theater_capacity;
    double price, discount;
    while (1)
    {
        printf("����Ʊ��: ");
        price = get_user_input_double(0, 1000);
        //getchar(); // ����������еĻ��з�

        // �����ۿ�
        printf("�����ۿ� (���� 0.9 ��ʾ����): ");
        discount = get_user_input_double(0, 1);
        //getchar(); // ����������еĻ��з�

        char* start_date=get_current_day();
        int start_day = date_to_days(start_date);

        int duration_day = 10;

        // ��ʾ��Ϣȷ��
        printf("������Ϣ��:\n");
        printf("��ʼʱ��: %s\n", start_time);
        printf("����ʱ��: %s\n", end_time);
        printf("ʣ��Ʊ��: %d\n", remaining_ticket);
        printf("Ʊ��: %.2lf\n", price);
        printf("�ۿ�: %.2lf\n", discount);
        printf("��ʼ���ڣ�%s\n", start_date);
        printf("����������%d\n", duration_day);
        printf("ȷ�������? (1:ȷ�� 0:ȡ����� 2:��������): ");
        int option = get_user_input_int(2);
        if (option == 0) return 0;
        if (option == 2) continue;
        for (int i = 0; i < duration_day; ++i)
        {
            // ȷ��Theater��Film����
            if (theater == NULL || film == NULL) {
                printf("Theater��Film����Ϊ�գ��޷���ӵ�Ӱ��\n");
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

            // ���µ�Ӱ��������
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

    int start_min = 0; int end_min = 1440;//��Ϊ���ʵ�ʵ�ʿ���ʱ��
    while (copied_theater_list) { //Ѱ������ʵ�ʱ��
        int count = 1;
        
        int number = 0;//���ڻ��ʱ���
        interval* free_period = find_free_times_interval(copied_theater_list->time_line, 540, 1380, &number);//����9:00��23:00�Ŀ���ʱ��
        for (int i = 0; i < number; ++i)
        {
            free_period[i].start += 5; free_period[i].end -= 5; //���ʵ�ʿ���ʱ��
            int differ = free_period[i].end - free_period[i].start - time;
            if (differ>0 && (differ< end_min - start_min))//����µ�ʵ�ʿ���ʱ�α�֮ǰ�Ĵ�
            {
                list_cout = count;
                start_min = free_period[i].start;
                end_min = free_period[i].end;
            }
        }
        copied_theater_list = copied_theater_list->next;
        count++;
    }
    //���յõ�theater�Լ���ʵ�����ʱ�Σ�������ʵ�����ʱ����ɸѡ������С
    
    int pre_flow_theater = 20;

    for (int i = start_min; i + time <= end_min; i++)
    {
        int now_flow_theater = is_avoid_flow(cinema, start_min, start_min + time);//���ڵ���������
        if ((pre_flow_theater -now_flow_theater ) > 0) //���֮ǰ�ı����ڵĶ�
        {
            pre_flow_theater = now_flow_theater;
            start_min = i; 
        }
    }
    //���õ�pre_flow_theater��start_min


    for (int i = 1; i < list_cout; ++i) //�������Ӱ����Ϣ
    {
        re__iterate_head = re__iterate_head->next;
    }

    printf("ϵͳΪ��ѡ���ʱ���ǣ�\n");
    end_min = start_min + time;
    theater_print(re__iterate_head);
    print_start_and_end_time(start_min, start_min+time);
    if (pre_flow_theater)
    {
        printf("����%d��������ͻ����", pre_flow_theater);
    }
    printf("�Ƿ�ȷ��?(1/0)\n");
    int option = get_user_input_int(1);
    if (!option) return 0;
    //�õ��˵�Ӱ��Ӱ������ʼ����ʱ�Σ�������Ƭ
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
    printf("��ʼʱ��: %s\n", start_time);
    printf("����ʱ��: %s\n", end_time);
}
Film* film_choose(Film* new_film_list,Film_hash_table* hash_table)
{
    int count = 0;
    Film* new_head_for_option = new_film_list;

    // ��ӡ���� Film ����Ϣ������������
    while (new_film_list)
    {
        count++;
        printf("ѡ�� %d:\n", count);
        film_print(new_film_list);  // ��ӡÿ�� Film ����ϸ��Ϣ
        new_film_list = new_film_list->next;
    }

    // ��ȡ�û������ѡ��
    int option = get_user_input_int(count);  // ��ȡ�û����������
    if (option == 0) return NULL;  // ����û�ѡ���˳����򷵻� NULL

    // �����û���ѡ���ҵ���Ӧ�� Film
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next;
    }

    return find_film_in_hash_table_by_id(hash_table,new_head_for_option->film_id);  // �����û�ѡ��� Film
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
        printf("����Ӱ������: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        printf("����Ӱ������: ");
        capacity = get_user_input_int(500);
        
        printf("����Ӱ������: ");
        fgets(type, sizeof(type), stdin);
        type[strcspn(type, "\n")] = 0;

        printf("������Ϣ��:\n");
        printf("%s\n", name);
        printf("%d\n", capacity);
        printf("%s\n", type);
        printf("ȷ�������? (1:ȷ�� 0:ȡ����� 2:��������):");
        int option = get_user_input_int(2);
        if (option == 0) return 0;
        if (option == 2) continue;
        // ��ȡ Cinema �ṹ���ָ�룬���� Cinema ID ����
        Cinema* cinema = admin_now->cinema;
        if (cinema == NULL) {
            return 2;
        }

        // ������ Theater ����������͹�ϣ��
        Theater* new_theater = theater_create(theater_hash_table, theater_id, name, capacity, cinema, cinema_id, type);
        if (new_theater == NULL) {        
            return 2;
        }

        theater_add_to_list(theater_list, new_theater);
        return 1;
    }
}
//Order main
//�ж��Ƿ�������ɶ������������������ɶ���
//���ɶ���
//return 0 : ����ʧ��
//       1 : ���ɳɹ���֧���ɹ�
//       2 : ���ɳɹ���֧��ʧ��
Order* order_generate_main(User* usr, Movie* movie, Order** order_list, Order_hash_table* orderHashTable) //�жϵ�ǰʱ���Ƿ����ڵ�Ӱ��ʼʱ��
{
    char *seats=(char*)malloc(sizeof(char)*30);
    while (1) {
        while (true)
        {
            seat_map_show(movie->seat_map);
            printf("���������빺�����λ��(����A1-B1-C1).\n");
            strcpy(seats, seats_input_check());
            if (seats == NULL) {
                printf("������Ч������������.\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        int judge = strcmp(get_current_time(), movie->start_time);
        if (judge <= 0) {
            int check = order_generation(usr, seats, movie, movie->seat_map, orderHashTable);
            switch (check) { //�������ɶ����Ľ�����в�ͬ����  
            case 0:
                printf("��ѯʧ��.\n");
                return 0;
            case 1:
                break;
            case 2:
                printf("���������λ�����������Ʊ�޶�.\n");
                return 0;
            case 3:
                printf("��������������ͬ����λ��.\n");
                return 0;
            case 4:
                printf("���������λ�Ų���ӰԺ���η�Χ��.\n");
                return 0;
            case 5:
                printf("��λ�Ѿ��۳�.\n");
                return 0;
            case 6:
                printf("��λ�����۳�����λ�����һ����λ.\n");
                return 0;
            case 7:
                printf("���Ѿ�������ó��ε�Ʊ,��ȷ���Ƿ��������,���������밴1,���������밴0\n");
                int cer = get_user_input_int(1);
                if (cer) {
                    break;
                }
                return 0;
            case 8:
                printf("�����ѹ����������ε�Ʊ,���������й���.\n");
                return 0;
            case 9:
                printf("�ó��κ����Ѿ�����ĳ���ʱ���ͻ,��ȷ���Ƿ��������,���������밴1,���������밴0\n");
                int cer1 = get_user_input_int(1);
                if (cer1) {
                    break;
                }
                return 0;
            case 10:
                printf("�ѹ�����ó��ε�Ʊ�ҹ�����ӰƬ����ʱ���ͻ,��ȷ���Ƿ��������,���������밴1,���������밴0\n");
                int cer2 = get_user_input_int(1);
                if (cer2) {
                    break;
                }
                return 0;
            }
            // �������ɲ���ӵ��б���  

            Order* new_order = order_create(orderHashTable, get_orderID(orderHashTable->count+1), usr, usr->userID, movie, movie->movie_id, movie->theater, movie->theater->cinema, seats, get_seat_number(seats), 2, get_current_time());
            order_add_to_list(order_list, new_order);
            return new_order;
            //printf("�������ɳɹ�������orderID��:%s\n�Ƿ񸶿ȷ�ϸ����밴1�����������밴0.\n", new_order->orderID);
            //int cer = get_user_input_int(1);
            //if (cer) {
            //    return process_pay_main_order(new_order);
            //}
            //else {
            //    return 2;
            //}
        }
        else {
            printf("�������ӰƬ�Ѿ���ʼ.\n");
            return 0;// ӰƬ�ѿ�ʼ���޷�����  
        }
    }
}




