//
// Created by Y on 2024/8/27.
//

#include "admin.h"
bool login()
{
    return true;
}
User* Admin_add() {
    // 动态分配内存用于保存一个 User 结构体
    Admin* newAdmin = (Admin*)malloc(sizeof(admin));
    if (newAdmin == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // 动态分配和初始化各个字段
    newAdmin->admin_ID = (char*)malloc(50 * sizeof(char));
    newAdmin->admin_name = (char*)malloc(50 * sizeof(char));
    newAdmin->admin_password = (char*)malloc(10 * sizeof(char));
    newAdmin->admin_telephone = (char*)malloc(20 * sizeof(char));
    newAdmin->admin_email = (char*)malloc(50 * sizeof(char));
    newAdmin->admin_cinema; = (char*)malloc(50 * sizeof(char));

    if (!newAdmin->admin_ID || !newAdmin->admin_name || !newAdmin->admin_password ||
        !newAdmin->admin_telephone || !newAdmin->admin_email || !newAdmin->admin_cinema) {
        printf("Memory allocation for fields failed!\n");
        free(newAdmin); // 释放分配的内存
        return NULL;
    }

    // 获取用户输入并将其存储在结构体中
    printf("Enter Admin ID: ");
    scanf("%49s", newAdmin->admin_ID

    printf("Enter Admin Name: ");
    scanf("%49s", newAdmin->admin_name);

    printf("Enter Admin Password: ");
    scanf("%9s", newAdmin->admin_password);

    printf("Enter Telephone: ");
    scanf("%19s", newAdmin->admin_telephone);

    printf("Enter email: ");
    scanf("%49s", newAdmin->admin_email);

    printf("Enter cinema: ");
    scanf("%49s", newAdmin->admin_cinema);

    return newAdmin;
}
void modify_personalinfo(); //修改用户信息