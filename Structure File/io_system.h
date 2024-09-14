#ifndef IO_SYSTEM_H
#define IO_SYSTEM_H
#include<stdbool.h>

typedef struct Movie Movie;
typedef struct Order Order;
typedef struct Theater Theater;
typedef struct Film Film;


void movie_print(const Movie* movie);
void order_print_for_user(const Order* order);
void movie_print_for_user(const Movie* movie);
void theater_print(const Theater* theater);

void get_user_input_string(char* input, int max_length);
int get_user_input_int(int max);
double get_user_input_double(double min, double max);
bool get_password(char* password, int maxLen);
void get_valid_email(char* email, int max_length);
char* get_valid_phone_number();
int get_valid_date_input(char* date);

void from_user_print_order(Movie* movie, Order* order_list);

void movie_list_print(const Movie* movie_list);
void film_print(const Film* film);

void display_movie_operate_main_menu();
void display_user_movie_operate_main_menu();
void display_admin_modify_info_menu();
void display_user_greet();
void display_purchase_ticket();
void admin_greet();
void admin_order_manage_greet();
void admin_theater_manage_greet();
void display_admin_movie_manage_greet();

void display_admin_sort_menu();
void display_admin_filter_menu();

#endif // !IO_SYSTEM_H
