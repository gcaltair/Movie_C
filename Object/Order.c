#include <stdlib.h>
#include <string.h>
#include "Order.h"
#include "User.h"
#include "Cinema.h"
#include "Movie.h"
#include "Theater.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "../hash.txt"
#include "../Structure File/linked_list.h"
Order* order_create(Order_hash_table *hashTable,const char* orderID, User* usr, const char* user_id, Movie* movie, const char* movie_id,
                    Theater* theater, Cinema* cinema, const char* seats, int seat_number,int status, const char* time) {
    Order* new_order = (Order*)malloc(sizeof(Order));
    if (new_order == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    new_order->orderID = strdup(orderID);
    new_order->usr = usr;
    new_order->user_id = strdup(user_id);
    new_order->movie = movie;
    new_order->movie_id = strdup(movie_id);
    new_order->theater = theater;
    new_order->cinema = cinema;
    new_order->seats = strdup(seats);
    new_order->seat_number=seat_number;
    new_order->status = status;
    new_order->time = strdup(time);
    new_order->next = NULL;
    new_order->hash_next=NULL;

    string_direct_add_to_list(&(new_order->usr->my_order),new_order->orderID);

    insert_order_to_hash_table(hashTable,new_order);
    return new_order;
}
// 将一个订单添加到链表中
void order_add_to_list(Order** head, Order* new_order) {
    if (*head == NULL) {
        *head = new_order;
        return;
    }

    Order* temp = new_order;
    temp->next = (*head);
    (*head) = temp;
}

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
    printf("Movie ID: %s\n", order->movie_id);
    printf("Seats: %s\n", order->seats);
    printf("Seat number: %d\n", order->seat_number);
    printf("Status: %d\n", order->status);
    printf("Time: %s\n", order->time);
    movie_show(order->movie);
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


//订座位，seats为用户视角下，故行与列均-1
// 座位  0 ：不在影院座次范围内
//       1 ：可购买
//       2 ：已售出
//       3 ：因与已售出的座位相隔一个座位导致无法售出
//status 1 : 生成订单已付款
//       2 ：生成订单未付款
//       3 ：取消订单
//       4 ：退款
//创建并初始化座位图
int (*Seat_map_generation())[26] {
    int (*seat_map)[26] = (int(*)[26])malloc(9 * sizeof(*seat_map));
    for (int line = 0; line < 9; line++) {
        for (int row = 0; row < 26; row++) {
            if (row - line >= 18 || row + line <= 7) {
                seat_map[line][row] = 0;
            }
            else {
                seat_map[line][row] = 1;
            }
        }
    }
    return seat_map;
}
//展示座位图
void Seat_map_show(int (*seat_map)[26]) {
    printf(" ");
    for (int i = 1; i <= 26; i++) {
        if (i > 9) {
            printf("%d ", i);
        }
        else {
            printf("%d  ", i);
        }
    }
    printf("\n");
    for (int line = 0; line < 9; line++) {
        printf("%c", line + 65);
        for (int row = 0; row < 26; row++) {
            if (seat_map[line][row] == 1) {
                printf("*  ");
            }
            else {
                printf("   ");
            }
        }
        printf("\n");
    }
}
//查询场次剩余座位数
int get_remaining_ticket(int (*seat_map)[26]) {
    int remaining_ticket = 0;
    for (int line = 0; line < 9; line++) {
        for (int row = 0; row < 26; row++) {
            if (seat_map[line][row] == 1) {
                remaining_ticket++;
            }
        }
    }
    return remaining_ticket++;
}
char* get_current_day() {
    time_t now = time(0);
    struct tm* ltm = localtime(&now);
    int current_year = 1900 + ltm->tm_year;
    int current_month = 1 + ltm->tm_mon;
    int current_day = ltm->tm_mday;
    char* current_time = (char*)malloc(11 * sizeof(char));
    if (current_time == NULL) {
        return NULL;
    }
    sprintf(current_time, "%d-%d-%d", current_year, current_month, current_day);
    return current_time;
}
char* get_current_time() {
    time_t now = time(0);
    struct tm* ltm = localtime(&now);
    int current_year = 1900 + ltm->tm_year;
    int current_month = 1 + ltm->tm_mon;
    int current_day = ltm->tm_mday;
    int current_hour = ltm->tm_hour;
    int current_min = ltm->tm_min;
    int current_sec = ltm->tm_sec;
    char* current_time = (char*)malloc(20 * sizeof(char));
    if (current_time == NULL) {
        return NULL;
    }
    sprintf(current_time, "%d-%d-%d %d:%d:%d", current_year, current_month, current_day, current_hour, current_min, current_sec);
    return current_time;
}
char* get_orderID() {
    srand(time(0));
    int randomNumber = rand();
    char* rand;
    sprintf(rand, "%d", randomNumber);
    char* orderID = strcat(get_current_time(), rand);
    return orderID;
}
//历史场次时间冲突判断
//return 0 :查询失败
//       1 :无冲突
//       2 :已购买过该场次的票
//       3 :当天已经购买五个场次的票
int history_order_time_check(User* usr, Movie* movie, Order_hash_table* hashTable) {
    int count = 0;
    int history_order_year[100];
    int history_order_month[100];
    int history_order_day[100];
    Linked_string_list* movie_id_list = NULL;
    if (!usr) { printf("User is NULL!\n"); return 0; }
    Linked_string_list* order = usr->my_order;
    while (order != NULL) {
        Order* order_find = find_order_in_hash_table(hashTable, order->id);
        if (order_find->status != 1) continue;
        if ((sscanf(order_find->time, "%d-%d-%d", &history_order_year[count], &history_order_month[count], &history_order_day[count])) != 3) {
            printf("%d\n", history_order_day[count]);
            printf("%s",order_find->time);
            return 0;
        }
        string_direct_add_to_list(&movie_id_list,order_find->movie_id);
        count++;
        order = order->next;
    }
    int current_year, current_month, current_day;
    sscanf(get_current_day(), "%d-%d-%d", &current_year, &current_month, &current_day);
    int history_order_count = 0;
    for (int i = count; i >0; i--) {
        if (history_order_year[i] == current_year && history_order_month[i] == current_month && history_order_day[i] == current_day && strcmp(movie_id_list->id, movie->movie_id)) {
            history_order_count++;
        }
        if (strcmp(movie_id_list->id,movie->movie_id) == 0) {
            return 2;
        }
        movie_id_list = movie_id_list->next;
    }
    free_list(movie_id_list);
    
    if (history_order_count >= 5) {
        return 3;
    }
    return 1;
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

