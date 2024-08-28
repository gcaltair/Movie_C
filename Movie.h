#ifndef MOVIE_C_MOVIE_H  
#define MOVIE_C_MOVIE_H  

#include "Theater.h"  

typedef struct Movie {
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
Movie* createMovie(const char* session_number, Theater* play_theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* theater_type);

// 添加 Movie 到链表  
void addMovie(Movie** head, Movie* newMovie);

// 从用户输入中创建 Movie 并添加到链表  
void addMovieFromInput(Movie** head);

// 显示单个 Movie 的信息  
void show_movie(const Movie* movie);

// 显示链表中所有 Movie 的信息  
void show_all_movies(Movie* head);

// 根据影片名查找 Movie 节点  
Movie* find_movie_by_name(Movie* head, const char* movie_name);

// 根据影片名和影院名查找 Movie 节点  
void find_movies_by_name_and_cinema(Movie* head, const char* movie_name, const char* cinema_name);

// 根据放映场次类型过滤  
void find_movies_by_theater_type(Movie* head, const char* theater_type);

// 根据放映开始时间排序  
void sort_movies_by_start_time(Movie** head);

// 根据票价排序  
void sort_movies_by_price(Movie** head);

// 根据余票数排序  
void sort_movies_by_remaining_ticket(Movie** head);

// 购票功能  
void purchase_ticket(Movie* movie, int number_of_tickets);

#endif // MOVIE_C_MOVIE_H
