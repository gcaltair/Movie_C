//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_CINEMA_H
#define MOVIE_C_CINEMA_H
#include "Theater.h"
typedef struct Cinema{
    char* cinema_name;
    char* location;
    int cinema_id;
    struct Cinema *next;
    struct Theater* theater;
}Cinema;
Cinema* cinema_create_list(Cinema* new_cinema); //创建链表头节点
void cinema_add_to_list(Cinema** head, Cinema* new_cinema);//添加一个元素到链表，头插法
void cinema_direct_add_to_list(Cinema** head,const char* name, const char* location, int id);
Cinema* cinema_find_by_id(Cinema* head, int id);
Cinema* cinema_add(const char* name, const char* location, int id);
void cinema_show(const Cinema* cinema);
void cinema_show_all(Cinema* head);


#endif //MOVIE_C_CINEMA_H
