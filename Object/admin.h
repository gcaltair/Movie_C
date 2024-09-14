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
    char *cinema_id;
    struct Cinema* cinema;
    struct Admin* next;
}Admin;
//对于修改管理员的功能的几个mode进行枚举
Admin* Admin_create(const char* id, const char* name, const char* telephone,
                    const char* password, const char* email,Cinema *cinema_,const char* cinema_id);
void admin_add_to_list(Admin** head, Admin* new_admin);
void admin_show(const Admin* admin);
//修改用户信息
void admin_show_all(Admin* head);
//查询管理员信息
Admin* admin_find_by_id(Admin* head, char* id);
//修改管理员信息
Admin* admin_modify(Admin* admin, int mode, char* arg);
char* admin_delete(Admin** head, char* id);
void admin_free_list(Admin** head);
#endif //MOVIE_C_ADMIN_H