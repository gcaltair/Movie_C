#ifndef MOVIE_C_MOVIE_H  
#define MOVIE_C_MOVIE_H  

#include "Theater.h"
#define HASH_TABLE_SIZE 100
typedef struct Movie_hash_table Movie_hash_table;
typedef struct Film Film;
typedef struct Film_hash_table Film_hash_table;
typedef struct Movie {
    char* movie_id;
    char* film_id;
    Film* film;
    char* theater_id;
    Theater* theater; // 指向在哪个影厅播放  
    
    char* start_time;
    char* end_time;
    int remaining_ticket;
    double price;
    double discount;

    struct Movie* next; // 指向下一个电影场次（链表）
    struct Movie *hash_next;
} Movie;

// 创建新的 Movie 节点  
Movie* movie_create(Movie_hash_table* movieHashTable, const char* movie_id, const char* film_id, Film* film, const char* theater_id, Theater* theater, const char* start_time, const char* end_time, int remaining_ticket, double price, double discount);

// 添加 Movie 到链表
void movie_add_to_list(Movie** head, Movie* newMovie);

// 显示单个 Movie 的信息  
void movie_show(const Movie* movie);

// 显示链表中所有 Movie 的信息  
void movie_show_all(Movie* head);

//根据剩余票数查找的比较函数(降序)
int compare_movies_by_remaining_ticket(const void* a, const void* b);

// 根据开始时间查找的比较函数  
int compare_movies_by_start_time(const void* a, const void* b);
// movie排序函数
Movie* movie_sort(Movie* head, int* compare(void*, void*));


Movie* movie_filter_by_film_type(Movie* head, const char* film_type);

//根据电影名筛选场次
Movie* movie_filter_by_film_name(char* name, Movie* head);

//按场次收入排序(降序)
int compare_movies_by_income(const void* a, const void* b);

//创建一个根据电影名所查到的场次链表
Movie* movie_list_create_by_film_name(char* name, Film_hash_table* film_hash_table, Movie_hash_table* movie_hash_table);

typedef struct Movie_hash_table{
    Movie *table[HASH_TABLE_SIZE];
}Movie_hash_table;

Movie_hash_table* movie_hash_table_create();
// 初始化哈希表
void movie_hash_table_init(Movie_hash_table* ht);

// 插入 Movie 到哈希表
void insert_movie_to_hash_table(Movie_hash_table* ht, Movie* movie);

// 在哈希表中查找 Movie
Movie* find_movie_in_hash_table(Movie_hash_table* ht, const char* movie_id);

//复制movie除哈希表与总链表的信息
Movie* movie_copy_info(Movie* movie);


//根据上座率排序(升序)
int compare_movies_by_occupancy_rate(const void* a, const void* b);

int compare_movies_by_price(const void* a, const void* b);

#endif // MOVIE_C_MOVIE_H
