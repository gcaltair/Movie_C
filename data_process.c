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
#include"Object/Theater.h"
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
        const char* cinema_alphabet = fields[1];
        const char* location = fields[2];
        const char* cinema_id = fields[3];

        // 将 context 转换为 Cinema** 和 Theater_hash_table* 指针
        Cinema** cinema_list = ((Cinema ***)context)[0];

        // 创建新的 Cinema 实例
        Cinema* new_cinema = cinema_create(cinema_name,cinema_alphabet, location, cinema_id);


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
    int film_time = atoi(fields[5]);
    int film_rating = atoi(fields[6]);
    
    // 创建新的 Film 实例
    Film* new_film = film_create(hash_table, film_id, film_name, film_type, film_language, film_summary, film_time,film_rating);
    if (!new_film) {
        printf("Failed to create film: %s\n", film_name);
        return;
    }

    // 将 Film 添加到链表中
    film_add_to_list(film_list, new_film);
}
void write_users_to_csv(const char* filename, User** user_list) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    // 写入标题行
    fprintf(file, "userID,user_name,gender,telephone,password,email,user_balance\n");

    // 遍历用户列表，将每个用户的信息写入文件
    User* current_user = user_list;
    while (current_user != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%.2f\n",
            current_user->userID,
            current_user->user_name,
            current_user->gender,
            current_user->telephone,
            current_user->password,
            current_user->email,
            current_user->user_balance);

        current_user = current_user->next;
    }

    fclose(file);
}
void write_admins_to_csv(const char* filename, Admin* admin_list) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    // 写入标题行
    fprintf(file, "admin_id,admin_name,admin_telephone,admin_password,admin_email,cinema_id\n");

    // 遍历管理员列表，将每个管理员的信息写入文件
    Admin* current_admin = admin_list;
    while (current_admin != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n",
            current_admin->admin_id,
            current_admin->admin_name,
            current_admin->admin_telephone,
            current_admin->admin_password,
            current_admin->admin_email,
            current_admin->cinema_id);

        current_admin = current_admin->next;
    }

    fclose(file);
}
void write_cinemas_to_csv(const char* filename, Cinema* cinema_list) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    // 写入标题行
    fprintf(file, "cinema_name,cinema_alphabet,location,cinema_id\n");

    // 遍历电影院列表，将每个电影院的信息写入文件
    Cinema* current_cinema = cinema_list;
    while (current_cinema != NULL) {
        fprintf(file, "%s,%s,%s,%s\n",
            current_cinema->cinema_name,
            current_cinema->cinema_alphabet,
            current_cinema->location,
            current_cinema->cinema_id);

        current_cinema = current_cinema->next;
    }

    fclose(file);
}
void write_orders_to_csv(const char* filename, Order* order_list) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    // 写入标题行
    fprintf(file, "orderID,user_id,movie_id,seats,seat_number,status,time\n");

    // 遍历订单列表，将每个订单的信息写入文件
    Order* current_order = order_list;
    while (current_order != NULL) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%s\n",
            current_order->orderID,
            current_order->user_id,
            current_order->movie_id,
            current_order->seats,
            current_order->seat_number,
            current_order->status,
            current_order->time);

        current_order = current_order->next;
    }

    fclose(file);
}
void write_theaters_to_csv(const char* filename, Theater* theater_list) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    // 写入标题行
    fprintf(file, "theater_id,theater_name,capacity,cinema_id,theater_type\n");

    // 遍历影厅列表，将每个影厅的信息写入文件
    Theater* current_theater = theater_list;
    while (current_theater != NULL) {
        fprintf(file, "%s,%s,%d,%s,%s\n",
            current_theater->theater_id,
            current_theater->theater_name,
            current_theater->theater_capacity,
            current_theater->cinema_id,
            current_theater->theater_type);

        current_theater = current_theater->next;
    }

    fclose(file);
}
void write_films_to_csv(const char* filename, Film* film_list) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    // 写入标题行
    fprintf(file, "film_id,film_name,film_type,film_language,film_summary,film_time,film_rating\n");

    // 遍历电影列表，将每个电影的信息写入文件
    Film* current_film = film_list;
    while (current_film != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s,%d,%d\n",
            current_film->film_id,
            current_film->film_name,
            current_film->film_type,
            current_film->film_language,
            current_film->film_summary,
            current_film->film_time,
            current_film->film_rating);

        current_film = current_film->next;
    }

    fclose(file);
}
void write_movies_to_csv(const char* filename, Movie* movie_list) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }

    // 写入标题行
    fprintf(file, "movie_id,film_id,theater_id,start_time,end_time,remaining_ticket,price,discount\n");

    // 遍历电影场次列表，将每个电影场次的信息写入文件
    Movie* current_movie = movie_list;
    while (current_movie != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s,%d,%.2f,%.2f\n",
            current_movie->movie_id,
            current_movie->film_id,
            current_movie->theater_id,
            current_movie->start_time,
            current_movie->end_time,
            current_movie->remaining_ticket,
            current_movie->price,
            current_movie->discount);

        current_movie = current_movie->next;
    }

    fclose(file);
}