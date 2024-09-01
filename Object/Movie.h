#ifndef MOVIE_C_MOVIE_H  
#define MOVIE_C_MOVIE_H  

#include "Theater.h"
#define HASH_TABLE_SIZE 100
typedef struct Movie_hash_table Movie_hash_table;
typedef struct Movie {
    char* movie_id;
    char* movie_name;


    Theater* theater; // 指向在哪个影厅播放  

    char* start_time;
    char* end_time;
    int remaining_ticket;
    double price;
    double discount;
    char* movie_type;

    struct Movie* next; // 指向下一个电影场次（链表）
    struct Movie *hash_next;
} Movie;

// 创建新的 Movie 节点  
Movie* movie_create(Movie_hash_table *movieHashTable,const char* movie_id, const char* movie_name,Theater* play_theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* movie_type);

// 添加 Movie 到链表
void movie_add_to_list(Movie** head, Movie* newMovie);

// 显示单个 Movie 的信息  
void movie_show(const Movie* movie);

// 显示链表中所有 Movie 的信息  
void movie_show_all(Movie* head);

// 通过放映时间排序movie
int compare_movies_by_start_time(const void* a, const void* b);// 声明一个比较函数，用于qsort  
Movie* movie_sort_by_start_time(Movie* head);// 对所有电影场次按放映时间进行排序  
Movie* movie_filter_by_movie_type(Movie* head, const char* movie_type);

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


#endif // MOVIE_C_MOVIE_H
