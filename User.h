//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_USER_H
#define MOVIE_C_USER_H

#include <stdbool.h>

typedef struct {
    char* userID;
    char* user_name;
    char* gender;
    char* telephone;
    char* password;
    char* email;
    double user_balance;
}User;
bool login();
void modify_personalinfo(); //修改用户信息




#endif //MOVIE_C_USER_H
