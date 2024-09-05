//
// Created by G on 2024/8/30.
//

#ifndef MOVIE_C_DATA_PROCESS_H
#define MOVIE_C_DATA_PROCESS_H
typedef struct User User;
typedef struct Admin Admin;
typedef struct Cinema Cinema;
typedef struct Order Order;
typedef struct Film Film;
typedef struct Movie Movie;
typedef struct Theater Theater;
typedef void (*DataHandler)(char** fields,void *context);
void handle_user_data(char** fields,void* context);
void load_data_from_csv(const char* filename, DataHandler handler,void* context);
void handle_admin_data(char** fields, void* context);
void handle_cinema_data(char** fields, void* context);
void handle_movie_data(char** fields, void* context);
void handle_theater_data(char** fields, void* context);
void handle_order_data(char** fields, void* context);
void handle_film_data(char** fields, void* context);
void write_users_to_csv(const char* filename, User** user_list);
void write_admins_to_csv(const char* filename, Admin* admin_list);
void write_cinemas_to_csv(const char* filename, Cinema* cinema_list);
void write_orders_to_csv(const char* filename, Order* order_list);
void write_theaters_to_csv(const char* filename, Theater* theater_list);
void write_films_to_csv(const char* filename, Film* film_list);
void write_movies_to_csv(const char* filename, Movie* movie_list);
#endif //MOVIE_C_DATA_PROCESS_H
