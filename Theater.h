//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_THEATER_H
#define MOVIE_C_THEATER_H

#include "Cinema.h"

typedef struct {
    int theater_id;
    char* theater_name;
    int theater_capacity;
    Cinema* cinema;
    //缺座位图，座位号
    char* theater_type;
    double day_income;
}Theater;
#endif //MOVIE_C_THEATER_H
