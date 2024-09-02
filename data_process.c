//
// Created by G on 2024/8/30.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_process.h"
#include "Object/User.h"
#include "Object/admin.h"
#include "Object/Cinema.h"
#include "Object/Movie.h"
#include "Object/Order.h"
#include"Object/Film.h"
#define MAX_LINE_LENGTH 1024

void load_data_from_csv(const char* filename, DataHandler handler, void* context) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file);  // 跳过标题行

    while (fgets(line, sizeof(line), file)) {
        // 去除换行符
        line[strcspn(line, "\n")] = '\0';

        // 使用一个数组保存解析后的字段
        char* fields[MAX_LINE_LENGTH];
        int field_count = 0;

        char* token = strtok(line, ",");
        while (token != NULL && field_count < MAX_LINE_LENGTH) {
            fields[field_count++] = token;
            token = strtok(NULL, ",");
        }

        // 调用回调函数处理数据
        handler(fields, context);
    }

    fclose(file);
}
void handle_user_data(char** fields,void* context) {
    if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6]) {
        const char* userID = fields[0];
        const char* name = fields[1];
        const char* gender = fields[2];
        const char* telephone = fields[3];
        const char* password = fields[4];
        const char* email = fields[5];
        double balance = atof(fields[6]);
        User_hash_table *hashtable = ((User_hash_table **)context)[0];
        User** user_list = ((User ***) context)[1]; //不加前面的(User**)编译器会警告，但是能正常运行
        User* new_user = user_create((User_hash_table*)hashtable, userID, name, gender, telephone, password, email, balance);
        user_add_to_list(user_list, new_user);
    }
}
void handle_admin_data(char** fields, void* context) {
    if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4]) {
        const char* admin_id = fields[0];
        const char* admin_name = fields[1];
        const char* admin_telephone = fields[2];
        const char* admin_password = fields[3];
        const char* admin_email = fields[4];
        const char* cinema_id=fields[5];
        // 将 context 转换为 Admin** 指针
        Cinema* head = ((Cinema**)context)[0];
        Admin** admin_list = ((Admin***)context)[1];

        // 创建新的 Admin 实例
        Admin* new_admin = Admin_create(admin_id, admin_name, admin_telephone, admin_password, admin_email,
                                        cinema_find_by_id(head,cinema_id) ,cinema_id);

        // 将新的 Admin 实例添加到链表中
        admin_add_to_list(admin_list, new_admin);
    }
}
void handle_cinema_data(char** fields, void* context) {
    if (fields[0] && fields[1] && fields[2]) {
        const char* cinema_name = fields[0];
        const char* location = fields[1];
        const char* cinema_id = fields[2];

        // 将 context 转换为 Cinema** 和 Theater_hash_table* 指针
        Cinema** cinema_list = ((Cinema ***)context)[0];

        // 创建新的 Cinema 实例
        Cinema* new_cinema = cinema_create(cinema_name, location, (char*)cinema_id);


        // 将新创建的 Cinema 添加到链表中
        cinema_add_to_list(cinema_list, new_cinema);
    }
    else printf("cinema data error!");
}
void handle_movie_data(char** fields, void* context) {
    if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6] && fields[7] && fields[8]) {
        const char* movie_id = fields[0];
        const char* film_id = fields[1];
        const char* theater_id = fields[2]; // 影厅ID
        const char* start_time = fields[3];
        const char* end_time = fields[4];
        int remaining_ticket = atoi(fields[5]);
        double price = atof(fields[6]);
        double discount = atof(fields[7]);
        const char* theater_type = fields[8];

        Movie** movie_list = ((Movie ***)context)[0];
        Movie_hash_table* movie_hash_table =  ((Movie_hash_table **)context)[1];
        Theater_hash_table* theater_table = ((Theater_hash_table**)context)[2];
        Film_hash_table * film_table = ((Film_hash_table**)context)[3];

        // 查找对应的 Theater
        Theater* play_theater = find_theater_in_hash_table(theater_table, theater_id);
        Film* released_film = find_film_in_hash_table_by_id(film_table, film_id);
        
        // 创建新的 Movie 实例
        Movie* new_movie = movie_create(movie_hash_table, movie_id, film_id,released_film, theater_id, play_theater, start_time, end_time, remaining_ticket, price, discount);

        // 将新创建的 Movie 添加到链表中
        movie_add_to_list(movie_list, new_movie);
    }
}
void handle_theater_data(char** fields, void* context) {
    if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5]) {
        const char* theater_id = fields[0];
        const char* name = fields[1];
        int capacity = atoi(fields[2]);
        const char* cinema_id = fields[3];
        const char* type = fields[4];

        Theater** theater_list = ((Theater ***) context)[0];
        Cinema** cinema_list = ((Cinema ***) context)[1];
        Theater_hash_table* hashtable = ((Theater_hash_table**)context)[2];

        // 查找 Cinema 是否存在
        Cinema* cinema = cinema_find_by_id(*cinema_list, cinema_id);
        if (cinema == NULL) {
            printf("Cinema with ID %s not found for Theater %s.\n", cinema_id, theater_id);
            return;
        }

        // 创建 Theater 并插入链表和哈希表
        Theater* new_theater = theater_create(hashtable, theater_id, name, capacity, cinema, cinema_id, type);
        theater_add_to_list(theater_list, new_theater);
    }
}
void handle_order_data(char** fields, void* context) {
    if (fields[0] && fields[1] && fields[2] && fields[3] && fields[4] && fields[5] && fields[6]) {
        const char* orderID = fields[0];
        const char* user_id = fields[1];
        const char* movie_id = fields[2];
        const char* seats = fields[3];
        int seat_number = atoi(fields[4]);
        int status = atoi(fields[5]);
        const char* time = fields[6];

        // 从上下文中提取哈希表和链表
        Order_hash_table* order_hash_table = ((Order_hash_table**)context)[0];
        User_hash_table* user_hash_table = ((User_hash_table**)context)[1];
        Movie_hash_table* movie_hash_table = ((Movie_hash_table**)context)[2];
        Order** order_list = ((Order***)context)[3]; // 假设上下文中包含订单链表
        // 查找相关的 User、Movie、Theater 和 Cinema
        User* user = find_user_in_hash_table(user_hash_table, user_id);
        Movie* movie = find_movie_in_hash_table(movie_hash_table, movie_id);
        Theater* theater = movie->theater;
        Cinema* cinema;
        if (theater) cinema = theater->cinema;
        else cinema = NULL;


        Order* new_order = order_create(order_hash_table, orderID,
                                        user, user_id, movie, movie_id, theater, cinema, seats, seat_number, status, time);
        order_add_to_list(order_list, new_order);

        }
}
void handle_film_data(char** fields, void* context) {
    // 从 context 中获取所需的 Film 列表和哈希表
    Film** film_list = ((Film***)context)[0];
    Film_hash_table* hash_table = ((Film_hash_table**)context)[1];

    // 从 fields 中提取数据
    const char* film_id = fields[0];
    const char* film_name = fields[1];
    const char* film_type = fields[2];
    const char* film_language = fields[3];
    const char* film_summary = fields[4];
    int film_rating = atoi(fields[5]);

    // 创建新的 Film 实例
    Film* new_film = film_create(hash_table, film_id, film_name, film_type, film_language, film_summary, film_rating);
    if (!new_film) {
        printf("Failed to create film: %s\n", film_name);
        return;
    }

    // 将 Film 添加到链表中
    film_add_to_list(film_list, new_film);
}