//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include <string.h>
#include "Object/User.h"
#include "Object/admin.h"
#include "Object/Cinema.h"
#include "Object/Theater.h"
#include "Object/Movie.h"
#include "Object/Order.h"
#include "data_process.h"
#include "Structure File/linked_list.h"

Order* order_list=NULL;
User* user_list=NULL;
Admin *admin_list=NULL;
Cinema *cinema_list=NULL;
Movie* movie_list=NULL;
Theater* theater_list=NULL;

User_hash_table *userHashTable=NULL;
Theater_hash_table* theaterHashTable=NULL;
Order_hash_table *orderHashTable=NULL;
Movie_hash_table *movieHashTable=NULL;
static void hash_ini();
static void load_file();
int main(){
    hash_ini();
    load_file();
    string_node_show_all(find_user_in_hash_table(userHashTable,"U001")->my_order);
}

static void hash_ini()
{
    userHashTable=user_hash_table_create();
    theaterHashTable=theater_hash_table_create();
    orderHashTable=order_hash_table_create();
    movieHashTable=movie_hash_table_create();
}
static void load_file()
{
    void* context1[]={userHashTable,&user_list};
    load_data_from_csv("D:\\Movie_C\\Data\\users.csv",handle_user_data,context1);
    void* context2[]= {&cinema_list};
    load_data_from_csv("D:\\Movie_C\\Data\\cinemas.csv",handle_cinema_data,context2);
    void *context3[]={cinema_list,&admin_list};
    load_data_from_csv("D:\\Movie_C\\Data\\admins.csv",handle_admin_data,context3);
    void* context4[] = { &theater_list,&cinema_list,theaterHashTable };
    load_data_from_csv("D:\\Movie_C\\Data\\theaters.csv", handle_theater_data, context4);
    void *context5[]={&movie_list,movieHashTable,theaterHashTable};
    load_data_from_csv("D:\\Movie_C\\Data\\movies.csv",handle_movie_data,context5);
    
    void* context6[] = {
            orderHashTable,   // 订单哈希表
            userHashTable,    // 用户哈希表
            movieHashTable,   // 电影哈希表
            &order_list,      // 订单链表
    };
    load_data_from_csv("D:\\Movie_C\\Data\\order.csv",handle_order_data,context6);

}
