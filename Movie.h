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
    struct Movie* next; // ָ����һ����Ӱ���Σ�����  
} Movie;

// �����µ� Movie �ڵ�  
Movie* movie_create(const char* session_number, Theater* play_theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* theater_type);

// ��� Movie ������
void movie_add_to_list(Movie** head, Movie* newMovie);

// ��ʾ���� Movie ����Ϣ  
void movie_show(const Movie* movie);

// ��ʾ���������� Movie ����Ϣ  
void movie_show_all(Movie* head);

#endif // MOVIE_C_MOVIE_H
