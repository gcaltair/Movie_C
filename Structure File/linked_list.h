//
// Created by G on 2024/8/31.
//

#ifndef MOVIE_C_LINKED_LIST_H
#define MOVIE_C_LINKED_LIST_H
typedef struct Linked_string_list
{
    char* id;
    struct Linked_string_list* next;
}Linked_string_list;
Linked_string_list* create_node(const char* id);
void string_direct_add_to_list(Linked_string_list** head,const char* id);
Linked_string_list* find_node_by_id(Linked_string_list* head,const char* id);
void string_node_show(Linked_string_list* node);
void string_node_show_all(Linked_string_list* head);
void free_string_list(Linked_string_list* head);

typedef struct Linked_int_list {
    int value;
    struct Linked_int_list* next;
} Linked_int_list;
void int_direct_add_to_list(Linked_int_list** head, const int value);
Linked_int_list* create_int_node(int value);
void int_add_to_list(Linked_int_list** head, Linked_int_list* node);
Linked_int_list* find_int_node_by_value(Linked_int_list* head, int value);
void int_node_show(Linked_int_list* node);
void int_node_show_all(Linked_int_list* head);
void free_int_list(Linked_int_list* head);
#endif //MOVIE_C_LINKED_LIST_H
