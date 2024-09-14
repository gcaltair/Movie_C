//
// Created by G on 2024/8/27.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Cinema.h"
#include "Theater.h"

Cinema *cinema_create(const char *name, const char* cinema_alphabet,const char *location, char* id) {
    // ��̬�����ڴ��Cinema�ṹ��
    Cinema* cinema = (Cinema*)malloc(sizeof(Cinema));
    if (cinema == NULL) {
        printf("�ڴ����ʧ��.\n");
        return NULL;
    }

    // ��̬�����ڴ沢���Ʋ������ݵ��ṹ���ֶ�
    cinema->cinema_name = strdup(name);
    cinema->cinema_alphabet = strdup(cinema_alphabet);
    cinema->location = strdup(location);
    cinema->cinema_id = strdup(id);
    cinema->next=NULL;
    cinema->my_theater=NULL;
    cinema->peak_time = NULL;
    return cinema;
}
void cinema_show(const Cinema* cinema) {
    if (cinema == NULL) {
        printf("��ӰԺ���ݲ�����.\n");
        return;
    }

    printf("��ӰԺ����: %s\n", cinema->cinema_name);
    printf("Cinema Alphabet: %s\n", cinema->cinema_alphabet);
    printf("�ص�: %s\n", cinema->location);
    printf("��ӰԺID: %s\n", cinema->cinema_id);
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
    return NULL; // ���û���ҵ�ƥ���ID������NULL
}
Cinema* cinema_find_by_name(Cinema* head, const char* name) {
    Cinema* temp = head;
    //if(!temp->cinema_id&&(!temp))
    while (temp != NULL) {
        if (strcmp(temp->cinema_name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // ���û���ҵ�ƥ���ID������NULL
}
void cinema_show_all(Cinema* head) {
    Cinema* temp = head;
    while (temp != NULL) {
        cinema_show(temp);
        temp = temp->next;
    }
}
