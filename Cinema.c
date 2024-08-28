//
// Created by G on 2024/8/27.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Cinema.h"

Cinema *cinema_add(const char *name, const char *location, int id,Cinema* next) {
    // 动态分配内存给Cinema结构体
    Cinema* cinema = (Cinema*)malloc(sizeof(Cinema));
    if (cinema == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // 动态分配内存并复制参数内容到结构体字段
    cinema->cinema_name = strdup(name);
    cinema->location = strdup(location);
    cinema->cinema_id = id;

    return cinema;
}
void cinema_show(const Cinema* cinema) {
    if (cinema == NULL) {
        printf("Cinema data is NULL.\n");
        return;
    }

    printf("Cinema Name: %s\n", cinema->cinema_name);
    printf("Location: %s\n", cinema->location);
    printf("Cinema ID: %d\n", cinema->cinema_id);
}
Cinema* cinema_create_list(const char* name, const char* location, int id,Cinema* next)
{
    // 创建新的Cinema节点
    Cinema* head = (Cinema*)malloc(sizeof(Cinema));
    if (head == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // 动态分配内存并复制参数内容到结构体字段
    head->cinema_name = strdup(name);
    head->location = strdup(location);
    head->cinema_id = id;
    head->next = NULL; // 初始化时next指向NULL

    return head;
}
void cinema_add_to_list(Cinema** head, const char* name, const char* location, int id,Cinema* next) {
    Cinema* new_cinema = cinema_add(name, location, id,NULL);
    if (*head == NULL) {
        *head = new_cinema;
        return;
    }

    Cinema* temp = new_cinema;
    temp->next=*head;
    *head=temp;

}
Cinema* cinema_find_by_id(Cinema* head, int id) {
    Cinema* temp = head;
    while (temp != NULL) {
        if (temp->cinema_id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // 如果没有找到匹配的ID，返回NULL
}
void cinema_show_all(Cinema* head) {
    Cinema* temp = head;
    while (temp != NULL) {
        cinema_show(temp);
        temp = temp->next;
    }
}
