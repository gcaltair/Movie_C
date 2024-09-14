#ifndef ADMIN_SYSTEM_H
#define ADMIN_SYSTEM_H



typedef struct User User;
typedef struct User_hash_table User_hash_table;
typedef struct Theater_hash_table Theater_hash_table;
typedef struct Admin Admin;
typedef struct Film Film;
typedef struct Order Order;
Theater* theater_choose_for_admin(Theater* new_theater_list, Theater_hash_table* hash_table);
int admin_add_a_movie_to_theater(Theater* theater, Film* film, Movie* movie_list, Movie_hash_table* movie_hash_table);

#endif // !ADMIN_SYSTEM_H