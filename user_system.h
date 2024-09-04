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

void movie_print(const Movie* movie);
void theater_print(const Theater* theater);

void press_zero_to_continue();

int admin_add_a_theater(Admin* admin_now, Theater* theater_list, Theater_hash_table* theater_hash_table);

int get_user_input_int(int max);
int get_valid_date_input(char* date);

void display_movie_operate_main_menu();
void admin_greet();
void admin_order_manage_greet();
void admin_theater_manage_greet();
//管理员排序菜单
void display_admin_sort_menu();
void display_admin_filter_menu();
#endif //MOVIE_C_USER_SYSTEM_H
