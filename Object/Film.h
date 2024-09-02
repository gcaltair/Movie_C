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

// �����µ�Ӱ
Film* film_create(Film_hash_table* hashTable, const char* id, const char* name, const char* type,
    const char* language, const char* summary, int rating);

// ����Ӱ��ӵ�������
void film_add_to_list(Film** head, Film* new_film);

// �����ֲ��ҵ�Ӱ
Film* film_find_by_name(Film* head, const char* name);

// ��ʾ������Ӱ����Ϣ
void film_show(const Film* film);

// ��ʾ���е�Ӱ����Ϣ
void film_show_all(Film* head);

// ��Ӱ��ϣ��ṹ
typedef struct Film_hash_table {
    Film* table_by_id[HASH_TABLE_SIZE];
    Film* table_by_name[HASH_TABLE_SIZE];
} Film_hash_table;

// ������Ӱ��ϣ��
Film_hash_table* film_hash_table_create();

// ��ʼ����Ӱ��ϣ��
void init_film_hash_table(Film_hash_table* ht);

// �����Ӱ����ϣ����
void insert_film_to_hash_table(Film_hash_table* ht, Film* film);

// ��ID���ҹ�ϣ���еĵ�Ӱ
Film* find_film_in_hash_table_by_id(Film_hash_table* ht, const char* film_id);

// �����ֲ��ҹ�ϣ���еĵ�Ӱ
Film* find_film_in_hash_table_by_name(Film_hash_table* ht, const char* film_name);

#endif //MOVIE_C_FILM_H
