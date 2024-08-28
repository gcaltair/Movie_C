//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_CINEMA_H
#define MOVIE_C_CINEMA_H
typedef struct Cinema{
    char* cinema_name;
    char* location;
    int cinema_id;
    struct Cinema* next;
}Cinema;
Cinema* cinema_create_list(const char* name, const char* location, int id,Cinema* next);
void cinema_add_to_list(Cinema** head, const char* name, const char* location, int id,Cinema* next);
Cinema* cinema_find_by_id(Cinema* head, int id);
Cinema* cinema_add(const char* name, const char* location, int id,Cinema* next);
void cinema_show(const Cinema* cinema);
void cinema_show_all(Cinema* head);

#endif //MOVIE_C_CINEMA_H
