//
// Created by G on 2024/8/2.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>
typedef int ElementType;
typedef struct {
    void* data;
    size_t capacity;
    size_t size;
    size_t elem_size;
}Vector;
Vector* vector_create(size_t elem_size);
void vector_destroy(Vector* v);
void vector_push_back(Vector* v,void* value);
#endif //VECTOR_H
