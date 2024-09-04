#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <stdio.h>
#include <stdlib.h>

// 区间节点结构体
typedef struct interval_node {
    int start;                    // 区间开始时间
    int end;                      // 区间结束时间
    int max_end;                  // 子树中最大的结束时间
    struct interval_node* left;   // 左子树
    struct interval_node* right;  // 右子树
} interval_node;

// 区间树结构体
typedef struct interval_tree {
    interval_node* root;          // 树的根节点
} interval_tree;
//检测是否重叠
int is_overlapping(interval_node* root, int start, int end);
// 创建一个新的区间树节点
interval_node* create_interval_node(int start, int end);

// 插入一个新的区间到区间树
interval_tree* insert_interval(interval_tree* tree, int start, int end);

// 删除一个区间
interval_tree* delete_interval(interval_tree* tree, int start, int end);

// 查找并输出一天中的所有空闲时间
void find_free_times(interval_tree* tree, int day_start, int day_end);

// 打印区间树
void print_interval_tree(interval_tree* tree);

// 释放区间树内存
void free_interval_tree(interval_tree* tree);

#endif // INTERVAL_TREE_H
