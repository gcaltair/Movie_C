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
    int size;  // �����ĳ�Ա���������ڼ�¼������Ԫ�صĸ���
} StringSet;

// ��������
StringSet* create_string_set();
bool string_set_add(StringSet* set, const char* str);
bool string_set_contains(StringSet* set, const char* str);
void string_set_destroy(StringSet* set);
int string_set_size(StringSet* set);

#endif // STRING_SET_H
