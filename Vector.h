//
// Created by G on 2024/8/2.
//

#ifndef VECTOR_H
#define VECTOR_H

typedef int ElementType;
typedef struct {
    ElementType* data;
    int capacity;
    int size;
}Vector;
Vector* vector_create();
void vector_destroy(Vector* v);
void vector_push_back(Vector* v,ElementType element);
#endif //VECTOR_H
