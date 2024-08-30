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



User* user_list=NULL;
Admin *admin_list=NULL;
Cinema *cinema_list=NULL;
User_hash_table *userHashTable=NULL;
Theater_hash_table* theaterHashTable=NULL;
Order_hash_table *orderHashTable=NULL;
static void hash_ini();
int main(){
    hash_ini();
    void* context[]={userHashTable,&user_list};
    load_data_from_csv("D:\\Movie_C\\Data\\users.csv",handle_user_data,context);
    context[0]=&cinema_list;
    load_data_from_csv("D:\\Movie_C\\Data\\cinemas.csv",handle_cinema_data,context);
    context[0]=cinema_list;context[1]=&admin_list;
    load_data_from_csv("D:\\Movie_C\\Data\\admins.csv",handle_admin_data,context);
    admin_show_all(admin_list);

}

static void hash_ini()
{
    userHashTable=user_hash_table_create();
    theaterHashTable=theater_hash_table_create();
    orderHashTable=order_hash_table_create();
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
    Theater *theater_head= theater_create(theaterHashTable,"1","1����",100,t,"1","3D");
    theater_add_to_list(&theater_head, theater_create(theaterHashTable,"2","2����",20,t,"1","4D"));
    theater_show(find_theater_in_hash_table(theaterHashTable,"1"));

 */

/*Order hash test
 User* head=NULL;
    user_add_to_list(&head,user_create(userHashTable,"114514","gc","man","114514","114514","114514@homo.com",0.0));
    User* temp=user_create(userHashTable,"123456","cg","unknow","22222","114514","114514@homo.com",0.0);
    user_add_to_list(&head,temp);
    //user_show(head);
    //user_show_all(head);
    //user_show(find_user_in_hash_table(userHashTable,"114514"));


    Cinema* t = cinema_create("Cinema A", "Location A", "1");
    Theater *theater_head= theater_create(theaterHashTable,"1","1����",100,t,"1","3D");
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
 */