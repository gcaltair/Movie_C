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

    // ����һ����Ӱ
    addMovie(&movie_list);

    // ��ʾ���е�Ӱ��Ϣ
    show_all_movies(movie_list);

    // �ͷ������˲��ֿ�����չ���ͷ��ڴ棩

    return 0;