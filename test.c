//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include "User.h"
#include "admin.h"
#include "Cinema.h"
#include "Theater.h"

int main(){

//    Cinema* t = cinema_create("Cinema A", "Location A", 1);
//    Cinema *cinema_list= cinema_create_list(t);
//    cinema_direct_add_to_list(&cinema_list, "Cinema C", "Location C" 3),;
//    Theater *theater_temp= theater_create("theater1",20,cinema_list,"3D");
//    Theater *theater_list=theater_create_list(theater_temp);
//    theater_add_to_list(&theater_list,theater_temp);
//    cinema_show(theater_temp->cinema);
//    theater_show(cinema_list->theater);
    User* head= user_create("114514","gc","man","114514","114514","114514@homo.com",0.0);
    User* temp=user_create("123456","cg","unknow","22222","114514","114514@homo.com",0.0);
    user_add_to_list(&head,temp);
    user_show_all(head);
    user_show(user_find_by_id(head,"114514"));

}
