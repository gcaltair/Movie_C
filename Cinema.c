//
// Created by G on 2024/8/27.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Cinema.h"

Cinema *cinema_add(const char *name, const char *location, int id) {
    // 动态分配内存给Cinema结构体
    Cinema* cinema = (Cinema*)malloc(sizeof(Cinema));
    if (cinema == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // 动态分配内存并复制参数内容到结构体字段
    cinema->cinema_name = strdup(name);
    cinema->location = strdup(location);
    cinema->cinema_id = id;

    return cinema;
}
void cinema_show(const Cinema* cinema) {
    if (cinema == NULL) {
        printf("Cinema data is NULL.\n");
        return;
    }

    printf("Cinema Name: %s\n", cinema->cinema_name);
    printf("Location: %s\n", cinema->location);
    printf("Cinema ID: %d\n", cinema->cinema_id);
}