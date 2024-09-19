#ifndef MOVIE_C_MOVIE_H  
#define MOVIE_C_MOVIE_H  

#include "Theater.h"
#define HASH_TABLE_SIZE 100
typedef struct Movie_hash_table Movie_hash_table;
typedef struct Film Film;
typedef struct Film_hash_table Film_hash_table;
typedef struct User User;
typedef struct Movie {
    char* movie_id;
    char* film_id;
    Film* film;
    char* theater_id;
    Theater* theater; // ָ�����ĸ�Ӱ������  
    
    char* start_time;
    int start_min;
    char* end_time;
    int end_min;
    int remaining_ticket;
    double price;
    double discount;
    int(*seat_map)[26];
    struct Movie* next; // ָ����һ����Ӱ���Σ�����
    struct Movie *hash_next;
} Movie;

// �����µ� Movie �ڵ�  
Movie* movie_create(Movie_hash_table* movieHashTable, const char* movie_id, const char* film_id, Film* film, const char* theater_id, Theater* theater, const char* start_time, const char* end_time, int remaining_ticket, double price, double discount);

// ��� Movie ������
void movie_add_to_list(Movie** head, Movie* newMovie);

// ��ʾ���� Movie ����Ϣ  
void movie_show(const Movie* movie);



// ��ʾ���������� Movie ����Ϣ  
void movie_show_all(Movie* head);

//����ʣ��Ʊ�����ҵıȽϺ���(����)
int compare_movies_by_remaining_ticket(const void* a, const void* b);

// ���ݿ�ʼʱ����ҵıȽϺ���  
int compare_movies_by_start_time(const void* a, const void* b);
// movie������
Movie* movie_sort(Movie* head, int* compare(void*, void*));


//��������������(����)
int compare_movies_by_income(const void* a, const void* b);

//����һ�����ݵ�Ӱ�����鵽�ĳ�������
Movie* movie_list_create_by_film(Film* film, Movie_hash_table* movie_hash_table);

Movie* movie_list_create_by_cinema(Cinema* cinema, Theater_hash_table* theater_hash_table, Movie_hash_table* movie_hash_table);

Movie* movie_filter_by_theater_type(char* type, Movie* head);

Movie* movie_filter_by_time_period(Movie* head, char* start_time, char* end_time);
//ɸѡ�Ѿ����ŵĳ���
Movie* movie_filter_by_played(Movie* head);
//ɸѡδ���ŵĳ���
Movie* movie_filter_by_not_played(Movie* head);

Movie* movie_filter_by_current_date(Movie* head);

Movie* movie_filter_by_film_type(Movie* head, const char* film_type);

Movie* movie_filter_by_cinema_id(char* id, Movie* head);

Movie* movie_filter_by_cinema_name(char* name, Movie* head);

//���ݵ�Ӱ��ɸѡ����
Movie* movie_filter_by_film_name(char* name, Movie* head);
typedef struct Movie_hash_table{
    Movie *table[HASH_TABLE_SIZE];
    int count;
}Movie_hash_table;

Movie_hash_table* movie_hash_table_create();
// ��ʼ����ϣ��
void movie_hash_table_init(Movie_hash_table* ht);

// ���� Movie ����ϣ��
void insert_movie_to_hash_table(Movie_hash_table* ht, Movie* movie);

// �ڹ�ϣ���в��� Movie
Movie* find_movie_in_hash_table(Movie_hash_table* ht, const char* movie_id);

//����movie����ϣ�������������Ϣ
Movie* movie_copy_info(Movie* movie);

Movie* movie_operation_sort(Movie* head, int mode);

Movie* movie_operation_filter(Movie* head, int mode, void* filter_param);


//��������������(����)
int compare_movies_by_occupancy_rate(const void* a, const void* b);

int compare_movies_by_price(const void* a, const void* b);
//�ж��Ƿ������������ͻ�����ҷ��س�ͻ�ĳ�����
int is_avoid_flow(Cinema* cinema, int start_min, int end_min);

double caculate_movie_income(Movie* head);

int datetime_to_minutes(const char* datetime);

void movie_list_free(Movie* head);

int my_abs(int a, int b);

#endif // MOVIE_C_MOVIE_H
