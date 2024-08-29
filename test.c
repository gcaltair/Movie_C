//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include "User.h"
#include "admin.h"
#include "Cinema.h"
#include "Theater.h"
#include "Movie.h"
#include "Order.h"
int main(){
    User_hash_table *userHashTable=user_hash_table_create();
    Theater_hash_table* theaterHashTable=theater_hash_table_create();
    Order_hash_table *orderHashTable=order_hash_table_create();

    User* head=NULL;
    user_add_to_list(&head,user_create(userHashTable,"114514","gc","man","114514","114514","114514@homo.com",0.0));
    User* temp=user_create(userHashTable,"123456","cg","unknow","22222","114514","114514@homo.com",0.0);
    user_add_to_list(&head,temp);
    //user_show(head);
    //user_show_all(head);
    //user_show(find_user_in_hash_table(userHashTable,"114514"));


    Cinema* t = cinema_create("Cinema A", "Location A", "1");
    Theater *theater_head= theater_create(theaterHashTable,"1","1ºÅÌü",100,t,"1","3D");
    Movie* movie= movie_create("114514",theater_head,"12-20:30","12-22:30",20,30,1,"3D");
    Order *order_head= order_create(orderHashTable,"1", find_user_in_hash_table(userHashTable,"114514"),"114514",movie,1,
                               find_theater_in_hash_table(theaterHashTable,"1"),find_theater_in_hash_table(theaterHashTable,"1")->cinema,1,0,"12:10");
    order_add_to_list(&order_head, order_create(orderHashTable,"2", find_user_in_hash_table(userHashTable,"114514"),"114514",movie,1,
                                                find_theater_in_hash_table(theaterHashTable,"1"),
                                                find_theater_in_hash_table(theaterHashTable,"1")->cinema,2,0,"12:10"));

    order_add_to_list(&order_head, order_create(orderHashTable, "4", find_user_in_hash_table(userHashTable, "114514"), "114514", movie, 1,
                                                find_theater_in_hash_table(theaterHashTable, "1"),
                                                find_theater_in_hash_table(theaterHashTable, "1")->cinema, 1, 0, "12:10"));

    order_add_to_list(&order_head, order_create(orderHashTable, "5", find_user_in_hash_table(userHashTable, "114514"), "114514", movie, 1,
                                                find_theater_in_hash_table(theaterHashTable, "1"),
                                                find_theater_in_hash_table(theaterHashTable, "1")->cinema, 1, 0, "12:10"));
    order_show(find_order_in_hash_table(orderHashTable,"5"));
}
//    User* head= user_create("114514","gc","man","114514","114514","114514@homo.com",0.0);
//    User* temp=user_create("123456","cg","unknow","22222","114514","114514@homo.com",0.0);
//    user_add_to_list(&head,temp);
//    user_show_all(head);
//    user_show(user_find_by_id(head,"114514"));

/* user hash test
  User_hash_table* userHashTable= user_hash_table_create();
    User* head=NULL;
    user_add_to_list(&head,user_create(userHashTable,"114514","gc","man","114514","114514","114514@homo.com",0.0));


    User* temp=user_create(userHashTable,"123456","cg","unknow","22222","114514","114514@homo.com",0.0);

    user_add_to_list(&head,temp);
    //user_show(head);
    user_show_all(head);
    user_show(find_user_in_hash_table(userHashTable,"114514"));
 * */

/*Theater hash test
 * Cinema* t = cinema_create("Cinema A", "Location A", "1");
    Theater_hash_table* theaterHashTable=theater_hash_table_create();
    Theater *theater_head= theater_create(theaterHashTable,"1","1ºÅÌü",100,t,"1","3D");
    theater_add_to_list(&theater_head, theater_create(theaterHashTable,"2","2ºÅÌü",20,t,"1","4D"));
    theater_show(find_theater_in_hash_table(theaterHashTable,"1"));

 */