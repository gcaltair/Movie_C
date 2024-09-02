//
// Created by G on 2024/8/27.
//
#ifndef MOVIE_C_USER_H
#define MOVIE_C_USER_H

#define HASH_TABLE_SIZE 100
typedef struct User_hash_table User_hash_table;
typedef struct Vector Vector;
typedef struct Order Order;
typedef struct Linked_string_list Linked_string_list;
typedef struct User {
    char* userID;
    char* user_name;
    char* gender;
    char* telephone;
    char* password;
    char* email;
    double user_balance;
    struct User* next;
    struct User* hash_next;
    Linked_string_list* my_order;
} User;

//对于修改用户的功能的几个mode进行枚举
enum user_modify_mode {
    modify_id = 1,
    modify_name = 2,
    
    modify_telephone = 3,
    modify_password = 4,
    modify_email = 5,
    modify_gender = 6,
};

User* user_create(User_hash_table* hashTable, const char* userID, const char* name, const char* gender, const char* telephone,
                  const char* password, const char* email, double balance); // 创建用户

User* user_create_list(User* new_user); // 创建链表头节点
void user_add_to_list(User** head, User* new_user); // 添加一个元素到链表，头插法
void user_direct_add_to_list(User_hash_table *hashTable,User** head, const char* userID, const char* name, const char* gender,
                             const char* telephone, const char* password, const char* email, double balance);
User* user_find_by_id(User* head, const char* userID); // 通过用户ID查找用户

void user_show(const User* user); // 显示单个用户信息
void user_show_all(User* head); // 显示所有用户信息
//修改用户信息
User* user_modify(User* head, char* id, int mode, char* arg);


//哈希表相关
typedef struct User_hash_table{
    User* table[HASH_TABLE_SIZE];
}User_hash_table;
User_hash_table* user_hash_table_create();
void user_hash_table_init(User_hash_table * ht);
void insert_user_to_hash_table(User_hash_table * ht, User* user);
User* find_user_in_hash_table(User_hash_table * ht, const char* userID);
void user_free_list(User* head);
void user_delete(User** head, const char* name);
#endif //MOVIE_C_USER_H

