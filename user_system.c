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
    printf("* 3. ɾ��Ӱ��                                   *\n");
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

