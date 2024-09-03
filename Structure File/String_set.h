#ifndef STRING_SET_H
#define STRING_SET_H

#include <stdint.h>
#include <stdbool.h>

// 定义哈希表大小
#define HASH_TABLE_SIZE 101

// Set中的节点结构
typedef struct StringSetNode {
    char* key;
    struct StringSetNode* next;
} StringSetNode;

// Set结构
typedef struct {
    StringSetNode* table[HASH_TABLE_SIZE];
    int size;  // 新增的成员变量，用于记录集合中元素的个数
} StringSet;

// 函数声明
StringSet* create_string_set();
bool string_set_add(StringSet* set, const char* str);
bool string_set_contains(StringSet* set, const char* str);
void string_set_destroy(StringSet* set);
int string_set_size(StringSet* set);

#endif // STRING_SET_H
