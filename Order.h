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
    char* user_id;
    Movie* movie;
    int movie_id;
    Theater* theater;
    Cinema* cinema; //指向头节点
    int seats; //可以是二维数组？
    int status; //订单状态
    char* time;
    struct Order* next;
}Order;
Order* order_create(int orderID, User* usr, const char* user_id, Movie* movie, int movie_id,
                    Theater* theater, Cinema* cinema, int seats, int status, const char* time);
// 将一个订单添加到链表中
void order_add_to_list(Order** head, Order* new_order);

// 直接添加一个订单到链表
void order_direct_add_to_list(Order** head, int orderID, User* usr, const char* user_id, Movie* movie,
                              int movie_id, Theater* theater, Cinema* cinema, int seats, int status, const char* time);

// 通过订单ID查找订单
Order* order_find_by_id(Order* head, int orderID);

// 显示单个订单信息
void order_show(const Order* order);

// 显示所有订单信息
void order_show_all(Order* head);

#endif //MOVIE_C_ORDER_H
