#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Movie.h"
#include "Cinema.h"
#include "../hash.txt"
// 创建新的 Movie 节点  
Movie* movie_create(Movie_hash_table *movieHashTable,const char* movie_id, const char *movie_name,Theater* theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* theater_type) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (!newMovie) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    if (!theater) { printf("Movie %s's Theater is null\n",movie_id); newMovie->theater = NULL;}
    else newMovie->theater = theater;
    newMovie->movie_id= strdup(movie_id); // 使用 strdup 简化内存分配和复制
    newMovie->movie_name= strdup(movie_name);
    
    newMovie->start_time = strdup(start_time);
    newMovie->end_time = strdup(end_time);
    newMovie->remaining_ticket = remaining_ticket;
    newMovie->price = price;
    newMovie->discount = discount;
    newMovie->theater_type = strdup(theater_type);
    newMovie->next = NULL;
    insert_movie_to_hash_table(movieHashTable,newMovie);
    return newMovie;
}

// 添加 Movie 到链表  
void movie_add_to_list(Movie** head, Movie* newMovie) {
    if (*head == NULL) {
        *head = newMovie;
    }
    else {
        Movie* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newMovie;
    }
}

// 显示单个 Movie 的信息  
void movie_show(const Movie* movie) {
    if (movie == NULL) return;
    printf("Movie ID: %s\n",movie->movie_id);
    printf("Movie Name: %s\n", movie->movie_name);
    printf("Play Theater: %s\n", movie->theater ? movie->theater->theater_name : "N/A");
    printf("Start Time: %s\n", movie->start_time);
    printf("End Time: %s\n", movie->end_time);
    printf("Remaining Tickets: %d\n", movie->remaining_ticket);
    printf("Price: %.2f\n", movie->price);
    printf("Discount: %.2f\n", movie->discount);
    printf("Theater Type: %s\n", movie->theater_type);
    printf("----------\n");
}

// 显示链表中所有 Movie 的信息  
void movie_show_all(Movie* head) {
    Movie* current = head;
    while (current != NULL) {
        movie_show(current);
        current = current->next;
    }
}


// 创建哈希表
Movie_hash_table* movie_hash_table_create() {
    Movie_hash_table* ht = (Movie_hash_table*)malloc(sizeof(Movie_hash_table));
    if (!ht) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    movie_hash_table_init(ht);
    return ht;
}

// 初始化哈希表
void movie_hash_table_init(Movie_hash_table* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// 插入 Movie 到哈希表
void insert_movie_to_hash_table(Movie_hash_table* ht, Movie* movie) {
    unsigned int index = hash(movie->movie_id, strlen(movie->movie_id), 0x9747b28c); // 使用MurmurHash2生成索引
    movie->hash_next = ht->table[index];  // 将当前的哈希表索引处的元素放在新电影的后面
    ht->table[index] = movie;             // 将新电影放在链表的头部
}

// 在哈希表中查找 Movie，通过 movie_id 查找
Movie* find_movie_in_hash_table(Movie_hash_table* ht, const char* movie_id) {
    unsigned int index = hash(movie_id, strlen(movie_id), 0x9747b28c);
    Movie* movie = ht->table[index];
    while (movie) {
        if (strcmp(movie->movie_id, movie_id) == 0) {
            return movie;  // 找到电影，返回指针
        }
        movie = movie->hash_next;  // 继续查找链表中的下一个电影
    }
    return NULL;  // 如果未找到，返回NULL
}















//// 根据影片名查找 Movie 节点
//Movie* movie_find_by_name(Movie* head, const char* movie_name_) {
//    Movie* current = head;
//    while (current != NULL) {
//        if (strcmp(current->movie_name, movie_name_) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//    return NULL;
//}
//// 根据影片名和影院名查找 Movie 节点
//Movie* movie_find_by_name_and_cinema(Movie * head, const char* movie_name, const char* cinema_name)
//{
//    Movie* current = head;
//    while (current != NULL) {
//        if (strcmp(current->movie_name, movie_name) == 0 && strcmp(current->theater->cinema->cinema_name, cinema_name) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//    return NULL;
//}
////
////
//// 根据放映场次类型过滤
//void movie_find_by_theater_type(Movie* head, const char* theater_type) {
//    Movie* current = head;
//    while (current != NULL) {
//        if (strcmp(current->theater_type, theater_type) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//    return NULL;
//}
