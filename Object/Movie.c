#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Movie.h"
#include "Cinema.h"
#include "Order.h"
#include "../hash.txt"
#include "../Structure File/linked_list.h"
#include"../Structure File/interval_tree.h"
#include"Film.h"
// �����µ� Movie �ڵ�  
Movie* movie_create(Movie_hash_table *movieHashTable,const char* movie_id,const char* film_id,Film* film,const char* theater_id,Theater* theater, const char* start_time, const char* end_time,
    int remaining_ticket, double price, double discount) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (!newMovie) {
        printf("�ڴ����ʧ��!\n");
        return NULL;
    }
    if (!theater) { printf("Movie %s's Theater is null\n",movie_id); newMovie->theater = NULL;}
    else newMovie->theater = theater;
    newMovie->film = film;
    newMovie->movie_id= strdup(movie_id); // ʹ�� strdup ���ڴ����͸���
    newMovie->film_id = strdup(film_id);
    newMovie->theater_id = strdup(theater_id);
    newMovie->theater = theater;
    newMovie->start_time = strdup(start_time);
    newMovie->start_min = datetime_to_minutes(start_time);
    newMovie->end_time = strdup(end_time);
    newMovie->end_min = datetime_to_minutes(end_time);
    newMovie->remaining_ticket = remaining_ticket;
    newMovie->price = price;
    newMovie->discount = discount;
    newMovie->next = NULL;
    newMovie->hash_next = NULL;
    newMovie->seat_map = seat_map_generation();
    insert_movie_to_hash_table(movieHashTable,newMovie);//�����ϣ��

    string_direct_add_to_list(&(newMovie->theater->my_movie),newMovie->movie_id);//��ӵ�Ӱ��
    //printf("theater id:%s movie_id:%s\n", theater->theater_id, movie_id);
    int_direct_add_to_list(&(theater->cinema->peak_time), newMovie->start_min);//�����ֹʱ�䵽peaktime
    int_direct_add_to_list(&(theater->cinema->peak_time), newMovie->end_min);

    theater->time_line = insert_interval(theater->time_line, newMovie->start_min, newMovie->end_min);//����timeLineʱ����

    string_direct_add_to_list(&(film->playing_movie), newMovie->movie_id);

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
    printf("���� ID: %s\n",movie->movie_id);
    printf("��Ӱ ID: %s\n", movie->film_id);
    printf("��ӰԺ ID: %s\n", movie->theater_id);
    printf("��ʼʱ��: %s\n", movie->start_time);
    printf("����ʱ��: %s\n", movie->end_time);
    printf("��Ʊ��: %d\n", movie->remaining_ticket);
    printf("�۸�: %.2f\n", movie->price);
    printf("�ۿ�: %.2f\n", movie->discount);
    printf("----------\n");
}

// ��ʾ���������� Movie ����Ϣ  
void movie_show_all(Movie* head) {
    Movie* movie = head;
    while (movie != NULL) {
        movie_show(movie);
        movie = movie->next;
    }
}




// ������ϣ��
Movie_hash_table* movie_hash_table_create() {
    Movie_hash_table* ht = (Movie_hash_table*)malloc(sizeof(Movie_hash_table));
    if (!ht) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    movie_hash_table_init(ht);
    return ht;
}

// ��ʼ����ϣ��
void movie_hash_table_init(Movie_hash_table* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    ht->count = 0;
}

// ���� Movie ����ϣ��
void insert_movie_to_hash_table(Movie_hash_table* ht, Movie* movie) {
    unsigned int index = hash(movie->movie_id, strlen(movie->movie_id), 0x9747b28c); // ʹ��MurmurHash2��������
    movie->hash_next = ht->table[index];  // ����ǰ�Ĺ�ϣ����������Ԫ�ط����µ�Ӱ�ĺ���
    ht->table[index] = movie;// ���µ�Ӱ���������ͷ��
    ht->count++;
}

// �ڹ�ϣ���в��� Movie��ͨ�� movie_id ����
Movie* find_movie_in_hash_table(Movie_hash_table* ht, const char* movie_id) {
    unsigned int index = hash(movie_id, strlen(movie_id), 0x9747b28c);
    Movie* movie = ht->table[index];
    while (movie) {
        if (strcmp(movie->movie_id, movie_id) == 0) {
            return movie;  // �ҵ���Ӱ������ָ��
        }
        movie = movie->hash_next;  // �������������е���һ����Ӱ
    }
    return NULL;  // ���δ�ҵ�������NULL
}
Movie *movie_copy_info(Movie* movie)
{
    /*if (!movie) {
        printf("movie is null"); return;
    }*/
    Movie* new_movie = (Movie*)malloc(sizeof(Movie));
    if (!new_movie) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // ���Ƶ�ǰ��Ӱ����Ϣ���½ڵ�
    new_movie->movie_id = strdup(movie->movie_id);
    new_movie->film_id = strdup(movie->film_id);
    new_movie->film = movie->film;
    new_movie->theater_id = strdup(movie->theater_id);
    new_movie->theater = movie->theater;
    new_movie->start_time = strdup(movie->start_time);
    new_movie->end_time = strdup(movie->end_time);
    new_movie->remaining_ticket = movie->remaining_ticket;
    new_movie->price = movie->price;
    new_movie->discount = movie->discount;
    new_movie->next = NULL;
    new_movie->hash_next=NULL;
    new_movie->seat_map = movie->seat_map;
    return new_movie;
}
//1.������(���򣩣�2.�۸�(����)��3.��������(����)��4.��ʼʱ��(����)��5.ʣ��Ʊ��(����)
Movie* movie_operation_sort(Movie* head, int mode)
{
    Movie* new_head = NULL;
    switch (mode)
    {
    case 1:
        new_head=movie_sort(head, compare_movies_by_occupancy_rate);
        break;
    case 2:
        new_head = movie_sort(head, compare_movies_by_price);
        break;
    case 3:
        new_head = movie_sort(head, compare_movies_by_income);
        break;
    case 4:
        new_head = movie_sort(head, compare_movies_by_start_time);
        break;
    case 5:
        new_head = movie_sort(head, compare_movies_by_remaining_ticket);
        break;
    default:
        return head;
    }
    return new_head;
}
//1.ʱ��Σ�2.�ѷ�ӳ��3.δ��ӳ��4.�������ڣ�5.ӰƬ���ͣ�6.��ӰԺid
Movie* movie_operation_filter(Movie* head, int mode, void* filter_param) {
    Movie* new_head = NULL;

    switch (mode) {
    case 1:  // ����ʱ���
    
        char** time_period = (char**)filter_param;  // filter_param should be a char* array with two elements: [start_time, end_time]
        new_head = movie_filter_by_time_period(head, time_period[0], time_period[1]);
        break;
    case 2:  // �����ѷ�ӳ
        new_head = movie_filter_by_played(head);
        break;
    case 3:  // ����δ��ӳ
        new_head = movie_filter_by_not_played(head);
        break;
    case 4:  // ���˵�������
        new_head = movie_filter_by_current_date(head);  // filter_param should be a const char* representing the date
        break;
    case 5:  // ����ӰƬ����
        new_head = movie_filter_by_film_type(head, (const char*)filter_param);  // filter_param should be a const char* representing the film type
        break;
    case 6:  // ���˵�ӰԺID
        new_head = movie_filter_by_cinema_id((char*)filter_param, head);  
        break;
    default:
        return head;  // ��� mode ���� 1-6 ֮�䣬ֱ�ӷ���ԭ����
    }

    return new_head;
}

// ���ݷ�ӳ�������͹���
Movie* movie_filter_by_film_type(Movie* head, const char* film_type) {
    Movie* result_head = NULL;  // ��������ͷ�ڵ�
    Movie* movie = head;

    // ����ԭ����
    while (movie != NULL) {
        // �����Ӱ�� movie_type ��������
        if (strcmp(movie->film->film_type, film_type) == 0) {
            // ����һ���½ڵ㣬������ӵ��������
            Movie* new_movie = movie_copy_info(movie);

            // ���½ڵ���ӵ��������
            movie_add_to_list(&result_head,new_movie);
        }
        movie = movie->next;  // ��������ԭ�����е���һ����Ӱ
    }
    return result_head;  // ���ؽ�������ͷ�ڵ�
}

Movie* movie_list_create_by_film(Film* film,Movie_hash_table* movie_hash_table)
{
    Movie* new_head = NULL;
    Linked_string_list* string_head = film->playing_movie; //string_head����

    while (string_head)
    {
        Movie* find = find_movie_in_hash_table(movie_hash_table, string_head->id);
        Movie* target = movie_copy_info(find);
        movie_add_to_list(&new_head, target);
        string_head = string_head->next;
    }
    return new_head;
}
Movie* movie_list_create_by_cinema(Cinema* cinema, Theater_hash_table* theater_hash_table, Movie_hash_table* movie_hash_table)
{   
    Movie* new_head = NULL;
    Linked_string_list* head_theater = cinema->my_theater;
    while (head_theater)
    {
        Theater* theater = find_theater_in_hash_table(theater_hash_table, head_theater->id);
        Linked_string_list* head_movie = theater->my_movie;
        while (head_movie)
        {
            Movie* movie_find = find_movie_in_hash_table(movie_hash_table, head_movie->id);
            if (!movie_find) { printf("movie id %s movie list create failed",head_movie->id); _sleep(10000); }
            Movie* new_movie = movie_copy_info(movie_find);
            movie_add_to_list(&new_head, new_movie);
            head_movie = head_movie->next;
        }
        head_theater = head_theater->next;
    }
    return new_head;
}
Movie* movie_filter_by_cinema_id(char* id, Movie* head)
{
    Movie* new_head = NULL;
    while (head)
    {
        if (!strcmp(head->theater->cinema_id, id))
        {
            movie_add_to_list(&new_head, movie_copy_info(head));
        }
        head = head->next;
    }
    return new_head;
}
Movie* movie_filter_by_cinema_name(char* name, Movie* head)
{
    Movie* new_head = NULL;
    while (head)
    {
        if (!strcmp(head->theater->cinema->cinema_name, name))
        {
            movie_add_to_list(&new_head, movie_copy_info(head));
        }
        head = head->next;
    }
    return new_head;
}

Movie* movie_filter_by_film_language(char* language, Movie* head)
{
    Movie* new_head = NULL;
    while (head)
    {
        if (!strcmp(head->film->film_language,language))
        {
            movie_add_to_list(&new_head, movie_copy_info(head));
        }
        head = head->next;
    }
    return new_head;
}
Movie* movie_filter_by_theater_type(char* type, Movie* head)
{
    Movie* new_head = NULL;
    while (head)
    {
        if (!strcmp(head->theater->theater_type, type))
        {
            movie_add_to_list(&new_head, movie_copy_info(head));
        }
        head = head->next;
    }
    return new_head;
}
Movie* movie_filter_by_time_period(Movie* head, char* start_time, char* end_time)
{
    Movie* new_head = NULL;
    while (head)
    {
        if ((strcmp(head->start_time, start_time)>=0)&& (strcmp(end_time, head->start_time)>=0))
        {
            movie_add_to_list(&new_head, movie_copy_info(head));
            
        }
        head = head->next;
    }
    return new_head;
}
Movie* movie_filter_by_not_played(Movie* head)
{
    char* time = get_current_time();
    Movie* new_head = NULL;
    while (head)
    {
        if (strcmp(head->start_time,time)>=0)
        {
            movie_add_to_list(&new_head, movie_copy_info(head));
        }
        head = head->next;
    }
    return new_head;
}
Movie* movie_filter_by_played(Movie* head)
{
    char* time = get_current_time();
    Movie* new_head = NULL;
    while (head)
    {
        if (strcmp(time, head->end_time)>=0)
        {
            movie_add_to_list(&new_head, movie_copy_info(head));
        }
        head = head->next;
    }
    return new_head;
}
Movie* movie_filter_by_film_name(char* name, Movie* head)
{
    Movie* new_head = NULL;
    while (head)
    {
        if (!strcmp(head->film->film_name, name))
        {
            movie_add_to_list(&new_head, movie_copy_info(head));
        }
        head = head->next;
    }
    return new_head;
}

int compare_movies_by_income(const void* a, const void* b)
{
    Movie* movie1 = *(Movie* const*)a;
    Movie* movie2 = *(Movie* const*)b;
    double income1 = (movie1->theater->theater_capacity - movie1->remaining_ticket) * (movie1->discount);
    double income2 = (movie2->theater->theater_capacity - movie1->remaining_ticket) * (movie2->discount);
    return income1 < income2 ? 1 : -1;
}



//����������
int compare_movies_by_occupancy_rate(const void* a, const void* b)
{
    Movie* movie1 = *(Movie* const*)a;
    Movie* movie2 = *(Movie* const*)b;
    double rate1 = (1 - (movie1->remaining_ticket)*(1.0)/ (movie1->theater->theater_capacity));
    double rate2= (1 - (movie2->remaining_ticket)*(1.0) / (movie2->theater->theater_capacity));
    if (rate1 < rate2) return 1;
    return -1;
}
//����
int compare_movies_by_price(const void* a, const void* b)
{
    Movie* movie1 = *(Movie* const*)a;
    Movie* movie2 = *(Movie* const*)b;
    if (movie1->price < movie2->price) return -1;
    return 1;
}

//����
int compare_movies_by_remaining_ticket(const void* a, const void* b)
{
    Movie* movie1 = *(Movie* const*)a;
    Movie* movie2 = *(Movie* const*)b;
    if (movie1->remaining_ticket < movie2->remaining_ticket) return -1;
    return 1;
}
//����     
int compare_movies_by_start_time(const void* a, const void* b) {
    Movie* movie1 = *(Movie* const*)a;
    Movie* movie2 = *(Movie* const*)b;
    return strcmp(movie1->start_time, movie2->start_time);
}

Movie* movie_sort(Movie* head,int* compare(void*,void*)) {
    Movie** movies = NULL;
    int count = 0;

    // ���ȣ����������еĵ�Ӱ����  
    Movie* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // ����һ���������洢���е�Ӱ��ָ��  
    movies = (Movie**)malloc(count * sizeof(Movie*));
    if (!movies) {
        printf("�ڴ����ʧ��!\n");
        return NULL;
    }

    // �����е�Ӱ��ָ��洢��������  
    int i = 0;
    current = head;
    while (current != NULL) {
        movies[i++] = current;
        current = current->next;
    }

    // ʹ��qsort�������������  
    qsort(movies, count, sizeof(Movie*), compare);

    // ���¹�������  
    Movie* new_head = movies[0];
    for (i = 1; i < count; i++) {
        movies[i - 1]->next = movies[i];
    }
    movies[count - 1]->next = NULL;

    // �ͷ������ڴ�  
    free(movies);

    return new_head;
}
// Helper function to compare the date part of start_time with the input date
int is_same_date(const char* start_time, const char* input_date) {
    char movie_date[11];
    strncpy(movie_date, start_time, 10);  // Extract the date part (YYYY-MM-DD) from start_time
    movie_date[10] = '\0';
    return strcmp(movie_date, input_date) == 0;
}

// Function to filter movies by date
Movie* movie_filter_by_current_date( Movie* head) {
    Movie* filtered_head = NULL;
    Movie* current = head;  
    char* current_day=get_current_day();
    while (current != NULL) {
        if (is_same_date(current->start_time, current_day)) {
            Movie* new_movie = movie_copy_info(current);
            movie_add_to_list(&filtered_head, new_movie);
        }
        current = current->next;
    }

    return filtered_head;
}
int my_abs(int a, int b)
{return a > b ? a - b : b - a;}

int is_avoid_flow(Cinema* cinema, int start_min, int end_min)
{
    int count = 0;
    Linked_int_list* head = cinema->peak_time;
    
    while (head)
    {
        if ((
            (head->value, start_min)<=5)||(my_abs(head->value, end_min) <=5)) count++;
        head = head->next;
    }
    if (!count) return 0;
    return (count + 1) / 2;
}
double caculate_movie_income(Movie* head)
{
    if (!head)
    {
        printf("���ݲ�����!");
        return 0;
    }
    double res = 0;
    while (head)
    {
        res += head->price * head->discount*(head->theater->theater_capacity-head->remaining_ticket);
        head = head->next;
    }
    return res;
}
int datetime_to_minutes(const char* datetime) 
{
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
    if (sscanf(datetime, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) == 6) {
        return hour * 60 + minute;
    }
    else {
        // �������ʧ�ܣ�����һ�������־
        return -1;
    }
}
void movie_list_free(Movie* head) {
    Movie* temp = head;
    if (!head) return;
    while (head != NULL) {
        temp = head;
        head = head->next;

        // �ͷ� movie_id, film_id, theater_id, start_time, end_time
        if (temp->movie_id) free(temp->movie_id);
        if (temp->film_id) free(temp->film_id);
        if (temp->theater_id) free(temp->theater_id);
        if (temp->start_time) free(temp->start_time);
        if (temp->end_time) free(temp->end_time);

        // �ͷ� Movie �ṹ�屾��
        free(temp);
        temp = NULL;
    }
}

