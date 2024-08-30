#include <stdlib.h>
#include <string.h>
#include "Order.h"
#include "User.h"
#include "Cinema.h"
#include "Movie.h"
#include "Theater.h"
#include <stdio.h>
#include <stdint.h>
#include "../hash.txt"

Order* order_create(Order_hash_table *hashTable,char* orderID, User* usr, const char* user_id, Movie* movie, int movie_id,
                    Theater* theater, Cinema* cinema, int seats, int status, const char* time) {
    Order* new_order = (Order*)malloc(sizeof(Order));
    if (new_order == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    new_order->orderID = strdup(orderID);
    new_order->usr = usr;
    new_order->user_id = strdup(user_id);
    new_order->movie = movie;
    new_order->movie_id = movie_id;
    new_order->theater = theater;
    new_order->cinema = cinema;
    new_order->seats = seats;
    new_order->status = status;
    new_order->time = strdup(time);
    new_order->next = NULL;
    new_order->hash_next=NULL;
    insert_order_to_hash_table(hashTable,new_order);
    return new_order;
}
// 将一个订单添加到链表中
void order_add_to_list(Order** head, Order* new_order) {
    if (*head == NULL) {
        *head = new_order;
        (*head)->usr->order=(*head);
        return;
    }

    Order* temp = new_order;
    temp->next = (*head);
    (*head) = temp;
    (*head)->usr->order=(*head);
}

// 直接添加一个订单到链表

// 通过订单ID查找订单
Order* order_find_by_id(Order* head, char* orderID) {
    while (head != NULL) {
        if (strcmp(head->orderID,orderID)==0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// 显示单个订单信息
void order_show(const Order* order) {
    if (order == NULL) {
        printf("Order not found.\n");
        return;
    }
    printf("OrderID: %s\n", order->orderID);
    printf("UserID: %s\n", order->user_id);
    printf("Movie ID: %d\n", order->movie_id);
    printf("Seats: %d\n", order->seats);
    printf("Status: %d\n", order->status);
    printf("Time: %s\n", order->time);
    // 可以根据需要显示更多的订单信息
}

// 显示所有订单信息
void order_show_all(Order* head) {
    while (head != NULL) {
        order_show(head);
        printf("\n");
        head = head->next;
    }
}

// 初始化哈希表，将所有的指针设置为 NULL
void init_order_hash_table(Order_hash_table* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// 创建并初始化一个 Order_hash_table
Order_hash_table* order_hash_table_create() {
    Order_hash_table* ht = (Order_hash_table*)malloc(sizeof(Order_hash_table));
    if (!ht) {
        return NULL;
    }
    init_order_hash_table(ht);
    return ht;
}

// 使用哈希表将订单插入表中
void insert_order_to_hash_table(Order_hash_table* ht, Order* order) {
    uint32_t index = hash(order->orderID, strlen(order->orderID), 0x9747b28c) ;
    //printf("add key%s\n",order->orderID);
    order->hash_next = ht->table[index];  // 处理哈希冲突，将新订单插入哈希链表头部
    ht->table[index] = order;
}

// 在哈希表中查找订单，通过 orderID 查找
Order* find_order_in_hash_table(Order_hash_table* ht, char* orderID) {
    uint32_t index = hash(orderID, strlen(orderID), 0x9747b28c) ;
    Order* order = ht->table[index];
    while (order) {
        if (strcmp(order->orderID,orderID)==0) {
            return order;  // 找到匹配的订单，返回指针
        }
        order = order->hash_next;  // 使用 hash_next 指针继续查找哈希链表中的下一个订单
    }
    return NULL;  // 如果未找到，返回 NULL
}