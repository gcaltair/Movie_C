#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <stdio.h>
#include <stdlib.h>

// ����ڵ�ṹ��
typedef struct interval_node {
    int start;                    // ���俪ʼʱ��
    int end;                      // �������ʱ��
    int max_end;                  // ���������Ľ���ʱ��
    struct interval_node* left;   // ������
    struct interval_node* right;  // ������
} interval_node;

// �������ṹ��
typedef struct interval_tree {
    interval_node* root;          // ���ĸ��ڵ�
} interval_tree;
//����Ƿ��ص�
int is_overlapping(interval_node* root, int start, int end);
// ����һ���µ��������ڵ�
interval_node* create_interval_node(int start, int end);

// ����һ���µ����䵽������
interval_tree* insert_interval(interval_tree* tree, int start, int end);

// ɾ��һ������
interval_tree* delete_interval(interval_tree* tree, int start, int end);

// ���Ҳ����һ���е����п���ʱ��
void find_free_times(interval_tree* tree, int day_start, int day_end);

// ��ӡ������
void print_interval_tree(interval_tree* tree);

// �ͷ��������ڴ�
void free_interval_tree(interval_tree* tree);

#endif // INTERVAL_TREE_H
