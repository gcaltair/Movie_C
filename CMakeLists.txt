cmake_minimum_required(VERSION 3.28)
project(Movie_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Movie_C main.c
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
        "main.h"
 "Object/Film.c" "Object/Film.h" "Structure File/String_set.c" "Structure File/String_set.h" "Structure File/interval_tree.h" "Structure File/interval_tree.c" "Structure File/io_system.c" "Structure File/io_system.h" "admin_system.h" "admin_system.c"  )