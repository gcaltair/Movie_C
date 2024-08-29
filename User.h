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

User* user_create_list(User* new_user); // 创建链表头节点
void user_add_to_list(User** head, User* new_user); // 添加一个元素到链表，头插法
void user_direct_add_to_list(User** head, const char* userID, const char* name, const char* gender,
                             const char* telephone, const char* password, const char* email, double balance);
User* user_find_by_id(User* head, const char* userID); // 通过用户ID查找用户
User* user_create(const char* userID, const char* name, const char* gender, const char* telephone,
                  const char* password, const char* email, double balance); // 创建用户
void user_show(const User* user); // 显示单个用户信息
void user_show_all(User* head); // 显示所有用户信息
//修改用户信息
void modify_personalinfo();




#endif //MOVIE_C_USER_H
