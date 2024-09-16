#ifndef ADMIN_SYSTEM_H
#define ADMIN_SYSTEM_H



typedef struct User User;
typedef struct User_hash_table User_hash_table;
typedef struct Theater_hash_table Theater_hash_table;
typedef struct Admin Admin;
typedef struct Film Film;
typedef struct Order Order;

void admin_view_and_count_order(Admin* admin_now, Theater_hash_table* theaterHashTable, Movie_hash_table* movieHashTable,Order* order_list);

void admin_theater_manage(Admin* admin_now, Theater ** theater_list, Theater_hash_table* theaterHashTable);
int add_movie_to_theater_dev(Film* film, Theater* theater, char* start_time, char* end_time, Movie_hash_table* movie_hash_table, Movie** movie_list);

void admin_movie_manage(Film* film_list, Film_hash_table* filmHashTable, Movie_hash_table* movieHashTable, Theater_hash_table* theaterHashTable, Movie ** movie_list, Admin* admin_now);

void admin_modify_self_info(Admin* admin_now);

bool admin_password_check(Admin* admin, Admin* admin_list);

void admin_order_manage(Admin* admin_now, Theater_hash_table* theaterHashTable, Movie_hash_table* movieHashTable, Order_hash_table* orderHashTable, Order* order_list);

static Movie* for_admin_movie_filter(Movie* new_movie_list);
static Movie* for_admin_movie_sort(Movie* new_movie_list);
Theater* theater_choose_for_admin(Theater* new_theater_list, Theater_hash_table* hash_table);
int admin_add_a_movie_to_theater(Theater* theater, Film* film, Movie* movie_list, Movie_hash_table* movie_hash_table);

#endif // !ADMIN_SYSTEM_H