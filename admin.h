#ifndef MOVIE_C_ADMIN_H
#define MOVIE_C_ADMIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Cinema.h"

typedef struct {
    char* admin_ID;
    char* admin_name;
    char* admin_telephone;
    char* admin_password;
    char* admin_email;
    Cinema* cinema;
}Admin;
Admin* Admin_add(const char* id, const char* name, const char* telephone,
                 const char* password, const char* email, Cinema* cinema);
void admin_show(const Admin* admin);
void modify_personalinfo(); //修改用户信息




#endif //MOVIE_C_ADMIN_H