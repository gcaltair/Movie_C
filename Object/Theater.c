//
// Created by G on 2024/8/27.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Theater.h"
#include"Movie.h"
#include "Cinema.h"
#include "../hash.txt"
#include "../Structure File/linked_list.h"
#include"../Structure File/interval_tree.h"
// 创建并初始化一个新的 Theater 结构体
Theater* theater_create(Theater_hash_table *hashTable,const char* theater_id_, const char* name, int capacity, Cinema* cinema_,const char *cinema_id_, const char* type){
    // 动态分配内存给 Theater 结构体
    Theater* theater = (Theater*)malloc(sizeof(Theater));
    if (theater == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // 动态分配内存并复制参数内容到结构体字段
    theater->theater_id= strdup(theater_id_);
    theater->theater_name = strdup(name);
    theater->theater_capacity = capacity;
    theater->cinema = cinema_;
    theater->cinema_id= strdup(cinema_id_);
    theater->theater_type = strdup(type);
    theater->next = NULL;
    theater->hash_next=NULL;
    theater->my_movie=NULL;

    theater->time_line = NULL;
    insert_theater_to_hash_table(hashTable,theater);

    string_direct_add_to_list(&(cinema_->my_theater),theater->theater_id);
    return theater;
}

// 显示单个剧院信息
void theater_show(const Theater* theater) {
    if (theater == NULL) {
        printf("Theater Data is NULL.\n");
        return;
    }

    printf("Theater ID: %s\n",theater->theater_id);
    printf("Theater Name: %s\n", theater->theater_name);
    printf("Capacity: %d\n", theater->theater_capacity);
    printf("Cinema ID: %s\n",theater->cinema_id);
    printf("Theater Type: %s\n", theater->theater_type);
    printf("\n");
}

// 添加一个元素到剧院链表（头插法）
void theater_add_to_list(Theater** head, Theater* new_theater) {
    if (*head == NULL) {
        *head = new_theater;
        return;
    }

    new_theater->next = *head;
    *head = new_theater;
}

// 根据剧院名查找剧院
Theater* theater_find_by_name(Theater* head, const char* name) {
    Theater* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->theater_name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // 如果没有找到匹配的名字，返回NULL
}

// 显示所有剧院信息
void theater_show_all(Theater* head) {
    Theater* temp = head;
    while (temp != NULL) {
        theater_show(temp);
        temp = temp->next;
    }
}

Theater* theater_list_create_by_cinema(Cinema* cinema, Theater_hash_table* theater_hash_table)
{
    Theater* new_head = NULL;
    Linked_string_list* head_theater = cinema->my_theater;  
    while (head_theater)
    {
        Theater* theater_find = find_theater_in_hash_table(theater_hash_table, head_theater->id);  
        if (!theater_find)
        {
            printf("theater id %s theater list create failed\n", head_theater->id);
            _sleep(10000);
        }
        else
        {
            Theater* new_theater = theater_copy_info(theater_find);  
            theater_add_to_list(&new_head, new_theater);  
        }
        head_theater = head_theater->next;  
    }
    return new_head;
}
Theater* theater_copy_info(Theater* theater)
{
    if (!theater) {
        printf("Theater is null!\n");
        return NULL;
    }

    Theater* new_theater = (Theater*)malloc(sizeof(Theater));
    if (!new_theater) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // 复制当前 Theater 的信息到新节点
    new_theater->theater_id = strdup(theater->theater_id);
    new_theater->theater_name = strdup(theater->theater_name);
    new_theater->theater_capacity = theater->theater_capacity;
    new_theater->cinema = theater->cinema;  // 如果需要复制 Cinema 信息，需要另行实现
    new_theater->cinema_id = strdup(theater->cinema_id);
    new_theater->theater_type = strdup(theater->theater_type);

    new_theater->my_movie = NULL; 
    Linked_string_list* head_movie = theater->my_movie;

    new_theater->time_line = theater->time_line; 

    new_theater->next = NULL;
    new_theater->hash_next = NULL;

    return new_theater;
}
void theater_free_copied_list(Theater* theater_list)
{
    Theater* current_theater = theater_list;
    Theater* next_theater;

    while (current_theater != NULL)
    {
        // 释放与当前 Theater 相关的内存
        free(current_theater->theater_id);
        free(current_theater->theater_name);
        free(current_theater->cinema_id);
        free(current_theater->theater_type);

        // 移动到下一个 Theater
        next_theater = current_theater->next;
        free(current_theater);
        current_theater = next_theater;
    }
}


double get_theater_income(Theater* theater, Movie_hash_table* hash_table)
{
    double res = 0;
    Linked_string_list* head = theater->my_movie;
    while (head)
    {
        Movie* target = find_movie_in_hash_table(hash_table, head->id);
        res += (target->discount) * (target->price);

    }
    return res;
}
//这个函数有问题！！！！
int compare_theaters_by_income(const void* a, const void* b, void* context) {
    Theater* theater1 = *(Theater* const*)a;
    Theater* theater2 = *(Theater* const*)b;
    Movie_hash_table* movieHashTable = (Movie_hash_table*)context;

    return get_theater_income(theater1, movieHashTable) < get_theater_income(theater2, movieHashTable) ? 1 : -1;
}

//Theater* theater_sort(Theater* head, int (*compare)(const void*,const void*,void*), Movie_hash_table* movie_hash_table) {
//    Theater** theaters = NULL;
//    int count = 0;
//
//    // 首先，计算链表中的影厅数量  
//    Theater* current = head;
//    while (current != NULL) {
//        count++;
//        current = current->next;
//    }
//    // 分配一个数组来存储所有影厅的指针  
//    theaters = (Theater**)malloc(count * sizeof(Theater*));
//    if (!theaters) {
//        printf("Memory allocation failed!\n");
//        return NULL;
//    }
//
//    // 将所有影厅的指针存储到数组中  
//    int i = 0;
//    current = head;
//    while (current != NULL) {
//        theaters[i++] = current;
//        current = current->next;
//    }
//
//    // 使用qsort对数组进行排序  
//    qsort_s(theaters, count, sizeof(Theater*), compare,(void*)movie_hash_table);
//
//    // 重新构建链表  
//    Theater* new_head = theaters[0];
//    for (i = 1; i < count; i++) {
//        theaters[i - 1]->next = theaters[i];
//    }
//    theaters[count - 1]->next = NULL;
//
//    // 释放数组内存  
//    free(theaters);
//
//    return new_head;
//}

// 初始化哈希表，将所有的指针设置为 NULL
void init_theater_hash_table(Theater_hash_table* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    ht->count = 0;
}

// 创建并初始化一个 Theater_hash_table
Theater_hash_table* theater_hash_table_create() {
    Theater_hash_table* ht = (Theater_hash_table*)malloc(sizeof(Theater_hash_table));
    if (!ht) {
        return NULL;
    }
    init_theater_hash_table(ht);
    return ht;
}

// 使用哈希表将剧院插入表中
void insert_theater_to_hash_table(Theater_hash_table* ht, Theater* theater) {
    uint32_t index = hash(theater->theater_id, strlen(theater->theater_id), 0x9747b28c) % HASH_TABLE_SIZE;
    theater->hash_next = ht->table[index];  // 处理哈希冲突，将新剧院插入哈希链表头部
    ht->table[index] = theater;
    ht->count++;
}

// 在哈希表中查找剧院，通过 theater_id 查找
Theater* find_theater_in_hash_table(Theater_hash_table* ht, const char* theater_id) {
    if (!ht) { printf("theater hash table is null"); return NULL; }
    uint32_t index = hash(theater_id, strlen(theater_id), 0x9747b28c) % HASH_TABLE_SIZE;
    Theater* theater = ht->table[index];
    while (theater) {
        if (strcmp(theater->theater_id, theater_id) == 0) {
            return theater;  // 找到匹配的剧院，返回指针
        }
        theater = theater->hash_next;  // 使用hash_next指针继续查找哈希链表中的下一个剧院
    }
    printf("%s haven't find\n", theater_id);
    return NULL;  // 如果未找到，返回NULL
}

