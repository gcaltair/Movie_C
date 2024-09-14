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
bool admin_password_check(Admin* admin,Admin* admin_list);
bool user_password_check(User *usr,User_hash_table*userHashTable);
static bool getPassword(char* password, int maxLen);


int date_to_days(const char* date);
void days_to_date(int days, char* date);



void minutes_to_hhmm(int minutes, char* buffer);
int hhmm_to_minutes(const char* hhmm);
void print_start_and_end_time(int start_min, int end_min);

void press_zero_to_continue();



int admin_auto_find_movie_to_theater(Cinema* cinema, Film* film, Theater_hash_table* theater_hash_table, Movie_hash_table* movie_hash_table, Movie* movie_list);





bool change_password(const char* current_password, char* new_password);

Movie* movie_choose(Movie* new_movie_list, Movie_hash_table* hash_table);

Film* film_choose(Film* new_film_list,Film_hash_table* hash_table);

Movie* for_user_movie_choose(Movie* new_movie_list, Movie* movie_hash_table);



#endif //MOVIE_C_USER_SYSTEM_H
