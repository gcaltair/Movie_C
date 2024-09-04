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
    return new_head_for_option;  
}
int admin_add_a_movie_to_theater(Theater* theater,Film* film);

Film* film_choose(Film* new_film_list)
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

    return new_head_for_option;  // �����û�ѡ��� Film
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
void admin_greet()
{
    printf("*************************************************\n");
    printf("*               ��ӭʹ�õ�ӰԺ����ϵͳ          *\n");
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

