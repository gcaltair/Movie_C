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
        printf("��� %d:\n", count);
        printf("Ӱ����:%s\n", new_theater_list->theater_name);
        find_free_times(new_theater_list->time_line, 0, 1440);
        new_theater_list = new_theater_list->next;
    }
    printf("���������ѡ��(����0�˳�): ");
    int option = get_user_input_int(count);
    if (option == 0) return NULL;
    for (int i = 1; i < option; ++i)
    {
        new_head_for_option = new_head_for_option->next;
    }
    return find_theater_in_hash_table(hash_table, new_head_for_option->theater_id);
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

    return hours * 60 + minutes; // �Ϸ�ʱ���ʽ
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
        int remaining_ticket = theater->theater_capacity;
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

            if (is_overlapping(theater->time_line->root, start_min - 5, end_min + 5)) //�ж��Ƿ��ص�
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
                printf("δ�ܱܿ�����,��ǰԼ��%d��������������ͻ���Ƿ�ȷ��?(1/0)\n", status);
                int option_flow = get_user_input_int(1);
                if (!option_flow) continue;
            }
            break;
        }

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
            movie_add_to_list(&movie_list, new_movie);
        }
        return 1;
    }
}