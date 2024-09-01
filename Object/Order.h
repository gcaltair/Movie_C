// Created by G on 2024/8/27.
//

#ifndef MOVIE_C_ORDER_H
#define MOVIE_C_ORDER_H
#define HASH_TABLE_SIZE 100
typedef struct User User;
typedef struct Movie Movie;
typedef struct Theater Theater;
typedef struct Cinema Cinema;
typedef struct Order{
    char* orderID;
    User* usr;
    char* user_id;
    Movie* movie;
    char* movie_id;
    Theater* theater;
    Cinema* cinema;
    char* seats; //可以是二维数组？
    int seat_number;
    int status; //订单状态
    char* time;
    struct Order* next;
    struct Order* hash_next;
}Order;
typedef struct Order_hash_table Order_hash_table;

Order* order_create(Order_hash_table *hashTable,const char* orderID, User* usr, const char* user_id, Movie* movie, const char* movie_id,
                    Theater* theater, Cinema* cinema, const char* seats, int seat_number,int status, const char* time);
void order_add_to_list(Order** head, Order* new_order);

Order* order_find_by_id(Order* head, char* orderID);

void order_show(const Order* order);

void order_show_all(Order* head);

int (*Seat_map_generation())[26];
void Seat_map_show(int (*seat_map)[26]);
int get_remaining_ticket(int (*seat_map)[26]);
char* get_current_day();
char* get_current_time();
char* get_orderID();
int history_order_time_check(User* usr, Movie* movie, Order_hash_table* hashTable);

typedef struct Order_hash_table {
    Order* table[HASH_TABLE_SIZE];
} Order_hash_table;

// 创建并初始化一个 Order_hash_table
Order_hash_table* order_hash_table_create();

// 初始化哈希表，将所有的指针设置为 NULL
void init_order_hash_table(Order_hash_table* ht);

// 使用哈希表将订单插入表中
void insert_order_to_hash_table(Order_hash_table* ht, Order* order);

// 在哈希表中查找订单，通过 orderID 查找
Order* find_order_in_hash_table(Order_hash_table* ht, char* orderID);
#endif //MOVIE_C_ORDER_H
