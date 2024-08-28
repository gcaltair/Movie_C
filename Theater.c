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
// 创建并初始化一个新的 Theater 结构体
Theater* theater_add(const char* name, int capacity, Cinema* cinema_, const char* type) {
    // 动态分配内存给 Theater 结构体
    Theater* theater = (Theater*)malloc(sizeof(Theater));
    if (theater == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // 动态分配内存并复制参数内容到结构体字段
    theater->theater_name = strdup(name);
    theater->theater_capacity = capacity;
    theater->cinema = cinema_;
    theater->theater_type = strdup(type);
    theater->movie = NULL;  // 需要另外赋值
    theater->next = NULL;
    theater->cinema=cinema_;
    return theater;
}

// 显示单个剧院信息
void theater_show(const Theater* theater) {
    if (theater == NULL) {
        printf("Theater data is NULL.\n");
        return;
    }

    printf("Theater Name: %s\n", theater->theater_name);
    printf("Capacity: %d\n", theater->theater_capacity);
    if (theater->cinema != NULL) {
        printf("Cinema Name: %s\n", theater->cinema->cinema_name);
    }
    printf("Theater Type: %s\n", theater->theater_type);
}

// 创建剧院链表头节点
Theater* theater_create_list(Theater* new_theater) {
    return new_theater;
}

// 添加一个元素到剧院链表（头插法）
void theater_add_to_list(Theater** head, Theater* new_theater) {
    if (*head == NULL) {
        *head = new_theater;
        return;
    }

    new_theater->next = *head;
    *head = new_theater;
    (*head)->cinema->theater=(*head);
}

// 直接添加剧院元素到链表中
void theater_direct_add_to_list(Theater** head, const char* name, int capacity, Cinema* cinema, const char* type) {
    Theater* new_theater = theater_add(name, capacity, cinema, type);
    if (new_theater == NULL) {
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
