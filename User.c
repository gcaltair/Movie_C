//
// Created by G on 2024/8/27.
//

#include "User.h"
bool login()
{
    return true;
}
User* User_add() {
    // 动态分配内存用于保存一个 User 结构体
    User* newUser = (User*)malloc(sizeof(User));
    if (newUser == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // 动态分配和初始化各个字段
    newUser->userID = (char*)malloc(50 * sizeof(char));
    newUser->user_name = (char*)malloc(50 * sizeof(char));
    newUser->gender = (char*)malloc(10 * sizeof(char));
    newUser->telephone = (char*)malloc(20 * sizeof(char));
    newUser->password = (char*)malloc(50 * sizeof(char));
    newUser->email = (char*)malloc(50 * sizeof(char));

    if (!newUser->userID || !newUser->user_name || !newUser->gender ||
        !newUser->telephone || !newUser->password || !newUser->email) {
        printf("Memory allocation for fields failed!\n");
        free(newUser); // 释放分配的内存
        return NULL;
    }

    // 获取用户输入并将其存储在结构体中
    printf("Enter User ID: ");
    scanf("%49s", newUser->userID);

    printf("Enter User Name: ");
    scanf("%49s", newUser->user_name);

    printf("Enter Gender: ");
    scanf("%9s", newUser->gender);

    printf("Enter Telephone: ");
    scanf("%19s", newUser->telephone);

    printf("Enter Password: ");
    scanf("%49s", newUser->password);

    printf("Enter Email: ");
    scanf("%49s", newUser->email);

    printf("Enter User Balance: ");
    scanf("%lf", &newUser->user_balance);

    return newUser;
}
void modify_personalinfo(); //修改用户信息

