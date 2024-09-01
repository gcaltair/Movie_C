#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "../hash.txt"
#include "../Structure File/linked_list.h"

// 创建用户
User* user_create(User_hash_table * hashTable,const char* userID, const char* name, const char* gender, const char* telephone,
                  const char* password, const char* email, double balance) {
    User* new_user = (User*)malloc(sizeof(User));
    if (new_user == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    new_user->userID = strdup(userID);
    new_user->user_name = strdup(name);
    new_user->gender = strdup(gender);
    new_user->telephone = strdup(telephone);
    new_user->password = strdup(password);
    new_user->email = strdup(email);
    new_user->user_balance = balance;
    new_user->next = NULL;
    new_user->hash_next=NULL;
//id确定后插入
    insert_user_to_hash_table(hashTable,new_user);
    new_user->my_order=NULL;
    return new_user;
}
// 创建链表头节点
User* user_create_list(User* new_user) {
    new_user->next = NULL;
    return new_user;
}

// 添加一个元素到链表，头插法
void user_add_to_list(User** head, User* new_user) {
    if (*head == NULL) {
        (*head) = new_user;
        return;
    }
    User* temp = new_user;
    temp->next=(*head);
    (*head)=new_user;
}

// 直接添加一个用户到链表
void user_direct_add_to_list(User_hash_table * hashTable,User** head, const char* userID, const char* name, const char* gender,
                             const char* telephone, const char* password, const char* email, double balance) {
    User* new_user = user_create(hashTable,userID, name, gender, telephone, password, email, balance);
    if(new_user==NULL){
        printf("user_direct_add_to_list failed!");
        return;
    }
    user_add_to_list(head, new_user);
}

// 通过用户ID查找用户
User* user_find_by_id(User* head, const char* userID) {
    while (head != NULL) {
        if (strcmp(head->userID, userID) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// 显示单个用户信息
void user_show(const User* user) {
    if (user == NULL) {
        printf("User not found.\n");
        return;
    }
    printf("UserID: %s\n", user->userID);
    printf("Name: %s\n", user->user_name);
    printf("Gender: %s\n", user->gender);
    printf("Telephone: %s\n", user->telephone);
    printf("Email: %s\n", user->email);
    printf("Balance: %.2f\n", user->user_balance);
}

// 显示所有用户信息
void user_show_all(User* head) {
    while (head != NULL) {
        user_show(head);
        printf("\n");
        head = head->next;
    }
}

// 释放用户链表占用的内存
void user_free_list(User* head) {
    while (head != NULL) {
        User* temp = head;
        head = head->next;

        free(temp->userID);
        free(temp->user_name);
        free(temp->gender);
        free(temp->telephone);
        free(temp->password);
        free(temp->email);
        free(temp);
    }
}

// 初始化哈希表，将所有的指针设置为NULL
// 创建并初始化一个User_hash_table
User_hash_table* user_hash_table_create() {
    // 动态分配内存给User_hash_table结构
    User_hash_table* ht = (User_hash_table*)malloc(sizeof(User_hash_table));
    if (!ht) {
        // 如果内存分配失败，返回NULL
        return NULL;
    }
    // 初始化哈希表，将所有的指针设置为NULL
    user_hash_table_init(ht);
    return ht;
}
void user_hash_table_init(User_hash_table* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// 将用户插入哈希表，使用链地址法处理哈希冲突
void insert_user_to_hash_table(User_hash_table* ht, User* user) {
    unsigned int index = hash(user->userID, strlen(user->userID), 0x9747b28c); // 使用MurmurHash2生成索引
    //printf("Inserting user %s at index %u\n", user->userID, index);
    user->hash_next = ht->table[index];  // 将当前的哈希表索引处的元素放在新用户的后面
    ht->table[index] = user;        // 将新用户放在链表的头部
}

// 在哈希表中查找用户，通过userID查找
User* find_user_in_hash_table(User_hash_table* ht, const char* userID) {
    unsigned int index = hash(userID, strlen(userID), 0x9747b28c);
    User* user = ht->table[index];
    while (user) {
        if (strcmp(user->userID, userID) == 0) {
            return user;  // 找到用户，返回指针
        }
        user = user->hash_next;  // 继续查找链表中的下一个用户
    }
    return NULL;  // 如果未找到，返回NULL
}
void user_delete(User **head, const char *user_id) {
    User* current = *head;
    User* previous = NULL;

    while (current != NULL && strcmp(current->userID, user_id) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("User not found.\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    }
    else {
        previous->next = current->next;
    }

    free(current->userID);
    free(current->user_name);
    free(current->gender);
    free(current->telephone);
    free(current->password);
    free(current->email);
    free(current);

    printf("User deleted successfully.\n");
}

//修改用户信息
User* user_modify(User* head, char* id, int mode, char* arg) {
    User* user = user_find_by_id(head, id);
    if (user == NULL) {
        printf("The user is not existed!\n");
        return NULL; // 如果找不到用户，则直接返回
    }

    switch (mode) {
    case 1: // 修改用户ID
        free(user->userID); // 释放旧ID的内存
        user->userID = strdup(arg); // 分配新ID的内存并复制
        break;
    case 2: // 修改用户名
        free(user->user_name);
        user->user_name = strdup(arg);
        break;
    case 3: // 修改性别
        free(user->gender);
        user->gender = strdup(arg);
        break;
    case 4: // 修改电话
        free(user->telephone);
        user->telephone = strdup(arg);
        break;
    case 5: // 修改密码
        free(user->password);
        user->password = strdup(arg);
        break;
    case 6: // 修改邮箱
        free(user->email);
        user->email = strdup(arg);
        break;
    default:
        printf("Invalid modification mode\n");
        break;
    }
    return user;
}

