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

// 从用户输入中创建 Movie 并添加到链表
//gc:这个函数先别修了，就放着别管，保证编译能过就行
//或者直接把他注释掉
void add_movie_from_input(Movie** head);

// 显示单个 Movie 的信息  
void movie_show(const Movie* movie);

// 显示链表中所有 Movie 的信息  
void movie_show_all(Movie* head);

// 根据影片名查找 Movie 节点  
Movie* movie_find_by_name(Movie* head, const char* movie_name);

// 根据影片名和影院名查找 Movie 节点  
void movie_find_by_name_and_cinema(Movie* head, const char* movie_name, const char* cinema_name);

// 根据放映场次类型过滤  
void movie_find_by_theater_type(Movie* head, const char* theater_type);

// 根据放映开始时间排序  
void movie_sort_by_start_time(Movie** head);

// 比较函数，用于根据票价排序  
int compare_by_price(const void* a, const void* b);
// 根据票价排序
void movie_sort_by_price(Movie** head);


// 比较函数，用于根据余票数排序  
int compare_by_remaining_ticket(const void* a, const void* b);
// 根据余票数排序  
void movie_sort_by_remaining_ticket(Movie** head);

// 购票功能  
void purchase_ticket(Movie* movie, int number_of_tickets);

#endif // MOVIE_C_MOVIE_H
