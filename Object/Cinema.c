//
// Created by G on 2024/8/27.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Cinema.h"
#include "Theater.h"

Cinema *cinema_create(const char *name, const char *location, char* id) {
    // 动态分配内存给Cinema结构体
    Cinema* cinema = (Cinema*)malloc(sizeof(Cinema));
    if (cinema == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // 动态分配内存并复制参数内容到结构体字段
    cinema->cinema_name = strdup(name);
    cinema->location = strdup(location);
    cinema->cinema_id = strdup(id);
    cinema->next=NULL;
    cinema->my_theater=NULL;
    cinema->peek_time = NULL;
    return cinema;
}
void cinema_show(const Cinema* cinema) {
    if (cinema == NULL) {
        printf("Cinema Data is NULL.\n");
        return;
    }

    printf("Cinema Name: %s\n", cinema->cinema_name);
    printf("Location: %s\n", cinema->location);
    printf("Cinema ID: %s\n", cinema->cinema_id);
}
void cinema_show_detail(const Cinema* cinema){
    cinema_show(cinema);
}
Cinema* cinema_create_list(Cinema* new_cinema)
{
    return new_cinema;
}
void cinema_add_to_list(Cinema** head,Cinema* new_cinema) {
    if (*head == NULL) {
        *head = new_cinema;
        return;
    }

    Cinema* temp = new_cinema;
    temp->next=*head;
    *head=temp;

}
Cinema* cinema_find_by_id(Cinema* head, const char* id) {
    Cinema* temp = head;
    //if(!temp->cinema_id&&(!temp))
    while (temp != NULL) {
            if (strcmp(temp->cinema_id,id)== 0) {
            return temp;
        }
        temp = temp->next;
    }
    printf("Not found Cinema ID %s\n",id);
    return NULL; // 如果没有找到匹配的ID，返回NULL
}
void cinema_show_all(Cinema* head) {
    Cinema* temp = head;
    while (temp != NULL) {
        cinema_show(temp);
        temp = temp->next;
    }
}
