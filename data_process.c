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
        const char* movie_name = fields[1];
        const char* theater_id = fields[2]; // 影厅ID
        const char* start_time = fields[3];
        const char* end_time = fields[4];
        int remaining_ticket = atoi(fields[5]);
        double price = atof(fields[6]);
        double discount = atof(fields[7]);
        const char* theater_type = fields[8];

        Movie** movie_list = ((Movie ***)context)[0];
        Movie_hash_table* movie_hash_table =  ((Movie_hash_table **)context)[1];
        Theater_hash_table *theater_table=((Theater_hash_table**)context)[2];

        // 查找对应的 Theater
        Theater* play_theater = find_theater_in_hash_table(theater_table, theater_id);

        // 创建新的 Movie 实例
        Movie* new_movie = movie_create(movie_hash_table, movie_id, movie_name, play_theater, start_time, end_time, remaining_ticket, price, discount, theater_type);

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
        Theater_hash_table *hashtable = ((Theater_hash_table **)context)[1];
        Cinema** cinema_list = ((Cinema ***) context)[2];

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
