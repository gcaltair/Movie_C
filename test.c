//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include "User.h"
#include "admin.h"
#include "Cinema.h"
#include "Theater.h"

int main(){

}
//    Cinema* t = cinema_create("Cinema A", "Location A", 1);
////    Cinema *cinema_list= cinema_create_list(t);
////    cinema_direct_add_to_list(&cinema_list, "Cinema C", "Location C" 3),;
////    Theater *theater_temp= theater_create("theater1",20,cinema_list,"3D");
////    Theater *theater_list=theater_create_list(theater_temp);
////    theater_add_to_list(&theater_list,theater_temp);
////    cinema_show(theater_temp->cinema);
////    theater_show(cinema_list->theater);
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