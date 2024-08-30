#ifndef MOVIE_C_ADMIN_H
#define MOVIE_C_ADMIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Cinema Cinema;
//管理员结构体
typedef struct Admin{
    char* admin_id;
    char* admin_name;
    char* admin_telephone;
    char* admin_password;
    char* admin_email;
    struct Cinema* cinema;
    char *cinema_id;
    struct Admin* next;
}Admin;
Admin* Admin_create(const char* id, const char* name, const char* telephone,
                 const char* password, const char* email,Cinema *cinema_,const char* cinema_id);
void admin_add_to_list(Admin** head, Admin* new_admin);
void admin_show(const Admin* admin);
//修改用户信息
void admin_show_all(Admin* head);
void modify_personalinfo();
//查询管理员信息
Admin* find_admin(char* name);
//修改管理员信息
void modify_admin(Admin* admin);

#endif //MOVIE_C_ADMIN_H