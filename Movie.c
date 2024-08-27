
//created by y on 2024.8.27

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

typedef struct {
    char* session_number;
    char* movie_name;
    char* affiliated_cinema;
    char* play_theater;
    char* start_time;
    char* end_time;
    int remaining_ticket;   
    double price;            
    double discount;       
    char* theater_type;
} Movie;

Movie* Movie_add() {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (!newMovie) {
        printf("Memory allocation for Movie struct failed!\n");
        return NULL;
    }

    // 动态分配和初始化各个字符串字段  
    newMovie->session_number = (char*)malloc(50 * sizeof(char));
    newMovie->movie_name = (char*)malloc(50 * sizeof(char));
    newMovie->affiliated_cinema = (char*)malloc(10 * sizeof(char));
    newMovie->play_theater = (char*)malloc(20 * sizeof(char));
    newMovie->start_time = (char*)malloc(50 * sizeof(char));
    newMovie->end_time = (char*)malloc(50 * sizeof(char));
    newMovie->theater_type = (char*)malloc(50 * sizeof(char));

    if (!newMovie->session_number || !newMovie->movie_name || !newMovie->affiliated_cinema ||
        !newMovie->play_theater || !newMovie->start_time || !newMovie->end_time || !newMovie->theater_type) {
        printf("Memory allocation for fields failed!\n");
        // 释放已分配的内存  
        free(newMovie->session_number);
        free(newMovie->movie_name);
        free(newMovie->affiliated_cinema);
        free(newMovie->play_theater);
        free(newMovie->start_time);
        free(newMovie->end_time);
        free(newMovie->theater_type);
        free(newMovie);
        return NULL;
    }

    // 获取用户输入并将其存储在结构体中  
    printf("Enter session number: ");
    scanf("%49s", newMovie->session_number);

    printf("Enter movie name: ");
    scanf("%49s", newMovie->movie_name);

    printf("Enter affiliated_cinema: ");
    scanf("%9s", newMovie->affiliated_cinema);

    printf("Enter play_theater: ");
    scanf("%19s", newMovie->play_theater);

    printf("Enter start time: ");
    scanf("%49s", newMovie->start_time);

    printf("Enter end time: ");
    scanf("%49s", newMovie->end_time);

    printf("Enter remaining ticket: ");
    scanf("%d", &newMovie->remaining_ticket);   

    printf("Enter price: ");
    scanf("%lf", &newMovie->price);

    printf("Enter discount: ");
    scanf("%lf", &newMovie->discount);

    printf("Enter theater_type: ");
    scanf("%49s", newMovie->theater_type);

    return newMovie;
}