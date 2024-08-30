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