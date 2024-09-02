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
} StringSet;


StringSet* create_string_set();
//增加元素
bool string_set_add(StringSet* set, const char* str);
//检测是否存在
bool string_set_contains(StringSet* set, const char* str);
//删除
void string_set_destroy(StringSet* set);

#endif // STRING_SET_H
