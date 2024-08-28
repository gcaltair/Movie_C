// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_THEATER_H
#define MOVIE_C_THEATER_H

typedef struct Cinema Cinema;

typedef struct Theater {
    char* theater_name;
    int theater_capacity;
    struct Cinema* cinema;
    // 缺少座位图和座位号的定义
    char* theater_type;
    struct Movie* movie;
    struct Theater* next;
} Theater;

// 创建影厅链表头节点
Theater* theater_create_list(Theater* new_theater);

// 添加一个元素到影厅链表（头插法）
void theater_add_to_list(Theater** head, Theater* new_theater);

// 直接添加影厅元素到链表中
void theater_direct_add_to_list(Theater** head, const char* name, int capacity, Cinema* cinema, const char* type);

// 根据影厅名查找影厅
Theater* theater_find_by_name(Theater* head, const char* name);

// 添加新影厅
Theater* theater_add(const char* name, int capacity, Cinema* cinema, const char* type);

// 显示单个影厅信息
void theater_show(const Theater* theater);

// 显示所有影厅信息
void theater_show_all(Theater* head);

#endif //MOVIE_C_THEATER_H
