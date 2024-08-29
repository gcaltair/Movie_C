// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_THEATER_H
#define MOVIE_C_THEATER_H

#define HASH_TABLE_SIZE 100
typedef struct Cinema Cinema;
typedef struct Theater_hash_table Theater_hash_table;

typedef struct Theater {
    char* theater_id;
    char* theater_name;
    int theater_capacity;
    struct Cinema* cinema;
    char* cinema_id;
    // 缺少座位图和座位号的定义
    char* theater_type;
    struct Movie* movie;
    struct Theater* next;
    struct Theater* hash_next;
}Theater;

// 添加新影厅
Theater* theater_create(Theater_hash_table *hashTable, const char* id,
                        const char* name, int capacity, Cinema* cinema_,const char *cinema_id_, const char* type);

void theater_add_to_list(Theater** head, Theater* new_theater);
Theater* theater_find_by_name(Theater* head, const char* name);
void theater_show(const Theater* theater);
void theater_show_all(Theater* head);

typedef struct Theater_hash_table {
    Theater* table[HASH_TABLE_SIZE];
} Theater_hash_table;
Theater_hash_table* theater_hash_table_create();
void init_theater_hash_table(Theater_hash_table* ht);
void insert_theater_to_hash_table(Theater_hash_table* ht, Theater* theater);
Theater* find_theater_in_hash_table(Theater_hash_table* ht, const char* theater_id);
#endif //MOVIE_C_THEATER_H
