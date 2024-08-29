#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Movie.h"
#include "Cinema.h"
// �����µ� Movie �ڵ�  
Movie* movie_create(const char* session_number, Theater* theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* theater_type) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (!newMovie) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newMovie->session_number = strdup(session_number); // ʹ�� strdup ���ڴ����͸���  
    newMovie->theater = theater;
    newMovie->start_time = strdup(start_time);
    newMovie->end_time = strdup(end_time);
    newMovie->remaining_ticket = remaining_ticket;
    newMovie->price = price;
    newMovie->discount = discount;
    newMovie->theater_type = strdup(theater_type);
    newMovie->next = NULL;

    return newMovie;
}

// ��� Movie ������  
void movie_add_to_list(Movie** head, Movie* newMovie) {
    if (*head == NULL) {
        *head = newMovie;
    }
    else {
        Movie* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newMovie;
    }
}

// ��ʾ���� Movie ����Ϣ  
void movie_show(const Movie* movie) {
    if (movie == NULL) return;
    printf("Session Number: %s\n", movie->session_number);
    printf("Play Theater: %s\n", movie->theater ? movie->theater->theater_name : "N/A");
    printf("Start Time: %s\n", movie->start_time);
    printf("End Time: %s\n", movie->end_time);
    printf("Remaining Tickets: %d\n", movie->remaining_ticket);
    printf("Price: %.2f\n", movie->price);
    printf("Discount: %.2f\n", movie->discount);
    printf("Theater Type: %s\n", movie->theater_type);
    printf("----------\n");
}

// ��ʾ���������� Movie ����Ϣ  
void movie_show_all(Movie* head) {
    Movie* current = head;
    while (current != NULL) {
        movie_show(current);
        current = current->next;
    }
}

