//
// Created by G on 2024/8/31.
//

#ifndef MOVIE_C_VECTOR_H
#define MOVIE_C_VECTOR_H
#ifndef VECTOR_H
#define VECTOR_H

typedef char* ElementType;
typedef struct Vector{
    ElementType* data;
    int capacity;
    int size;
}Vector;
Vector* vector_create();
void vector_destroy(Vector* v);
void vector_push_back(Vector* v,ElementType element);
#endif //VECTOR_H
#endif //MOVIE_C_VECTOR_H
