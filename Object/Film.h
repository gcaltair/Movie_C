#ifndef MOVIE_C_FILM_H
#define MOVIE_C_FILM_H

#define HASH_TABLE_SIZE 100

typedef struct Film_hash_table Film_hash_table;

typedef struct Linked_string_list Linked_string_list;
typedef struct Film {
    char* film_id;
    char* film_name;
    char* film_type;
    char* film_language;
    char* film_summary;
    int film_rating;
    struct Film* next;
    struct Film* hash_next_id;
    struct Film* hash_next_name;
    Linked_string_list* playing_movie;
} Film;

// 创建新电影
Film* film_create(Film_hash_table* hashTable, const char* id, const char* name, const char* type,
    const char* language, const char* summary, int rating);

// 将电影添加到链表中
void film_add_to_list(Film** head, Film* new_film);

// 按名字查找电影
Film* film_find_by_name(Film* head, const char* name);

// 显示单个电影的信息
void film_show(const Film* film);

// 显示所有电影的信息
void film_show_all(Film* head);

// 电影哈希表结构
typedef struct Film_hash_table {
    Film* table_by_id[HASH_TABLE_SIZE];
    Film* table_by_name[HASH_TABLE_SIZE];
} Film_hash_table;

// 创建电影哈希表
Film_hash_table* film_hash_table_create();

// 初始化电影哈希表
void init_film_hash_table(Film_hash_table* ht);

// 插入电影到哈希表中
void insert_film_to_hash_table(Film_hash_table* ht, Film* film);

// 按ID查找哈希表中的电影
Film* find_film_in_hash_table_by_id(Film_hash_table* ht, const char* film_id);

// 按名字查找哈希表中的电影
Film* find_film_in_hash_table_by_name(Film_hash_table* ht, const char* film_name);

#endif //MOVIE_C_FILM_H
