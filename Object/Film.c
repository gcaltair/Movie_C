#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Film.h"
#include "..\hash.txt"
#include"..\Structure File\linked_list.h"

// 创建新电影
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

// 将电影添加到链表中
void film_add_to_list(Film** head, Film* new_film) {
    if ((*head) == NULL) 
    {
        (*head) = new_film;
        return;
    }
    new_film->next = *head;
    *head = new_film;
}

// 按名字查找电影
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
        // 为新Film结构分配内存
        Film* new_film = (Film*)malloc(sizeof(Film));
        if (!new_film) {
            // 处理内存分配失败情况
            perror("Failed to allocate memory for new film");
            exit(EXIT_FAILURE);
        }

        // 复制字符串字段
        new_film->film_id = strdup(current->film_id);
        new_film->film_name = strdup(current->film_name);
        new_film->film_type = strdup(current->film_type);
        new_film->film_language = strdup(current->film_language);
        new_film->film_summary = strdup(current->film_summary);

        // 复制数值字段
        new_film->film_time = current->film_time;
        new_film->film_rating = current->film_rating;

        // 处理链表链接
        new_film->next = NULL;
        new_film->hash_next_id = NULL;
        new_film->hash_next_name = NULL;

        film_add_to_list(&new_head, new_film);
        current = current->next;
    }
    return new_head;
}
int compare_films_by_ratings(const void* a, const void* b)//降序排列
{
    Film* film1 = *(Film* const*)a;
    Film* film2 = *(Film* const*)b;
    if (film1->film_rating< film2->film_rating) return 1;
    return -1;
}
Film* film_sort(Film* head, int* compare(void*, void*)) {
    Film** films = NULL;
    int count = 0;

    // 首先，计算链表中的电影数量  
    Film* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // 分配一个数组来存储所有电影的指针  
    films = (Film**)malloc(count * sizeof(Film*));
    if (!films) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // 将所有电影的指针存储到数组中  
    int i = 0;
    current = head;
    while (current != NULL) {
        films[i++] = current;
        current = current->next;
    }

    // 使用qsort对数组进行排序  
    qsort(films, count, sizeof(Film*), compare);

    // 重新构建链表  
    Film* new_head = films[0];
    for (i = 1; i < count; i++) {
        films[i - 1]->next = films[i];
    }
    films[count - 1]->next = NULL;

    // 释放数组内存  
    free(films);

    return new_head;
}
// 显示单个电影的信息
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

// 显示所有电影的信息
void film_show_all(Film* head) {
    while (head) {
        film_show(head);
        head = head->next;
    }
}

// 创建电影哈希表
Film_hash_table* film_hash_table_create() {
    Film_hash_table* ht = (Film_hash_table*)malloc(sizeof(Film_hash_table));
    if (!ht) return NULL;
    init_film_hash_table(ht);
    return ht;
}

// 初始化电影哈希表
void init_film_hash_table(Film_hash_table* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table_by_id[i] = NULL;
        ht->table_by_name[i] = NULL;
    }
}

// 插入电影到哈希表中
void insert_film_to_hash_table(Film_hash_table* ht, Film* film) {
    unsigned int id_index = hash(film->film_id,strlen(film->film_id), 0x9747b28c);
    unsigned int name_index = hash(film->film_name,strlen(film->film_name), 0x9747b28c);
    //printf("Insert film %s\n",film->film_id);
    // 按ID插入
    film->hash_next_id = ht->table_by_id[id_index];
    ht->table_by_id[id_index] = film;

    // 按名字插入
    film->hash_next_name = ht->table_by_name[name_index];
    ht->table_by_name[name_index] = film;
}

// 按ID查找哈希表中的电影
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

// 按名字查找哈希表中的电影
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
