//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include "User.h"
#include "admin.h"
#include "Cinema.h"
#include"Movie.h"
#include "Theater.h"
#include "Order.h"
int main(){

	Order* head = NULL;
	Cinema* cin = cinema_create("A", "location 1", 1);
	User* usr = user_create("111", "2323", "dsds", "111", "asdf", "dadsa", 0.1);
	Theater* tha = theater_create("sadsd", 10, "A", "3D");
	Movie* mov=movie_create("12212", tha, "500-11:10", "500-13:30", 100, 50.0, 1, "3D");
	add_order(usr, mov, head);
	

}
