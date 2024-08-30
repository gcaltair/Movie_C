//
// Created by G on 2024/8/27.
//
/*
测试代码
Cinema* t = cinema_add("Cinema A", "Location A", 1);
Cinema *cinema_list= cinema_create_list(t);;
cinema_direct_add_to_list(&cinema_list, "Cinema C", "Location C", 3);
Theater *theater_temp= theater_add("theater1",20,cinema_list,"3D");
Theater *theater_list=theater_create_list(theater_temp);
theater_add_to_list(&theater_list,theater_temp); //只有使用这个函数添加对象到链表才会更新Cinema->Theater的指针
cinema_show(theater_temp->cinema);
theater_show(cinema_list->theater);

 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Theater.h"
#include "Cinema.h"
#include "../hash.txt"

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
    theater->cinema=cinema_;
    insert_theater_to_hash_table(hashTable,theater);
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
}

// 添加一个元素到剧院链表（头插法）
void theater_add_to_list(Theater** head, Theater* new_theater) {
    if (*head == NULL) {
        *head = new_theater;
        (*head)->cinema->theater=(*head);
        return;
    }

    new_theater->next = *head;
    *head = new_theater;
    (*head)->cinema->theater=(*head);
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
    uint32_t index = hash(theater_id, strlen(theater_id), 0x9747b28c) % HASH_TABLE_SIZE;
    Theater* theater = ht->table[index];
    while (theater) {
        if (strcmp(theater->theater_id, theater_id) == 0) {
            return theater;  // 找到匹配的剧院，返回指针
        }
        theater = theater->hash_next;  // 使用hash_next指针继续查找哈希链表中的下一个剧院
    }
    return NULL;  // 如果未找到，返回NULL
}

