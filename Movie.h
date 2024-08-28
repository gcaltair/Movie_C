//
// Created by Y on 2024/8/27.
//

#ifndef MOVIE_C_MOVIE_H
#define MOVIE_C_MOVIE_H
#include "Theater.h"
typedef struct {
    char* session_number;
    char* movie_name;
    Theater* play_theater; //在哪个影厅播放
    char* start_time;
    char* end_time;
    int remaining_ticket;
    double price;
    double discount; //优惠
    char* theater_type;
}Movie;

Movie* find_movie1(char* movie_name);//according to movie name to find 




#endif //MOVIE_C_MOVIE_H