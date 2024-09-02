#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Film.h"
#include "..\hash.txt"
#include"..\Structure File\linked_list.h"

// �����µ�Ӱ
Film* film_create(Film_hash_table* hashTable, const char* id, const char* name, const char* type,
    const char* language, const char* summary, int rating) {
    Film* new_film = (Film*)malloc(sizeof(Film));
    if (!new_film) return NULL;

    new_film->film_id = strdup(id);
    new_film->film_name = strdup(name);
    new_film->film_type = strdup(type);
    new_film->film_language = strdup(language);
    new_film->film_summary = strdup(summary);
    new_film->film_rating = rating;
    new_film->next = NULL;
    new_film->hash_next_id = NULL;
    new_film->hash_next_name = NULL;
    new_film->playing_movie = NULL;;

    insert_film_to_hash_table(hashTable, new_film);

    return new_film;
}

// ����Ӱ��ӵ�������
void film_add_to_list(Film** head, Film* new_film) {
    if ((*head) == NULL) 
    {
        (*head) = new_film;
        return;
    }
    new_film->next = *head;
    *head = new_film;
}

// �����ֲ��ҵ�Ӱ
Film* film_find_by_name(Film* head, const char* name) {
    while (head) {
        if (strcmp(head->film_name, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// ��ʾ������Ӱ����Ϣ
void film_show(const Film* film) {
    if (film) {
        printf("Film ID: %s\n", film->film_id);
        printf("Name: %s\n", film->film_name);
        printf("Type: %s\n", film->film_type);
        printf("Language: %s\n", film->film_language);
        printf("Summary: %s\n", film->film_summary);
        printf("Rating: %d\n", film->film_rating);
    }
}

// ��ʾ���е�Ӱ����Ϣ
void film_show_all(Film* head) {
    while (head) {
        film_show(head);
        head = head->next;
    }
}

// ������Ӱ��ϣ��
Film_hash_table* film_hash_table_create() {
    Film_hash_table* ht = (Film_hash_table*)malloc(sizeof(Film_hash_table));
    if (!ht) return NULL;
    init_film_hash_table(ht);
    return ht;
}

// ��ʼ����Ӱ��ϣ��
void init_film_hash_table(Film_hash_table* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table_by_id[i] = NULL;
        ht->table_by_name[i] = NULL;
    }
}

// �����Ӱ����ϣ����
void insert_film_to_hash_table(Film_hash_table* ht, Film* film) {
    unsigned int id_index = hash(film->film_id,strlen(film->film_id), 0x9747b28c);
    unsigned int name_index = hash(film->film_name,strlen(film->film_name), 0x9747b28c);
    //printf("Insert film %s\n",film->film_id);
    // ��ID����
    film->hash_next_id = ht->table_by_id[id_index];
    ht->table_by_id[id_index] = film;

    // �����ֲ���
    film->hash_next_name = ht->table_by_name[name_index];
    ht->table_by_name[name_index] = film;
}

// ��ID���ҹ�ϣ���еĵ�Ӱ
Film* find_film_in_hash_table_by_id(Film_hash_table* ht, const char* film_id) {
    unsigned int index = hash(film_id,strlen(film_id), 0x9747b28c);
    Film* film = ht->table_by_id[index];
    while (film) {
        if (strcmp(film->film_id, film_id) == 0) {
            return film;
        }
        film = film->hash_next_id;
    }
    return NULL;
}

// �����ֲ��ҹ�ϣ���еĵ�Ӱ
Film* find_film_in_hash_table_by_name(Film_hash_table* ht, const char* film_name) {
    unsigned int index = hash(film_name,strlen(film_name), 0x9747b28c);
    Film* film = ht->table_by_name[index];
    while (film) {
        if (strcmp(film->film_name, film_name) == 0) {
            return film;
        }
        film = film->hash_next_name;
    }
    return NULL;
}
