cmake_minimum_required(VERSION 3.28)
project(Movie_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Movie_C main.c
        test.c
        Object/User.c
        Object/User.h
        Object/Order.c
        Object/Order.h
        Object/Movie.c
        Object/Movie.h
        Object/Theater.c
        Object/Theater.h
        Object/Cinema.c
        Object/Cinema.h
        Object/admin.h
        Object/admin.c
        data_process.c
        data_process.h
        "Structure File/linked_list.c"
        "Structure File/linked_list.h"
        user_system.c
        user_system.h
        test.h
 "Object/Film.c" "Object/Film.h")
add_executable(test1
        test.c
        Object/User.c
        Object/User.h
        Object/Theater.c
        Object/Theater.h
        Object/Cinema.c
        Object/Cinema.h
        Object/admin.h
        Object/admin.c
        Object/Order.c
        Object/Order.h
        Object/Movie.c
        Object/Movie.h
        data_process.c
        data_process.h
        "Structure File/linked_list.c"
        "Structure File/linked_list.h"
        user_system.c
        user_system.h
        test.h
 "Object/Film.c" "Object/Film.h")