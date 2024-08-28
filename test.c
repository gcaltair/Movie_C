//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include "User.h"
#include "admin.h"
#include "Cinema.h"
#include "movie.h"
#include "theater.h"
int main() {
    Movie* movie_list = NULL;

    // 增加一部电影
    addMovie(&movie_list);

    // 显示所有电影信息
    show_all_movies(movie_list);

    // 释放链表（此部分可以扩展以释放内存）

    return 0;