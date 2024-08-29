// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_THEATER_H
#define MOVIE_C_THEATER_H

typedef struct Cinema Cinema;

typedef struct Theater {
    char* theater_name;
    int theater_capacity;
    struct Cinema* cinema;
    // ȱ����λͼ����λ�ŵĶ���
    char* theater_type;
    struct Movie* movie;
    struct Theater* next;
} Theater;

// ����Ӱ������ͷ�ڵ�
Theater* theater_create_list(Theater* new_theater);

// ���һ��Ԫ�ص�Ӱ������ͷ�巨��
void theater_add_to_list(Theater** head, Theater* new_theater);

// ֱ�����Ӱ��Ԫ�ص�������
void theater_direct_add_to_list(Theater** head, const char* name, int capacity, Cinema* cinema, const char* type);

// ����Ӱ��������Ӱ��
Theater* theater_find_by_name(Theater* head, const char* name);

// �����Ӱ��
Theater* theater_create(const char* name, int capacity, Cinema* cinema, const char* type);

// ��ʾ����Ӱ����Ϣ
void theater_show(const Theater* theater);

// ��ʾ����Ӱ����Ϣ
void theater_show_all(Theater* head);

#endif //MOVIE_C_THEATER_H
