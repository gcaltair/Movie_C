//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_CINEMA_H
#define MOVIE_C_CINEMA_H
typedef struct {
    char* cinema_name;
    char* location;
    int cinema_id;
}Cinema;
Cinema* cinema_add(const char* name, const char* location, int id);
void cinema_show(const Cinema* cinema);
#endif //MOVIE_C_CINEMA_H
