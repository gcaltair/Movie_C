//
// Created by G on 2024/8/27.
//
#include<stdio.h>
#include "User.h"
#include "admin.h"

int main()
{
    Cinema* cinema = cinema_add("Cinema A", "123 Main St", 101);
    User* usr1= User_add("114514","gc",
                         "man","114514",
                         "114514","114514@qq.com",1.1);
    user_show(usr1);
    Admin* admin = Admin_add("adm123", "Alice",
                             "12345678901", "password123",
                             "alice@cinema.com", cinema);
    admin_show(admin);
}