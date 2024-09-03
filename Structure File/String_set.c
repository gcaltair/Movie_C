#include "string_set.h"
#include <stdlib.h>
#include <string.h>
#include"..\hash.txt"
StringSet* create_string_set() {
    StringSet* set = (StringSet*)malloc(sizeof(StringSet));
    if (set) {
        memset(set->table, 0, sizeof(set->table));
        set->size = 0;  // ��ʼ�����ϵĴ�С
    }
    return set;
}

bool string_set_add(StringSet* set, const char* str) {
    uint32_t index = hash(str, strlen(str), 0);
    StringSetNode* node = set->table[index];

    // ����Ƿ��Ѵ���
    while (node) {
        if (strcmp(node->key, str) == 0) {
            return false; // �Ѵ��ڣ������
        }
        node = node->next;
    }

    // �½��ڵ�
    node = (StringSetNode*)malloc(sizeof(StringSetNode));
    if (!node) return false;

    node->key = strdup(str);
    node->next = set->table[index];
    set->table[index] = node;
    set->size++;  // ���Ӽ��ϵĴ�С

    return true;
}

bool string_set_contains(StringSet* set, const char* str) {
    uint32_t index = hash(str, strlen(str), 0);
    StringSetNode* node = set->table[index];

    while (node) {
        if (strcmp(node->key, str) == 0) {
            return true;
        }
        node = node->next;
    }

    return false;
}

void string_set_destroy(StringSet* set) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        StringSetNode* node = set->table[i];
        while (node) {
            StringSetNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(set);
}

int string_set_size(StringSet* set) {
    return set->size;
}
