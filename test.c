//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include "User.h"
#include "admin.h"
#include "Cinema.h"
#include "Theater.h"

    // ����һ����Ӱ
    addMovie(&movie_list);

    Cinema* t = cinema_add("Cinema A", "Location A", 1);
    Cinema *cinema_list= cinema_create_list(t);;
    cinema_direct_add_to_list(&cinema_list, "Cinema C", "Location C", 3);
    Theater *theater_temp= theater_add("theater1",20,cinema_list,"3D");
    Theater *theater_list=theater_create_list(theater_temp);
    theater_add_to_list(&theater_list,theater_temp);
    cinema_show(theater_temp->cinema);
    theater_show(cinema_list->theater);

}
