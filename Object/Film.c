#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Film.h"
#include "..\hash.txt"
#include"..\Structure File\linked_list.h"

// �����µ�Ӱ
Film* film_create(Film_hash_table* hashTable, const char* id, const char* name, const char* type,
    const char* language, const char* summary, int time,int rating) {
    Film* new_film = (Film*)malloc(sizeof(Film));
    if (!new_film) return NULL;

    new_film->film_id = strdup(id);
    new_film->film_name = strdup(name);
    new_film->film_type = strdup(type);
    new_film->film_language = strdup(language);
    new_film->film_summary = strdup(summary);
    new_film->film_time = time;
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
Film* film_copy_list(Film* head)
{
    if (!head) return NULL;
    Film* current = head;
    Film* new_head = NULL;
    while (current) {
        // Ϊ��Film�ṹ�����ڴ�
        Film* new_film = (Film*)malloc(sizeof(Film));
        if (!new_film) {
            // �����ڴ����ʧ�����
            perror("Failed to allocate memory for new film");
            exit(EXIT_FAILURE);
        }

        // �����ַ����ֶ�
        new_film->film_id = strdup(current->film_id);
        new_film->film_name = strdup(current->film_name);
        new_film->film_type = strdup(current->film_type);
        new_film->film_language = strdup(current->film_language);
        new_film->film_summary = strdup(current->film_summary);

        // ������ֵ�ֶ�
        new_film->film_time = current->film_time;
        new_film->film_rating = current->film_rating;

        // ������������
        new_film->next = NULL;
        new_film->hash_next_id = NULL;
        new_film->hash_next_name = NULL;

        film_add_to_list(&new_head, new_film);
        current = current->next;
    }
    return new_head;
}
int compare_films_by_ratings(const void* a, const void* b)//��������
{
    Film* film1 = *(Film* const*)a;
    Film* film2 = *(Film* const*)b;
    if (film1->film_rating< film2->film_rating) return 1;
    return -1;
}
Film* film_sort(Film* head, int* compare(void*, void*)) {
    Film** films = NULL;
    int count = 0;

    // ���ȣ����������еĵ�Ӱ����  
    Film* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // ����һ���������洢���е�Ӱ��ָ��  
    films = (Film**)malloc(count * sizeof(Film*));
    if (!films) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // �����е�Ӱ��ָ��洢��������  
    int i = 0;
    current = head;
    while (current != NULL) {
        films[i++] = current;
        current = current->next;
    }

    // ʹ��qsort�������������  
    qsort(films, count, sizeof(Film*), compare);

    // ���¹�������  
    Film* new_head = films[0];
    for (i = 1; i < count; i++) {
        films[i - 1]->next = films[i];
    }
    films[count - 1]->next = NULL;

    // �ͷ������ڴ�  
    free(films);

    return new_head;
}
// ��ʾ������Ӱ����Ϣ
void film_show(const Film* film) {
    if (film) {
        printf("Film ID: %s\n", film->film_id);
        printf("Name: %s\n", film->film_name);
        printf("Type: %s\n", film->film_type);
        printf("Language: %s\n", film->film_language);
        printf("Summary: %s\n", film->film_summary);
        printf("Time:%d\n", film->film_time);
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

Film* film_list_free(Film* head)
{
    Film* temp = head;

    while (head)
    {
        temp = head;
        head = head->next;

        if (temp->film_id) free(temp->film_id);
        if (temp->film_language) free(temp->film_language);
        if (temp->film_name) free(temp->film_name);
        if (temp->film_summary) free(temp->film_summary);
        if (temp->film_time) free(temp->film_time);
        if (temp->film_type) free(temp->film_type);

        free(temp);
        temp = NULL;
    }
}
