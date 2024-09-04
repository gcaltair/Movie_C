//
// Created by G on 2024/8/31.
//

#ifndef MOVIE_C_USER_SYSTEM_H
#define MOVIE_C_USER_SYSTEM_H
typedef struct User User;
typedef struct User_hash_table User_hash_table;
typedef struct Admin Admin;
typedef struct Film Film;
bool admin_password_check(Admin* admin,Admin* admin_list);
bool user_password_check(User *usr,User_hash_table*userHashTable);

void movie_print(const Movie* movie);
void theater_print(const Theater* theater);
void film_print(const Film* film);

void minutes_to_hhmm(int minutes, char* buffer);

int hhmm_to_minutes(const char* hhmm);

void press_zero_to_continue();

int admin_add_a_theater(Admin* admin_now, Theater* theater_list, Theater_hash_table* theater_hash_table);

int get_user_input_int(int max);
int get_valid_date_input(char* date);

Movie* movie_choose(Movie* new_movie_list);
Theater* theater_choose_for_admin(Theater* new_theater_list);
Film* film_choose(Film* new_film_list);

void display_movie_operate_main_menu();
void admin_greet();
void admin_order_manage_greet();
void admin_theater_manage_greet();
void display_admin_movie_manage_greet();
//管理员排序菜单
void display_admin_sort_menu();
void display_admin_filter_menu();
#endif //MOVIE_C_USER_SYSTEM_H
