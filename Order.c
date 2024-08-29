#include <stdlib.h>
#include <string.h>
#include "Order.h"
#include "User.h"
#include "Cinema.h"
#include "Movie.h"
#include "Theater.h"
#include <stdio.h>
Order* order_create(int orderID, User* usr, const char* user_id, Movie* movie, int movie_id,
                    Theater* theater, Cinema* cinema, int seats, int status, const char* time) {
    Order* new_order = (Order*)malloc(sizeof(Order));
    if (new_order == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    new_order->orderID = orderID;
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

    return new_order;
}
// ��һ��������ӵ�������
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

// ֱ�����һ������������
void order_direct_add_to_list(Order** head, int orderID, User* usr, const char* user_id, Movie* movie,
                              int movie_id, Theater* theater, Cinema* cinema, int seats, int status, const char* time) {
    Order* new_order = order_create(orderID, usr, user_id, movie, movie_id, theater, cinema, seats, status, time);
    order_add_to_list(head, new_order);
}

// ͨ������ID���Ҷ���
Order* order_find_by_id(Order* head, int orderID) {
    while (head != NULL) {
        if (head->orderID == orderID) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// ��ʾ����������Ϣ
void order_show(const Order* order) {
    if (order == NULL) {
        printf("Order not found.\n");
        return;
    }
    printf("OrderID: %d\n", order->orderID);
    printf("UserID: %s\n", order->user_id);
    printf("Movie ID: %d\n", order->movie_id);
    printf("Seats: %d\n", order->seats);
    printf("Status: %d\n", order->status);
    printf("Time: %s\n", order->time);
    // ���Ը�����Ҫ��ʾ����Ķ�����Ϣ
}

// ��ʾ���ж�����Ϣ
void order_show_all(Order* head) {
    while (head != NULL) {
        order_show(head);
        printf("\n");
        head = head->next;
    }
}
