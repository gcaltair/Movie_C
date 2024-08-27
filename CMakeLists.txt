cmake_minimum_required(VERSION 3.28)
project(Movie_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Movie_C main.c
        Vector.c
        Vector.h
        test.c
        User.c
        User.h
        Order.c
        Order.h
        Movie.c
        Movie.h)
add_executable(test1
        test.c
        User.c
        User.h
        Order.c)