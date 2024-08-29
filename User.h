//
// Created by G on 2024/8/27.
//
#ifndef MOVIE_C_USER_H
#define MOVIE_C_USER_H

typedef struct Order Order;
typedef struct User {
    char* userID;
    char* user_name;
    char* gender;
    char* telephone;
    char* password;
    char* email;
    double user_balance;
    struct User* next;
    struct Order* order;
} User;

User* user_create_list(User* new_user); // ��������ͷ�ڵ�
void user_add_to_list(User** head, User* new_user); // ���һ��Ԫ�ص�����ͷ�巨
void user_direct_add_to_list(User** head, const char* userID, const char* name, const char* gender,
                             const char* telephone, const char* password, const char* email, double balance);
User* user_find_by_id(User* head, const char* userID); // ͨ���û�ID�����û�
User* user_create(const char* userID, const char* name, const char* gender, const char* telephone,
                  const char* password, const char* email, double balance); // �����û�
void user_show(const User* user); // ��ʾ�����û���Ϣ
void user_show_all(User* head); // ��ʾ�����û���Ϣ
//�޸��û���Ϣ
void modify_personalinfo();




#endif //MOVIE_C_USER_H
