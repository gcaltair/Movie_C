//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include "User.h"
#include "admin.h"
#include "Cinema.h"

int main()
{

    Cinema* cinema_list = cinema_create_list("Cinema A", "Location A", 1,NULL);
    cinema_add_to_list(&cinema_list, "Cinema B", "Location B", 2,NULL);
    cinema_add_to_list(&cinema_list, "Cinema C", "Location C", 3,NULL);
//
//    printf("Showing all cinemas:\n");
    cinema_show_all(cinema_list);
    cinema_show(cinema_list);
    cinema_show(cinema_find_by_id(cinema_list,2));
}