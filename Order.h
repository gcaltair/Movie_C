// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_ORDER_H
#define MOVIE_C_ORDER_H
typedef struct User User;
typedef struct Movie Movie;
typedef struct Theater Theater;
typedef struct Cinema Cinema;
typedef struct Order{
    int orderID;
    User* usr;
    Movie* movie;
    Theater* theater;
    Cinema* cinema;
    int seats; //可以是二维数组？
    int status; //订单状态
    char time[30];
    struct Order* next;
}Order;
#endif //MOVIE_C_ORDER_H
