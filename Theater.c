//
// Created by G on 2024/8/27.
//
/*
���Դ���
Cinema* t = cinema_add("Cinema A", "Location A", 1);
Cinema *cinema_list= cinema_create_list(t);;
cinema_direct_add_to_list(&cinema_list, "Cinema C", "Location C", 3);
Theater *theater_temp= theater_add("theater1",20,cinema_list,"3D");
Theater *theater_list=theater_create_list(theater_temp);
theater_add_to_list(&theater_list,theater_temp); //ֻ��ʹ�����������Ӷ�������Ż����Cinema->Theater��ָ��
cinema_show(theater_temp->cinema);
theater_show(cinema_list->theater);

 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Theater.h"
#include "Cinema.h"
// ��������ʼ��һ���µ� Theater �ṹ��
Theater* theater_add(const char* name, int capacity, Cinema* cinema_, const char* type) {
    // ��̬�����ڴ�� Theater �ṹ��
    Theater* theater = (Theater*)malloc(sizeof(Theater));
    if (theater == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // ��̬�����ڴ沢���Ʋ������ݵ��ṹ���ֶ�
    theater->theater_name = strdup(name);
    theater->theater_capacity = capacity;
    theater->cinema = cinema_;
    theater->theater_type = strdup(type);
    theater->movie = NULL;  // ��Ҫ���⸳ֵ
    theater->next = NULL;
    theater->cinema=cinema_;
    return theater;
}

// ��ʾ������Ժ��Ϣ
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

// ������Ժ����ͷ�ڵ�
Theater* theater_create_list(Theater* new_theater) {
    return new_theater;
}

// ���һ��Ԫ�ص���Ժ����ͷ�巨��
void theater_add_to_list(Theater** head, Theater* new_theater) {
    if (*head == NULL) {
        *head = new_theater;
        return;
    }

    new_theater->next = *head;
    *head = new_theater;
    (*head)->cinema->theater=(*head);
}

// ֱ����Ӿ�ԺԪ�ص�������
void theater_direct_add_to_list(Theater** head, const char* name, int capacity, Cinema* cinema, const char* type) {
    Theater* new_theater = theater_add(name, capacity, cinema, type);
    if (new_theater == NULL) {
        return;
    }

    new_theater->next = *head;
    *head = new_theater;
    (*head)->cinema->theater=(*head);
}

// ���ݾ�Ժ�����Ҿ�Ժ
Theater* theater_find_by_name(Theater* head, const char* name) {
    Theater* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->theater_name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // ���û���ҵ�ƥ������֣�����NULL
}

// ��ʾ���о�Ժ��Ϣ
void theater_show_all(Theater* head) {
    Theater* temp = head;
    while (temp != NULL) {
        theater_show(temp);
        temp = temp->next;
    }
}

