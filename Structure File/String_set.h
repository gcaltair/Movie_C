#ifndef STRING_SET_H
#define STRING_SET_H

#include <stdint.h>
#include <stdbool.h>

// �����ϣ���С
#define HASH_TABLE_SIZE 101

// Set�еĽڵ�ṹ
typedef struct StringSetNode {
    char* key;
    struct StringSetNode* next;
} StringSetNode;

// Set�ṹ
typedef struct {
    StringSetNode* table[HASH_TABLE_SIZE];
} StringSet;


StringSet* create_string_set();
//����Ԫ��
bool string_set_add(StringSet* set, const char* str);
//����Ƿ����
bool string_set_contains(StringSet* set, const char* str);
//ɾ��
void string_set_destroy(StringSet* set);

#endif // STRING_SET_H
