//
// Created by G on 2024/8/27.
//

#include "User.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
User* User_create(const char* id, const char* name, const char* gender,
               const char* telephone, const char* password, const char* email, double balance) {
    User* user = (User*)malloc(sizeof(User));
    if (user == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // 动态分配内存并复制字符串
    user->userID = strdup(id);
    user->user_name = strdup(name);
    user->gender = strdup(gender);
    user->telephone = strdup(telephone);
    user->password = strdup(password);
    user->email = strdup(email);
    user->user_balance = balance;

    return user;
}

void user_show(const User *user) {
    if (user == NULL) {
        printf("User data is NULL.\n");
        return;
    }

    printf("User ID: %s\n", user->userID);
    printf("Name: %s\n", user->user_name);
    printf("Gender: %s\n", user->gender);
    printf("Telephone: %s\n", user->telephone);
    printf("Password: %s\n", user->password);  // 注意：实际系统中通常不会打印密码
    printf("Email: %s\n", user->email);
    printf("Balance: %.2f\n", user->user_balance);

}

void modify_personalinfo();

