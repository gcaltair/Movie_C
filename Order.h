//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_ORDER_H
#define MOVIE_C_ORDER_H

#include "User.h"
#include "Movie.h"
#include "Cinema.h"

typedef struct {
    int oderID;
    User* usr;
    Movie* movie;
    Theater* theater;
    Cinema* cinema;
    int seats; //可以是二维数组？
    int status; //订单状态
    char time[30];
}Order;
#endif //MOVIE_C_ORDER_H
