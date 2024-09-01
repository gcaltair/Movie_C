#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Movie.h"
#include "Cinema.h"
#include "Order.h"
#include "../hash.txt"
#include "../Structure File/linked_list.h"
// 创建新的 Movie 节点  
Movie* movie_create(Movie_hash_table *movieHashTable,const char* movie_id, const char *movie_name,Theater* theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* movie_type) {
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
    newMovie->movie_type = strdup(movie_type);
    newMovie->next = NULL;
    insert_movie_to_hash_table(movieHashTable,newMovie);

    //string_direct_add_to_list(&(theater->my_movie),newMovie->movie_id);

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
    printf("Movie Type: %s\n", movie->movie_type);
    printf("----------\n");
}

// 显示链表中所有 Movie 的信息  
void movie_show_all(Movie* head) {
    Movie* movie = head;
    while (movie != NULL) {
        movie_show(movie);
        movie = movie->next;
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
Movie *movie_copy_info(Movie* movie)
{

    Movie* new_movie = (Movie*)malloc(sizeof(Movie));
    if (!new_movie) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // 复制当前电影的信息到新节点
    new_movie->movie_id = strdup(movie->movie_id);
    new_movie->movie_name = strdup(movie->movie_name);
    new_movie->theater = movie->theater;
    new_movie->start_time = strdup(movie->start_time);
    new_movie->end_time = strdup(movie->end_time);
    new_movie->remaining_ticket = movie->remaining_ticket;
    new_movie->price = movie->price;
    new_movie->discount = movie->discount;
    new_movie->movie_type = strdup(movie->movie_type);
    new_movie->next = NULL;
    new_movie->hash_next=NULL;
    return new_movie;
}
// 根据放映场次类型过滤
Movie* movie_filter_by_movie_type(Movie* head, const char* movie_type) {
    Movie* result_head = NULL;  // 结果链表的头节点
    Movie* movie = head;

    // 遍历原链表
    while (movie != NULL) {
        // 如果电影的 movie_type 符合条件
        if (strcmp(movie->movie_type, movie_type) == 0) {
            // 创建一个新节点，将其添加到结果链表
            Movie* new_movie = movie_copy_info(movie);

            // 将新节点添加到结果链表
            movie_add_to_list(&result_head,new_movie);
        }
        movie = movie->next;  // 继续遍历原链表中的下一个电影
    }
    return result_head;  // 返回结果链表的头节点
}

// 创建新链表并对其进行排序
Movie* movie_sort_by_purchased_ticket(Movie* head) {
    Movie* new_head = NULL;
    char current_time[20];
    get_current_time(current_time, sizeof(current_time));

    // 遍历原链表，将未放映的场次添加到新链表中
    Movie* current = head;
    while (current != NULL) {
        // 判断电影是否未放映：end_time > current_time
        if (strcmp(current->end_time, current_time) > 0) {
            // 复制节点
            Movie* new_node = (Movie*)malloc(sizeof(Movie));
            *new_node = *current;  // 复制节点内容
            new_node->next = new_head;
            new_head = new_node;
        }
        current = current->next;
    }

    // 对新链表按余票数进行排序（余票少的排在前面）
    if (new_head != NULL) {
        int swapped;
        do {
            swapped = 0;
            Movie* ptr = new_head;
            Movie* prev = NULL;
            while (ptr->next != NULL) {
                if (ptr->remaining_ticket > ptr->next->remaining_ticket) {
                    // 交换节点数据
                    if (prev == NULL) {
                        // 交换的是头节点
                        Movie* temp = ptr->next;
                        ptr->next = temp->next;
                        temp->next = ptr;
                        new_head = temp;
                        prev = new_head;
                    }
                    else {
                        Movie* temp = ptr->next;
                        ptr->next = temp->next;
                        temp->next = ptr;
                        prev->next = temp;
                        prev = temp;
                    }
                    swapped = 1;
                }
                else {
                    prev = ptr;
                    ptr = ptr->next;
                }
            }
        } while (swapped);
    }

    return new_head;
}

// 计算上座率
double calculate_occupancy_rate(Movie* movie) {
    // 假设上座率计算为: 已售票数 / (已售票数 + 剩余票数)
    int sold_tickets = movie->remaining_ticket; // 剩余票数
    return (sold_tickets > 0) ? 1.0 / sold_tickets : 1.0;
}

// 创建新链表并对其进行排序
Movie* movie_sort_by_occupancy_rate(Movie* head) {
    Movie* new_head = NULL;
    char current_time[20];
    get_current_time(current_time, sizeof(current_time));

    // 遍历原链表，将已放映结束的场次添加到新链表中
    Movie* current = head;
    while (current != NULL) {
        // 判断电影是否已放映结束：end_time <= current_time
        if (strcmp(current->end_time, current_time) <= 0) {
            // 复制节点
            Movie* new_node = (Movie*)malloc(sizeof(Movie));
            *new_node = *current;  // 复制节点内容
            new_node->next = new_head;
            new_head = new_node;
        }
        current = current->next;
    }

    // 对新链表按上座率进行排序（上座率高的排在前面）
    if (new_head != NULL) {
        int swapped;
        do {
            swapped = 0;
            Movie* ptr = new_head;
            Movie* prev = NULL;
            while (ptr->next != NULL) {
                double current_occupancy = calculate_occupancy_rate(ptr);
                double next_occupancy = calculate_occupancy_rate(ptr->next);
                if (current_occupancy < next_occupancy) {
                    // 交换节点数据
                    if (prev == NULL) {
                        // 交换的是头节点
                        Movie* temp = ptr->next;
                        ptr->next = temp->next;
                        temp->next = ptr;
                        new_head = temp;
                        prev = new_head;
                    }
                    else {
                        Movie* temp = ptr->next;
                        ptr->next = temp->next;
                        temp->next = ptr;
                        prev->next = temp;
                        prev = temp;
                    }
                    swapped = 1;
                }
                else {
                    prev = ptr;
                    ptr = ptr->next;
                }
            }
        } while (swapped);
    }

    return new_head;
}
//按场次总票价收入排序已经放映结束的所有历史场次信息
//（可以按日期分区段进行排序显示）


    // 声明一个比较函数，用于qsort  
int compare_movies_by_start_time(const void* a, const void* b) {
    Movie* movie1 = *(Movie* const*)a;
    Movie* movie2 = *(Movie* const*)b;
    return strcmp(movie1->start_time, movie2->start_time);
}
    // 对所有电影场次按放映时间进行排序  
Movie* movie_sort_by_start_time(Movie* head) {
    Movie** movies = NULL;
    int count = 0;

    // 首先，计算链表中的电影数量  
    Movie* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // 分配一个数组来存储所有电影的指针  
    movies = (Movie**)malloc(count * sizeof(Movie*));
    if (!movies) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // 将所有电影的指针存储到数组中  
    int i = 0;
    current = head;
    while (current != NULL) {
        movies[i++] = current;
        current = current->next;
    }

    // 使用qsort对数组进行排序  
    qsort(movies, count, sizeof(Movie*), compare_movies_by_start_time);

    // 重新构建链表  
    Movie* new_head = movies[0];
    for (i = 1; i < count; i++) {
        movies[i - 1]->next = movies[i];
    }
    movies[count - 1]->next = NULL;

    // 释放数组内存  
    free(movies);

    return new_head;
}



