#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Movie.h"

// �����µ� Movie �ڵ�  
Movie* createMovie(const char* session_number, Theater* play_theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount, const char* theater_type) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (!newMovie) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newMovie->session_number = strdup(session_number); // ʹ�� strdup ���ڴ����͸���  
    newMovie->play_theater = play_theater;
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
void addMovie(Movie** head, Movie* newMovie) {
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

// ���û������д��� Movie ����ӵ�����  
void addMovieFromInput(Movie** head) {
    char session_number[50], start_time[50], end_time[50], theater_type[50];
    Theater* play_theater;
    int remaining_ticket;
    double price, discount;

    printf("Enter session number: ");
    scanf("%49s", session_number);

    char theater_name[20];
    printf("Enter play theater name: ");
    scanf("%19s", theater_name);
    play_theater = find_theater_by_name(theater_name);
    if (!play_theater) {
        printf("Theater not found. Cannot create movie.\n");
        return;
    }

    printf("Enter start time: ");
    scanf("%49s", start_time);

    printf("Enter end time: ");
    scanf("%49s", end_time);

    printf("Enter remaining ticket: ");
    scanf("%d", &remaining_ticket);

    printf("Enter price: ");
    scanf("%lf", &price);

    printf("Enter discount: ");
    scanf("%lf", &discount);

    printf("Enter theater type: ");
    scanf("%49s", theater_type);

    Movie* newMovie = createMovie(session_number, play_theater, start_time, end_time,
        remaining_ticket, price, discount, theater_type);
    if (newMovie) {
        addMovie(head, newMovie);
    }
}

// ����Ӱ���ĸ�������������Ӱ��������Ӱ��ָ��  
Theater* find_theater_by_name(const char* theater_name) {
    extern Theater* theater_list; // ���� theater_list ��ȫ�ֱ���
    Theater* current = theater_list;
    while (current != NULL) {
        if (strcmp(current->theater_name, theater_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// ����ӰƬ������ Movie �ڵ�  
Movie* find_movie_by_name(Movie* head, const char* movie_name) {
    Movie* current = head;
    while (current != NULL) {
        if (strcmp(current->session_number, movie_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// ����ӰƬ����ӰԺ������ Movie �ڵ�  
void find_movies_by_name_and_cinema(Movie* head, const char* movie_name, const char* cinema_name) {
    Movie* current = head;
    while (current != NULL) {
        if (strcmp(current->session_number, movie_name) == 0 && strcmp(current->play_theater->cinema->cinema_name, cinema_name) == 0) {
            show_movie(current);
        }
        current = current->next;
    }
}

// ���ݷ�ӳ�������͹���  
void find_movies_by_theater_type(Movie* head, const char* theater_type) {
    Movie* current = head;
    while (current != NULL) {
        if (strcmp(current->theater_type, theater_type) == 0) {
            show_movie(current);
        }
        current = current->next;
    }
}

// �ȽϺ��������ڸ��ݿ�ʼʱ������  
int compare_by_start_time(const void* a, const void* b) {
    const Movie* movie1 = *(const Movie**)a;
    const Movie* movie2 = *(const Movie**)b;
    return strcmp(movie1->start_time, movie2->start_time);
}

// �������г���  
void sort_movies_by_start_time(Movie** head) {
    int count = 0;
    Movie* current = *head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    Movie** array = (Movie**)malloc(count * sizeof(Movie*));
    current = *head;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    qsort(array, count, sizeof(Movie*), compare_by_start_time);

    for (int i = 0; i < count - 1; i++) {
        array[i]->next = array[i + 1];
    }
    array[count - 1]->next = NULL;

    *head = array[0];
    free(array);
}

// �ȽϺ��������ڸ���Ʊ������  
int compare_by_price(const void* a, const void* b) {
    const Movie* movie1 = *(const Movie**)a;
    const Movie* movie2 = *(const Movie**)b;
    return (movie1->price > movie2->price) - (movie1->price < movie2->price);
}

// �������г���  
void sort_movies_by_price(Movie** head) {
    int count = 0;
    Movie* current = *head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    Movie** array = (Movie**)malloc(count * sizeof(Movie*));
    current = *head;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    qsort(array, count, sizeof(Movie*), compare_by_price);

    for (int i = 0; i < count - 1; i++) {
        array[i]->next = array[i + 1];
    }
    array[count - 1]->next = NULL;

    *head = array[0];
    free(array);
}

// �ȽϺ��������ڸ�����Ʊ������  
int compare_by_remaining_ticket(const void* a, const void* b) {
    const Movie* movie1 = *(const Movie**)a;
    const Movie* movie2 = *(const Movie**)b;
    return (movie1->remaining_ticket > movie2->remaining_ticket) - (movie1->remaining_ticket < movie2->remaining_ticket);
}

// �������г���  
void sort_movies_by_remaining_ticket(Movie** head) {
    int count = 0;
    Movie* current = *head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    Movie** array = (Movie**)malloc(count * sizeof(Movie*));
    current = *head;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    qsort(array, count, sizeof(Movie*), compare_by_remaining_ticket);

    for (int i = 0; i < count - 1; i++) {
        array[i]->next = array[i + 1];
    }
    array[count - 1]->next = NULL;

    *head = array[0];
    free(array);
}



// ��ʾ���� Movie ����Ϣ  
void show_movie(const Movie* movie) {
    if (movie == NULL) return;
    printf("Session Number: %s\n", movie->session_number);
    printf("Play Theater: %s\n", movie->play_theater ? movie->play_theater->theater_name : "N/A");
    printf("Start Time: %s\n", movie->start_time);
    printf("End Time: %s\n", movie->end_time);
    printf("Remaining Tickets: %d\n", movie->remaining_ticket);
    printf("Price: %.2f\n", movie->price);
    printf("Discount: %.2f\n", movie->discount);
    printf("Theater Type: %s\n", movie->theater_type);
    printf("----------\n");
}

// ��ʾ���������� Movie ����Ϣ  
void show_all_movies(Movie* head) {
    Movie* current = head;
    while (current != NULL) {
        show_movie(current);
        current = current->next;
    }
}

