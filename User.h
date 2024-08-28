//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_USER_H
#define MOVIE_C_USER_H


typedef struct {
    char* userID;
    char* user_name;
    char* gender;
    char* telephone;
    char* password;
    char* email;
    double user_balance;
    struct User* next;
}User;
//添加新用户
void user_show(const User* user);
User* User_add(const char* id, const char* name, const char* gender,
               const char* telephone, const char* password, const char* email, double balance) ;
//修改用户信息
void modify_personalinfo();




#endif //MOVIE_C_USER_H
