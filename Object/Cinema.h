//
// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_CINEMA_H
#define MOVIE_C_CINEMA_H
typedef struct Cinema{
    char* cinema_name;
    char* location;
    char* cinema_id;
    struct Cinema *next;
}Cinema;
Cinema* cinema_create(const char* name, const char* location, char* id);
Cinema* cinema_create_list(Cinema* new_cinema); //创建链表头节点
void cinema_add_to_list(Cinema** head, Cinema* new_cinema);//添加一个元素到链表，头插法
Cinema* cinema_find_by_id(Cinema* head, const char* id);

void cinema_show(const Cinema* cinema);
void cinema_show_all(Cinema* head);

void cinema_show_detail(const Cinema* cinema);

#endif //MOVIE_C_CINEMA_H
