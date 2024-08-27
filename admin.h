#ifndef MOVIE_C_ADMIN_H
#define MOVIE_C_ADMIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct {
    char* admin_ID;
    char* admin_name;
    char* admin_telephone;
    char* admin_password;
    char* admin_email;
    char* admin_cinema;
}Admin;
bool login();
Admin* Admin_add();
void modify_personalinfo(); //修改用户信息




#endif //MOVIE_C_ADMIN_H