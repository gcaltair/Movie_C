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
        ch =_getch(); // ��ȡһ���ַ�������ʾ
        if(ch==26||ch==3) return 0;
        if (ch == '\r') { // ��⵽�س�����Enter����
            break;
        } else if (ch == '\b') { // �����˸��
            if (i > 0) {
                i--;
                printf("\b \b"); // ɾ��һ���ַ�
            }
        } else {
            password[i++] = ch;

            printf("*"); // ��ʾ�Ǻ�
        }
    }
    password[i] = '\0'; // �ַ���ĩβ�����ֹ��
    return 1;
}
bool change_password(const char* current_password,char* new_password) {
    char input_password[20]; // ���ڴ洢�û�����ĵ�ǰ����
    char new_password1[20];  // ���ڴ洢�û���һ�������������
    char new_password2[20];  // ���ڴ洢�û��ڶ��������������

    // ���뵱ǰ����
    printf("�����뵱ǰ����: ");
    if (!getPassword(input_password, sizeof(input_password))) {
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
    if (!getPassword(new_password1, sizeof(new_password1))) {
        printf("\n��������ʧ�ܡ�\n");
        return false;
    }
    printf("\n");

    // ���������루�ڶ��Σ�
    printf("���ٴ�����������: ");
    if (!getPassword(new_password2, sizeof(new_password2))) {
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

double get_user_input_double(double min, double max) {
    double option;
    char c;

    while (1) {
        printf("������һ����ֵ (��Χ: %.2f - %.2f): ", min, max);

        // ���Զ�ȡһ�� double ����
        if (scanf("%lf", &option) == 1) {
            // ��������Ƿ���ָ����Χ��
            if (option >= min && option <= max) {
                // �������뻺����
                while ((c = getchar()) != '\n' && c != EOF) {}
                return option;
            }
            else {
                printf("������Ч��������Χ�����������롣\n");
            }
        }
        else {
            printf("������Ч��������һ����ֵ��\n");

            // �������뻺����������� double ����
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
            printf("����0�Լ���...\n");
        

        // ���Զ�ȡһ����������
        if (scanf("%d", &option) == 1) {
            // ��������Ƿ���ָ����Χ��
            if (option >= 0 && option <= max) {
                // �������뻺����
                while ((c = getchar()) != '\n' && c != EOF) {}
                return option;
            }
            else {
                printf("invalid input,"); 
            }
        }
        else {
            printf("invalid input,");
            
            // �������뻺�������������������
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
}
// ������ڸ�ʽ�Ƿ�Ϊ YYYY-MM-DD
bool is_valid_date_format(const char* date) {
    // ���ȱ���Ϊ 10
    if (strlen(date) != 10) {
        return false;
    }

    // ���ÿһ�����Ƿ����Ҫ��
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

// ��ȡ�û����벢ȷ����ʽ��ȷ
int get_valid_date_input(char* date) {
    while (true) {
        printf("���������ڣ���ʽ: YYYY-MM-DD����");
        scanf("%s", date);

        if (is_valid_date_format(date)) {
            break;
        }
        //else if (strcmp(date, "exit") == 0)
        //{
        //    return 1;
        //}
        else {
            printf("�����ʽ�������������롣\n");
        }
    }
    return 0;
}
void movie_print(const Movie* movie) {
    if (movie == NULL) { printf("��ǰ��ϢΪ��"); return; }
    printf("����ID: %s\n", movie->movie_id);
    printf("��ӰID: %s\n", movie->film_id);
    printf("Ӱ��ID: %s\n", movie->theater_id);
    printf("��ʼʱ��: %s\n", movie->start_time);
    printf("����ʱ��: %s\n", movie->end_time);
    printf("��Ʊ��: %d\n", movie->remaining_ticket);
    printf("�۸�: %.2f\n", movie->price);
    printf("�ۿ�: %.2f\n", movie->discount);
    printf("------------\n");
}
void movie_print_for_user(const Movie* movie)
{
    if (movie == NULL) { printf("��ǰ��ϢΪ��"); return; }
    printf("ӰԺ���ƣ�%s\n", movie->theater->cinema->cinema_name);
    printf("Ӱ�����ƣ�%s\n", movie->theater->theater_name);
    printf("Ӱ�����ͣ�%s\n", movie->theater->theater_type);
    printf("�������ͣ�%s\n", movie->film->film_language);
    printf("��ʼʱ��: %s\n", movie->start_time);
    printf("����ʱ��: %s\n", movie->end_time);
    printf("��Ʊ��: %d\n", movie->remaining_ticket);
    printf("�۸�: %.2f\n", movie->price);
    printf("�ۿ�: %.2f\n", movie->discount);
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
        printf("��� %d:\n", count);
        movie_print(new_movie_list);
        new_movie_list = new_movie_list->next;
    }
    printf("���������ѡ��(����0�˳�):");
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
        printf("�����޿ɲ���ӰƬ\n");
        return;
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
        printf("��� %d:\n", count);
        printf("Ӱ����:%s\n", new_theater_list->theater_name);  
        find_free_times(new_theater_list->time_line,0,1440);
        new_theater_list = new_theater_list->next;
    }
    printf("���������ѡ��(����0�˳�): ");
    int option = get_user_input_int(count);  
    if (option == 0) return NULL;  
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next; 
    }
    return find_theater_in_hash_table(hash_table,new_head_for_option->theater_id);  
}
int get_time_format_hours_and_minutes(const char* time_str) {
    // ���ʱ���ַ����ĳ����Ƿ�Ϊ5�����ҵ������ַ��Ƿ�Ϊ ':'
    if (strlen(time_str) != 5 || time_str[2] != ':') {
        return -1; // ��Чʱ���ʽ
    }

    // ���Сʱ�ͷ��ӵ��ַ��Ƿ�Ϊ����
    for (int i = 0; i < 5; ++i) {
        if (i == 2) continue; // ���� ':'
        if (!isdigit(time_str[i])) {
            return -1; // �������ַ�
        }
    }

    // ��Сʱ�ͷ��Ӵ��ַ�������ȡ����
    int hours = (time_str[0] - '0') * 10 + (time_str[1] - '0');
    int minutes = (time_str[3] - '0') * 10 + (time_str[4] - '0');

    // ���Сʱ�ͷ����Ƿ�����Ч��Χ��
    if (hours < 0 || hours > 24 || minutes < 0 || minutes > 59) {
        return -1; // ��Чʱ�䷶Χ
    }

    return hours*60+minutes; // �Ϸ�ʱ���ʽ
}
int date_to_days(const char* date) {
    struct tm tm_date = { 0 };
    // ���������ַ���
    if (sscanf(date, "%d-%d-%d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday) != 3) printf("��ȡʱ�����\n");

    // ����ݵ���Ϊ��1900�꿪ʼ
    tm_date.tm_year -= 1900;
    // �·ݴ�0��ʼ�����Լ�ȥ1
    tm_date.tm_mon -= 1;

    // ��ȡʱ�����תΪ����
    time_t time_since_epoch = mktime(&tm_date);
    return (int)(time_since_epoch / (60 * 60 * 24));
}
void days_to_date(int days, char* date) {
    // ȷ���������㹻���Է�ֹ���
    // �Ƚ� days ת��Ϊ time_t ����
    time_t time_since_epoch = (time_t)days * 60 * 60 * 24;

    // ʹ�� gmtime ת��Ϊ tm �ṹ��
    struct tm* tm_date = gmtime(&time_since_epoch);

    // ȷ�� tm_date �ǿ�
    if (tm_date != NULL) {
        // ��ʽ��Ϊ�ַ���
        strftime(date, 20, "%Y-%m-%d ", tm_date);
    }
    else {
        // ��� tm_date �� NULL������������
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
                printf("�����Ӱ�Ŀ�ʼʱ�� (��ʽ: HH:MM): ");// �����Ӱ�Ŀ�ʼʱ��
                fgets(start_time, sizeof(start_time), stdin);
                start_time[strcspn(start_time, "\n")] = 0;
                start_min = get_time_format_hours_and_minutes(start_time);
                if (start_min != -1)
                {
                    end_min = start_min + film->film_time;
                    break;
                }
                printf("�������,����������\n");
            }

            if (is_overlapping(theater->time_line->root, start_min-5, end_min+5)) //�ж��Ƿ��ص�
            {
                printf("��Ƭʱ���ص���ͬӰ�����ʱ�䲻��!�Ƿ���������?(1/0)\n");
                int option_lapping = get_user_input_int(1);
                if (option_lapping) continue;
                else
                    return 0;
            }
            int status = is_avoid_flow(theater->cinema, start_min, end_min);
            
            if (status)
            {
                printf("δ�ܱܿ�����,��ǰԼ��%d��������������ͻ���Ƿ�ȷ��?(1/0)\n",status);
                int option_flow = get_user_input_int(1);
                if (!option_flow) continue;
            }
            break;
        }

        printf("����Ʊ��: ");
        price=get_user_input_double(0, 1000);
        //getchar(); // ����������еĻ��з�

        // �����ۿ�
        printf("�����ۿ� (���� 0.9 ��ʾ����): ");
        discount = get_user_input_double(0, 1);
        //getchar(); // ����������еĻ��з�

        char start_date[20]="2024-09-04";
        int start_day = date_to_days(start_date);
        
        int duration_day = 10;
        
        char end_time[20];
        minutes_to_hhmm(end_min, end_time);
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
            
            // ���µ�Ӱ��������
            movie_add_to_list(&movie_list, new_movie);
        }
        return 1;
    }
}
int my_min(int a,int b)
{
    return a < b ? a : b;
}

//������ʵFilm��Theater
int add_movie_to_theater_dev(Film* film, Theater* theater, char* start_time, char* end_time, Movie_hash_table* movie_hash_table, Movie* movie_list)
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

        char start_date[20] = "2024-09-04";
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


            Movie* new_movie = movie_create(movie_hash_table, movie_id, film->film_id, film, theater->theater_id, theater, date_time_start, date_time_end, remaining_ticket, price, discount);
            if (new_movie == NULL) {
                return 2;
            }

            // ���µ�Ӱ��������
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
    theater_print(re__iterate_head);
    print_start_and_end_time(start_min, end_min);
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
        printf("��� %d:\n", count);
        film_print(new_film_list);  // ��ӡÿ�� Film ����ϸ��Ϣ
        new_film_list = new_film_list->next;
    }

    // ��ȡ�û������ѡ��
    printf("���������ѡ��(����0�˳�): ");
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
int admin_add_a_theater(Admin* admin_now, Theater* theater_list, Theater_hash_table* theater_hash_table) {
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

        theater_add_to_list(&theater_list, new_theater);
        return 1;
    }
}
// �жϵ绰�����Ƿ�Ϸ��ĺ���
int is_valid_phone_number(const char* phone) {
    // �жϳ����Ƿ�Ϊ11λ
    if (strlen(phone) != 11) {
        return 0; // ���Ȳ��Ϸ�
    }

    // �ж���λ�Ƿ�Ϊ1
    if (phone[0] != '1') {
        return 0; // ��λ����1
    }

    // �ж��Ƿ�ȫΪ����
    for (int i = 0; i < 11; i++) {
        if (!isdigit(phone[i])) {
            return 0; // ���ַ������ַ�
        }
    }

    return 1; // �Ϸ��绰����
}
// ��ȡ�Ϸ��ĵ绰���룬������char*����
char* get_valid_phone_number() {
    char* phone = (char*)malloc(12 * sizeof(char)); // 11λ���ּ�1��������'\0'

    while (1) {
        printf("�������µĵ绰����: ");
        scanf("%s", phone);

        if (is_valid_phone_number(phone)) {
            return phone; // �Ϸ������ص绰����
        }
        else {
            printf("���벻�Ϸ������������롣\n");
        }
    }
}
// ��֤�����Ƿ�Ϸ��ĺ���
bool is_valid_email(const char* email) {
    int at_pos = -1;
    int dot_pos = -1;
    int len = strlen(email);

    // ���䳤��������Ҫ�� 5 ���ַ����� a@b.co��
    if (len < 5) {
        return false;
    }

    // ���������ַ���
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            // ����ж�� '@' ���ţ��򲻺Ϸ�
            if (at_pos != -1) {
                return false;
            }
            at_pos = i;
        }
        if (email[i] == '.') {
            // ��¼���һ�� '.' ���ŵ�λ��
            dot_pos = i;
        }
    }

    // ��� '@' ���ŵ�λ�ü�������Ƿ��� '.'
    if (at_pos == -1 || dot_pos == -1 || at_pos == 0 || dot_pos <= at_pos + 1 || dot_pos == len - 1) {
        return false;
    }

    // ��һ������Ƿ������Ч�ַ�������ĸ�����֡��»��ߡ�������ַ���
    for (int i = 0; i < len; i++) {
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.' && email[i] != '_' && email[i] != '-') {
            return false;
        }
    }

    return true;
}

// ��ȡ�Ϸ���������ĺ���
void get_valid_email(char* email, int max_length) {
    while (1) {
        printf("���������������ַ: ");
        fgets(email, max_length, stdin);

        // ȥ��ĩβ�Ļ��з�
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }

        // ��֤�����Ƿ�Ϸ�
        if (is_valid_email(email)) {
            printf("�����ַ�Ϸ���\n");
            break;
        }
        else {
            printf("�����ַ���Ϸ������������롣\n");
        }
    }
}
void get_user_input_string(char* input, int max_length) {
    printf("���������%dλ���ַ���: ", max_length);
    fgets(input, max_length + 1, stdin);  // ��ȡ���룬���max_length���ַ�

    // ȥ��ĩβ�Ļ��з�������У�
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
}
void display_user_greet()
{
    printf("*************************************************\n");
    printf("*               ��ӭʹ������ӰԺ                *\n");
    printf("*************************************************\n");
    printf("* 1. ��Ӱ��Ʊ                                   *\n");
    printf("* 2. ������ӳ                                   *\n");
    printf("* 3. �ҵĶ���                                   *\n");
    printf("* 4. ��������                                   *\n");
    printf("*                                               *\n");
    printf("* 0.�˳�                                        *\n");
    printf("*************************************************\n");
}
void display_purchase_ticket()
{
    printf("*************************************************\n");
    printf("*                 ��Ӱ��Ʊ                      *\n");
    printf("*************************************************\n");
    printf("* 1. ӰƬ��ѯ                                   *\n");
    printf("* 2. ӰƬ+ӰԺ��ѯ                              *\n");
    printf("* 3. �Ż��ۿ�                                   *\n");
    printf("* 4. �Զ����ѯ                                 *\n");
    printf("*                                               *\n");
    printf("* 0.�˳�                                        *\n");
    printf("*************************************************\n");
}
void admin_greet()
{
    printf("*************************************************\n");
    printf("*             ��ӭʹ�õ�ӰԺ����ϵͳ            *\n");
    printf("*************************************************\n");
    printf("* 1. ��������                                   *\n");
    printf("* 2. Ӱ������                                   *\n");
    printf("* 3. ���ι���                                   *\n");
    printf("* 4. ������Ϣ����                               *\n");
    printf("* 5. �û���Ϣ����                               *\n");
    printf("*                                               *\n");
    printf("* 0.�˳�                                        *\n");
    printf("*************************************************\n");
}
void display_admin_modify_info_menu()
{
    printf("*************************************************\n");
    printf("*               �޸Ĺ���Ա��Ϣ                  *\n");
    printf("*************************************************\n");
    printf("* 1. �޸�ID                                     *\n");
    printf("* 2. �޸�����                                   *\n");
    printf("* 3. �޸ĵ绰                                   *\n");
    printf("* 4. �޸�����                                   *\n");
    printf("* 5. �޸�����                                   *\n");
    printf("*                                               *\n");
    printf("* 0. �˳�                                       *\n");
    printf("*************************************************\n");
}

void admin_order_manage_greet()
{
    printf("*************************************************\n");
    printf("*                  ��������                     *\n");
    printf("*************************************************\n");
    printf("* 1. �鿴��ͳ���û�����                         *\n");
    printf("* 2. ��������                                   *\n");
    printf("*                                               *\n");
    printf("* 0.�˳�                                        *\n");
    printf("*************************************************\n");
}
void admin_theater_manage_greet()
{
    printf("*************************************************\n");
    printf("*                  Ӱ������                     *\n");
    printf("*************************************************\n");
    printf("* 1. ���Ӱ��                                   *\n");
    printf("* 2. �鿴Ӱ��                                   *\n");
    //printf("* 3. ɾ��Ӱ��                                   *\n");
    printf("*                                               *\n");
    printf("* 0.�˳�                                        *\n");
    printf("*************************************************\n");
}
void display_admin_movie_manage_greet()
{
    printf("*************************************************\n");
    printf("*                  ���ι���                     *\n");
    printf("*************************************************\n");
    printf("* 1. ������Ƭ                                   *\n");
    printf("* 2. �鿴��Ƭ                                   *\n");
    printf("* 3. �Զ�����Ƭ                                 *\n");
    printf("*                                               *\n");
    printf("* 0.�˳�                                        *\n");
    printf("*************************************************\n");
}
//���β����˵�
void display_movie_operate_main_menu() {
    printf("\n==== �������˵� ====\n");
    printf("1. ����\n");
    printf("2. ɸѡ\n");
    printf("3. �鿴��ѡ�񳡴�\n");
    printf("4. �鿴ӰԺ�ڵ�ǰ���������\n\n");
    printf("0. ���ض����������ò��������\n");
    
}

void display_user_movie_operate_main_menu() {
    printf("\n==== �������˵� ====\n");
    printf("1. ����\n");
    printf("2. ɸѡ\n");
    printf("3. �鿴��ѡ�񳡴�\n\n");
    printf("0. ���ع�Ʊ�����ò��������\n");

}

//����Ա����˵�
void display_admin_sort_menu() {
    printf("\n==== ����˵� ====\n");
    printf("1. ������ (����)\n");
    printf("2. �۸� (����)\n");
    printf("3. �������� (����)\n");
    printf("4. ��ʼʱ�� (����)\n");
    printf("5. ʣ��Ʊ�� (����)\n\n");
    printf("0. ���ز������˵�\n");
}
void display_user_sort_menu() {
    printf("\n==== ����˵� ====\n");
    printf("1. �۸� (����)\n");
    printf("2. ��ʼʱ�� (����)\n");
    printf("3. ʣ��Ʊ�� (����)\n\n");
    printf("0. ���ز������˵�\n");
}
void display_admin_filter_menu() {
    printf("\n==== ɸѡ�˵� ====\n");
    printf("1. ʱ���\n");
    printf("2. �ѷ�ӳ\n");
    printf("3. δ��ӳ\n");
    printf("4. ��������\n");
    printf("5. ӰƬ����\n");
    printf("6. ��ӰԺID\n\n");
    printf("0. ���ز������˵�\n");
}
void display_user_filter_menu() {
    printf("\n==== ɸѡ�˵� ====\n");
    printf("1. ʱ���\n");
    printf("2. ӰƬ����\n");
    printf("3. ��ӰԺ\n");
    printf("4. Ӱ������\n\n");
    printf("0. ���ز������˵�\n");
}
