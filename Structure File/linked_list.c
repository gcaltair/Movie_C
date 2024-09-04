//
// Created by G on 2024/8/31.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
void string_add_to_list(Linked_string_list** head, Linked_string_list* node);

void string_direct_add_to_list(Linked_string_list** head,const char* id)
{
    Linked_string_list *new_node=create_node(id);
    string_add_to_list(head,new_node);
}
void int_direct_add_to_list(Linked_int_list** head, const int value)
{
    Linked_int_list* new_node = create_int_node(value);
    int_add_to_list(head, new_node);
}
// 创建新的节点
Linked_string_list* create_node(const char* id)
{
    Linked_string_list* new_node = (Linked_string_list*)malloc(sizeof(Linked_string_list));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_node->id = strdup(id); // 复制字符串
    new_node->next = NULL;
    return new_node;
}
// 向链表中添加节点
void string_add_to_list(Linked_string_list** head, Linked_string_list* node)
{
    if(node==NULL)
    {
        perror("string node is NULL,add failed");
        return;
    }

    if (*head == NULL)
    {
        (*head)=node;
        return;
    }
    node->next = *head;
    *head = node;
}

// 根据ID查找节点
Linked_string_list* find_node_by_id(Linked_string_list* head, const char* id)
{
    while (head != NULL)
    {
        if (strcmp(head->id, id) == 0)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// 显示单个节点的内容
void string_node_show(Linked_string_list* node)
{
    if (node != NULL)
    {
        printf("Node ID: %s\n", node->id);
    }
    else
    {
        printf("Node is NULL\n");
    }
}
void string_node_show_all(Linked_string_list* head){
    while(head!=NULL)
    {
        string_node_show(head);
        head=head->next;
    }

}

// 释放链表节点的内存
void free_string_list(Linked_string_list* head)
{
    Linked_string_list* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->id); // 释放字符串
        free(temp);     // 释放节点
    }
}
// 创建新的节点
Linked_int_list* create_int_node(int value) {
    Linked_int_list* new_node = (Linked_int_list*)malloc(sizeof(Linked_int_list));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// 向链表中添加节点
void int_add_to_list(Linked_int_list** head, Linked_int_list* node) {
    if (node == NULL) {
        perror("int node is NULL, add failed");
        return;
    }

    if (*head == NULL) {
        *head = node;
        return;
    }
    node->next = *head;
    *head = node;
}

// 根据值查找节点
Linked_int_list* find_int_node_by_value(Linked_int_list* head, int value) {
    while (head != NULL) {
        if (head->value == value) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// 显示单个节点的内容
void int_node_show(Linked_int_list* node) {
    if (node != NULL) {
        printf("Node Value: %d\n", node->value);
    }
    else {
        printf("Node is NULL\n");
    }
}

// 显示链表中所有节点的内容
void int_node_show_all(Linked_int_list* head) {
    while (head != NULL) {
        int_node_show(head);
        head = head->next;
    }
}

// 释放链表节点的内存
void free_int_list(Linked_int_list* head) {
    Linked_int_list* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}