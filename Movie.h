#ifndef MOVIE_C_MOVIE_H  
#define MOVIE_C_MOVIE_H  

#include "Theater.h"  

typedef struct Movie {
    char* movie_name;
    char* session_number;
    Theater* theater; // ָ�����ĸ�Ӱ������  
    char* start_time;
    char* end_time;
    int remaining_ticket;
    double price;
    double discount;
    char* theater_type;
    struct Movie* next; // ָ����һ����Ӱ���Σ�������  
} Movie;

// �����µ� Movie �ڵ�  
Movie* movie_create(const char* session_number, Theater* play_theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* theater_type);

// ���� Movie ������
void movie_add_to_list(Movie** head, Movie* newMovie);

// ���û������д��� Movie �����ӵ�����
//gc:��������ȱ����ˣ��ͷ��ű�ܣ���֤�����ܹ�����
//����ֱ�Ӱ���ע�͵�
void add_movie_from_input(Movie** head);

// ��ʾ���� Movie ����Ϣ  
void movie_show(const Movie* movie);

// ��ʾ���������� Movie ����Ϣ  
void movie_show_all(Movie* head);

// ����ӰƬ������ Movie �ڵ�  
Movie* movie_find_by_name(Movie* head, const char* movie_name);

// ����ӰƬ����ӰԺ������ Movie �ڵ�  
void movie_find_by_name_and_cinema(Movie* head, const char* movie_name, const char* cinema_name);

// ���ݷ�ӳ�������͹���  
void movie_find_by_theater_type(Movie* head, const char* theater_type);

// ���ݷ�ӳ��ʼʱ������  
void movie_sort_by_start_time(Movie** head);

// �ȽϺ��������ڸ���Ʊ������  
int compare_by_price(const void* a, const void* b);
// ����Ʊ������
void movie_sort_by_price(Movie** head);


// �ȽϺ��������ڸ�����Ʊ������  
int compare_by_remaining_ticket(const void* a, const void* b);
// ������Ʊ������  
void movie_sort_by_remaining_ticket(Movie** head);

// ��Ʊ����  
void purchase_ticket(Movie* movie, int number_of_tickets);

#endif // MOVIE_C_MOVIE_H
