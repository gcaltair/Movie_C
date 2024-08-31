//
// Created by G on 2024/8/31.
//

#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAUT_CAPACITY 10
#define EDGE_VALUE 1024
Vector * vector_create() {
    Vector* v=calloc(1,sizeof(Vector));
    if(v==NULL) {
        printf("calloc error");
        return NULL;
    }
    v->data=calloc(DEFAUT_CAPACITY,sizeof(ElementType));
    if(v->data==NULL) {
        printf("malloc error");
        free(v);
        return NULL;
    }
    v->capacity=DEFAUT_CAPACITY;
    return v;

}

void vector_destroy(Vector *v) {
    free(v->data);
    free(v);
}

static void vector_resize(Vector *v) {
    int old_capacity=v->capacity;
    int new_capacity=old_capacity>EDGE_VALUE?((old_capacity>>1)+old_capacity):(old_capacity<<1);
    ElementType * p_=realloc(v->data,sizeof(int)*new_capacity);
    if(p_==NULL) {
        printf("realloc error");
        exit(-1);
    }
    v->data=p_;
}
void vector_push_back(Vector *v, ElementType element) {
    if(v->size>=v->capacity-1) vector_resize(v);
    v->data[++(v->size)]=element;
}