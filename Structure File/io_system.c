#include"io_system.h"
#include<stdlib.h>
#include <stdbool.h>
#include<stdio.h>
#include "../Object/Movie.h"
#include "../Object/Order.h"
#include"../Object/Cinema.h"
#include"../Object/Film.h"
void get_user_input_string(char* input, int max_length) {
    printf("���������%dλ���ַ���: ", max_length);
    fgets(input, max_length + 1, stdin);  // ��ȡ���룬���max_length���ַ�

    // ȥ��ĩβ�Ļ��з�������У�
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
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
        if (max != 0)
            printf("����������ѡ�� 0-%d:", max);
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
                printf("�������,");
            }
        }
        else {
            printf("�������,");
            // �������뻺�������������������
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
}

bool get_password(char* password, int maxLen) {
    int i = 0;
    char ch;
    while (i < maxLen - 1) {
        ch = _getch(); // ��ȡһ���ַ�������ʾ
        if (ch == 26 || ch == 3) return 0;
        if (ch == '\r') { // ��⵽�س�����Enter����
            break;
        }
        else if (ch == '\b') { // �����˸��
            if (i > 0) {
                i--;
                printf("\b \b"); // ɾ��һ���ַ�
            }
        }
        else {
            password[i++] = ch;

            printf("*"); // ��ʾ�Ǻ�
        }
    }
    password[i] = '\0'; // �ַ���ĩβ�����ֹ��
    return 1;
}
// ������ڸ�ʽ�Ƿ�Ϊ YYYY-MM-DD
// �ж�����
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// ��֤�����Ƿ�Ϊ��Ч�ĸ�ʽ����Ч����
bool is_valid_date_format(const char* date) {
    // ���ȱ���Ϊ 10
    if (strlen(date) != 10) {
        return false;
    }

    // ����ʽ�Ƿ�Ϊ YYYY-MM-DD
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

    // ��ȡ��ݡ��·ݡ�����
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);

    // ����·��Ƿ���Ч
    if (month < 1 || month > 12) {
        return false;
    }

    // ��������Ƿ���Ч
    int max_days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // ��������꣬2 ���� 29 ��
    if (is_leap_year(year)) {
        max_days_in_month[1] = 29;
    }

    // ��������Ƿ���Ч
    if (day < 1 || day > max_days_in_month[month - 1]) {
        return false;
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

void from_user_print_order(Movie* movie,Order* order_list)
{
    Order* new_head = order_list;
    while (new_head)
    {
        if (!strcmp(movie->movie_id, new_head->movie_id))
        {
            order_print_for_user(new_head);
        }
        new_head = new_head->next;
    }
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
void movie_print_for_user_ticket(const Movie* movie, char* seat) {
    if (movie == NULL) {
        printf("��ǰ��ϢΪ��\n");
        return;
    }

    printf("==========================================\n");
    printf("|              ��ӰƱ��Ϣ                |\n");
    printf("==========================================\n");
    printf("| %-10s: %-26s |\n", "��Ӱ����", movie->film->film_name);
    printf("| %-10s: %-26s |\n", "ӰԺ����", movie->theater->cinema->cinema_name);
    printf("| %-10s: %-26s |\n", "Ӱ������", movie->theater->theater_name);
    printf("| %-10s: %-26s |\n", "��λ��", seat);
    printf("| %-10s: %-26s |\n", "Ӱ������", movie->theater->theater_type);
    printf("| %-10s: %-26s |\n", "����", movie->film->film_language);
    printf("| %-10s: %-26s |\n", "��ʼʱ��", movie->start_time);
    printf("| %-10s: %-26s |\n", "����ʱ��", movie->end_time);
    printf("| %-10s: %-26.2f |\n", "�۸�", movie->price);
    printf("| %-10s: %-26.2f |\n", "�ۿ�", movie->discount);
    printf("==========================================\n\n");
}
void order_print_for_user(const Order* order)
{
    if (order == NULL) {//order�Ҳ�����ʾ
        printf("Order not found.\n");
        return;
    }
    printf("����ID: %s\n", order->orderID);//չʾorder����
    printf("�û�ID: %s\n", order->user_id);//չʾorder����
    printf("���� ID: %s\n", order->movie_id);//չʾorder����
    printf("��λ %s\n", order->seats);//չʾorder����
    printf("��λ����: %d\n", order->seat_number);//չʾorder����
    printf("����״̬: %d\n", order->status);//չʾorder����
    printf("����ʱ��: %s\n", order->time);//չʾorder����
    printf("�����۸�: %f\n", order->price);//չʾorder����
    printf("-----------------");
    //movie_print(order->movie);//չʾorder����
    // ���Ը�����Ҫ��ʾ����Ķ�����Ϣ
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

void display_user_greet()
{
    printf("*************************************************\n");
    printf("*               ��ӭʹ������ӰԺ                *\n");
    printf("*************************************************\n");
    printf("* 1. ��Ӱ��Ʊ                                   *\n");
    printf("* 2. ������ӳ                                   *\n");
    printf("* 3. �ҵĶ���                                   *\n");
    printf("* 4. ��ֵ                                       *\n");
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
    //printf("* 3. �Ż��ۿ�                                   *\n");
    printf("* 3. �Զ����ѯ                                 *\n");
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