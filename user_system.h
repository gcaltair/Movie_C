//
// Created by G on 2024/8/31.
//

#ifndef MOVIE_C_USER_SYSTEM_H
#define MOVIE_C_USER_SYSTEM_H
typedef struct User User;
typedef struct User_hash_table User_hash_table;
typedef struct Admin Admin;
typedef struct Film Film;
typedef struct Order Order;
typedef struct Order_hash_table Order_hash_table;

void Film_recommend(Film* film_list, Movie_hash_table* movieHashTable, User* user_now, Order** order_list, Order_hash_table* orderHashTable, Film_hash_table* filmHashTable);
int order_cancle_main(Order_hash_table* orderHashTable);
void order_system_for_user(User* user_now, Order_hash_table* orderHashTable, Order** order_list);
int process_pay_main(Order_hash_table* orderHashTable);
void order_list_show_by_user(User* usr, Order_hash_table* hashTable);
int process_pay_main_order(Order* order, Order_hash_table* orderHashTable);

//负责处理根据场次购买的用户行为
void user_buy_ticket_by_movie(User* user_now, Order** order_list, Order_hash_table* orderHashTable, Movie* target_movie);

void recharge_main(User* user_now);

void user_purchase_system(Film_hash_table* filmHashTable, Movie_hash_table* movieHashTable, Order_hash_table* orderHashTable, User* user_now, Cinema* cinema_list, Movie* movie_list, Order** order_list);

Movie* user_view_and_count_movie(Movie* movie_list, Movie_hash_table* movieHashTable, User* user_now);





Movie* for_user_movie_filter(Movie* new_movie_list);
Movie* sub_purchase_by_name_and_cinema(Cinema* cinema_list, Film_hash_table* filmHashTable, Movie_hash_table* movieHashTable, User* user_now);
Movie* sub_purchase_by_name(Film_hash_table* filmHashTable, Movie* movieHashTable, User* user_now);
Movie* for_user_movie_sort(Movie* new_movie_list);

bool user_password_check(User *usr,User_hash_table*userHashTable);

int date_to_days(const char* date);
void days_to_date(int days, char* date);



void minutes_to_hhmm(int minutes, char* buffer);
int hhmm_to_minutes(const char* hhmm);
void print_start_and_end_time(int start_min, int end_min);

void press_zero_to_continue();

int admin_add_a_theater(Admin* admin_now, Theater ** theater_list, Theater_hash_table* theater_hash_table);

Order* order_generate_main(User* usr, Movie* movie, Order** order_list, Order_hash_table* orderHashTable);




int admin_auto_find_movie_to_theater(Cinema* cinema, Film* film, Theater_hash_table* theater_hash_table, Movie_hash_table* movie_hash_table, Movie ** movie_list);





bool change_password(const char* current_password, char* new_password);

Movie* movie_choose(Movie* new_movie_list, Movie_hash_table* hash_table);

Movie* search_target_film_and_choose_movie(Film* target_film, Movie_hash_table* movieHashTable, User* user_now);

Film* film_choose(Film* new_film_list,Film_hash_table* hash_table);

Movie* for_user_movie_choose(Movie* new_movie_list, Movie* movie_hash_table);



#endif //MOVIE_C_USER_SYSTEM_H
