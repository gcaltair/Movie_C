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
// �����µĽڵ�
Linked_string_list* create_node(const char* id)
{
    Linked_string_list* new_node = (Linked_string_list*)malloc(sizeof(Linked_string_list));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_node->id = strdup(id); // �����ַ���
    new_node->next = NULL;
    return new_node;
}
// ����������ӽڵ�
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

// ����ID���ҽڵ�
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

// ��ʾ�����ڵ������
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

// �ͷ�����ڵ���ڴ�
void free_string_list(Linked_string_list* head)
{
    Linked_string_list* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->id); // �ͷ��ַ���
        free(temp);     // �ͷŽڵ�
    }
}
// �����µĽڵ�
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

// ����������ӽڵ�
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

// ����ֵ���ҽڵ�
Linked_int_list* find_int_node_by_value(Linked_int_list* head, int value) {
    while (head != NULL) {
        if (head->value == value) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// ��ʾ�����ڵ������
void int_node_show(Linked_int_list* node) {
    if (node != NULL) {
        printf("Node Value: %d\n", node->value);
    }
    else {
        printf("Node is NULL\n");
    }
}

// ��ʾ���������нڵ������
void int_node_show_all(Linked_int_list* head) {
    while (head != NULL) {
        int_node_show(head);
        head = head->next;
    }
}

// �ͷ�����ڵ���ڴ�
void free_int_list(Linked_int_list* head) {
    Linked_int_list* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}