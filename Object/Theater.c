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
    theater->movie = NULL;  // 需要另外赋值
    theater->next = NULL;
    theater->hash_next=NULL;
    theater->my_movie=NULL;
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

