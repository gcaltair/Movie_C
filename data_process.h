//
// Created by G on 2024/8/30.
//

#ifndef MOVIE_C_DATA_PROCESS_H
#define MOVIE_C_DATA_PROCESS_H
typedef void (*DataHandler)(char** fields,void *context);
void handle_user_data(char** fields,void* context);
void load_data_from_csv(const char* filename, DataHandler handler,void* context);
void handle_admin_data(char** fields, void* context);
void handle_cinema_data(char** fields, void* context);
void handle_movie_data(char** fields, void* context);
void handle_theater_data(char** fields, void* context);
void handle_order_data(char** fields, void* context);
#endif //MOVIE_C_DATA_PROCESS_H
