//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_ORDER_H
#define MOVIE_C_ORDER_H

#include "User.h"
#include "Movie.h"
#include "Cinema.h"

typedef struct {
    int orderID;
    User* usr;
    Movie* movie;
    Theater* theater;
    Cinema* cinema;
    int seats; //�����Ƕ�ά���飿
    int status; //����״̬
    char time[30];
    Order* next;
}Order;
#endif //MOVIE_C_ORDER_H