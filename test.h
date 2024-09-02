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
#endif //MOVIE_C_TEST_H
