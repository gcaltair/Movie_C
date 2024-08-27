//
// Created by G on 2024/8/2.
//

#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAUT_CAPACITY 10
#define EDGE_VALUE 1024
Vector * vector_create(size_t elem_size) {
    Vector* v=calloc(1,sizeof(Vector));
    if(v==NULL) {
        perror("Fail to initialize vector!");
        exit(EXIT_FAILURE);
    }
    v->data=calloc(DEFAUT_CAPACITY,elem_size);
    if(v->data==NULL) {
        perror("Fail to initialize data!");
        free(v);
        return NULL;
    }
    v->capacity=DEFAUT_CAPACITY;
    v->size=0;
    return v;

}

void vector_destroy(Vector *v) {
    free(v->data);
    free(v);
}

static void vector_resize(Vector *v) {
    size_t old_capacity=v->capacity;
    size_t new_capacity=old_capacity>EDGE_VALUE?((old_capacity>>1)+old_capacity):(old_capacity<<1);
    void* p_=realloc(v->data,(v->elem_size)*new_capacity);
    if(p_==NULL) {
        printf("realloc error");
        exit(-1);
    }
    v->data=p_;
}
void vector_push_back(Vector *v,void* value) {
    if(v->size>=v->capacity-1) vector_resize(v);
    v->data[++(v->size)]=value;
}

