#ifndef MOVIE_C_MOVIE_H  
#define MOVIE_C_MOVIE_H  

#include "Theater.h"

typedef struct Movie {
    char* movie_name;
    char* session_number;

    Theater* theater; // 指向在哪个影厅播放  

    char* start_time;
    char* end_time;
    int remaining_ticket;
    double price;
    double discount;
    char* theater_type;

    struct Movie* next; // 指向下一个电影场次（链表）  
} Movie;

// 创建新的 Movie 节点  
Movie* movie_create(const char* session_number, Theater* play_theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* theater_type);

// 添加 Movie 到链表
void movie_add_to_list(Movie** head, Movie* newMovie);

// 显示单个 Movie 的信息  
void movie_show(const Movie* movie);

// 显示链表中所有 Movie 的信息  
void movie_show_all(Movie* head);


#endif // MOVIE_C_MOVIE_H
