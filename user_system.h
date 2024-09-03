//
// Created by G on 2024/8/31.
//

#ifndef MOVIE_C_USER_SYSTEM_H
#define MOVIE_C_USER_SYSTEM_H
typedef struct User User;
typedef struct User_hash_table User_hash_table;
typedef struct Admin Admin;
bool admin_password_check(Admin* admin,Admin* admin_list);
bool user_password_check(User *usr,User_hash_table*userHashTable);
int get_user_input_int(int max);
void display_movie_operate_main_menu();
void admin_greet();
void admin_order_manage_greet();
//管理员排序菜单
void display_admin_sort_menu();
#endif //MOVIE_C_USER_SYSTEM_H
