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
void movie_list_print(const Movie* movie_list);
int date_to_days(const char* date);
void days_to_date(int days, char* date);
void theater_print(const Theater* theater);
void film_print(const Film* film);

void minutes_to_hhmm(int minutes, char* buffer);
int hhmm_to_minutes(const char* hhmm);
void print_start_and_end_time(int start_min, int end_min);

void press_zero_to_continue();

int admin_add_a_theater(Admin* admin_now, Theater* theater_list, Theater_hash_table* theater_hash_table);
int admin_add_a_movie_to_theater(Theater* theater, Film* film, Movie* movie_list, Movie_hash_table* movie_hash_table);
int admin_auto_find_movie_to_theater(Cinema* cinema, Film* film, Theater_hash_table* theater_hash_table, Movie_hash_table* movie_hash_table, Movie* movie_list);

int get_user_input_int(int max);
double get_user_input_double(double min, double max);
int get_valid_date_input(char* date);
char* get_valid_phone_number();
void get_valid_email(char* email, int max_length);
void get_user_input_string(char* input, int max_length);

bool change_password(const char* current_password, char* new_password);

Movie* movie_choose(Movie* new_movie_list, Movie_hash_table* hash_table);
Theater* theater_choose_for_admin(Theater* new_theater_list,Theater_hash_table* hash_table);
Film* film_choose(Film* new_film_list,Film_hash_table* hash_table);

void display_movie_operate_main_menu();
void display_admin_modify_info_menu();
void admin_greet();
void admin_order_manage_greet();
void admin_theater_manage_greet();
void display_admin_movie_manage_greet();
//管理员排序菜单
void display_admin_sort_menu();
void display_admin_filter_menu();
#endif //MOVIE_C_USER_SYSTEM_H
