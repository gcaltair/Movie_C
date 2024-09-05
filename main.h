//
// Created by G on 2024/8/31.
//

#ifndef MOVIE_C_TEST_H
#define MOVIE_C_TEST_H
#include<stdio.h>
#include <string.h>
//outer file
//#include <conio.h>
//#include <zconf.h>
#include "Object/User.h"
#include "Object/admin.h"
#include "Object/Cinema.h"
#include "Object/Theater.h"
#include "Object/Movie.h"
#include "Object/Order.h"
#include"Object/Film.h"
#include "data_process.h"
#include "Structure File/linked_list.h"
#include "Structure File/interval_tree.h"
#include "user_system.h"
User *user_now;
Admin *admin_now;

Order* order_list=NULL;
Film* film_list = NULL;
User* user_list=NULL;
Admin *admin_list=NULL;
Cinema *cinema_list=NULL;
Movie* movie_list=NULL;
Theater* theater_list=NULL;

User_hash_table *userHashTable=NULL;
Theater_hash_table* theaterHashTable=NULL;
Order_hash_table *orderHashTable=NULL;
Movie_hash_table *movieHashTable=NULL;
Film_hash_table* filmHashTable = NULL;

enum system_mode
{
    user_mode=1,
    admin_mode=2
};

static void hash_ini();
static void load_file();
static int login();
static void admin_operation();
static void admin_theater_manage();
static void admin_view_and_count_order();
static void admin_movie_manage();
static void admin_modify_self_info();
static void user_operation();
static void user_purchase_ticket();
static void user_view_and_count_movie();
Movie* search_target_film_and_choose_movie(Film* target_film);
Movie* for_user_movie_filter(Movie* new_movie_list);
Movie* for_user_movie_sort(Movie* new_movie_list);
Movie* for_admin_movie_sort(Movie* new_movie_list);
Movie* for_admin_movie_filter(Movie* new_movie_list);

int order_generate_main(User* usr, Movie* movie, Order_hash_table* hashTable);
int process_pay_main(Order_hash_table* hashTable);
void recharge_main(Order_hash_table* hashTable);
#endif //MOVIE_C_TEST_H
