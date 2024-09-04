#include "interval_tree.h"

// 创建一个新的区间树节点
interval_node* create_interval_node(int start, int end) {
    interval_node* node = (interval_node*)malloc(sizeof(interval_node));
    node->start = start;
    node->end = end;
    node->max_end = end;
    node->left = node->right = NULL;
    return node;
}
// 检查给定区间 [start, end] 是否与树中任何区间重叠
int is_overlapping(interval_node* root, int start, int end) {
    // 检查根节点是否为空
    if (root == NULL) {
        return 0;  // 空树，无重叠
    }

    // 检查当前节点的区间是否与新插入的区间重叠
    if (start < root->end && end > root->start) {
        return 1;  // 重叠
    }

    // 选择合适的子树继续检查
    if (root->left != NULL && root->left->max_end > start) {
        return is_overlapping(root->left, start, end);
    }

    return is_overlapping(root->right, start, end);
}


// 更新节点的最大结束时间
void update_max_end(interval_node* node) {
    if (node == NULL) return;
    node->max_end = node->end;
    if (node->left && node->left->max_end > node->max_end) {
        node->max_end = node->left->max_end;
    }
    if (node->right && node->right->max_end > node->max_end) {
        node->max_end = node->right->max_end;
    }
}

// 插入一个新的区间到区间树
interval_node* insert_interval_node(interval_node* root, int start, int end) {
    if (is_overlapping(root, start, end)) {
        // 区间已存在，返回当前根节点
        return root;
    }   
    
    if (root == NULL) return create_interval_node(start, end);

    if (start < root->start) {
        root->left = insert_interval_node(root->left, start, end);
    }
    else {
        root->right = insert_interval_node(root->right, start, end);
    }

    update_max_end(root);
    return root;
}

// 包装插入函数
interval_tree* insert_interval(interval_tree* tree, int start, int end) {
    if (tree == NULL) {
        tree = (interval_tree*)malloc(sizeof(interval_tree));
        tree->root = NULL;
    }
    tree->root = insert_interval_node(tree->root, start, end);
    return tree;
}

// 删除一个区间
interval_node* delete_interval_node(interval_node* root, int start, int end) {
    if (root == NULL) return NULL;

    if (start < root->start) {
        root->left = delete_interval_node(root->left, start, end);
    }
    else if (start > root->start) {
        root->right = delete_interval_node(root->right, start, end);
    }
    else if (end == root->end) {
        // 找到要删除的节点
        if (root->left == NULL) {
            interval_node* right_child = root->right;
            free(root);
            return right_child;
        }
        else if (root->right == NULL) {
            interval_node* left_child = root->left;
            free(root);
            return left_child;
        }
        else {
            // 找到右子树的最小值
            interval_node* min_node = root->right;
            while (min_node->left != NULL) {
                min_node = min_node->left;
            }
            root->start = min_node->start;
            root->end = min_node->end;
            root->right = delete_interval_node(root->right, min_node->start, min_node->end);
        }
    }
    else {
        root->right = delete_interval_node(root->right, start, end);
    }

    update_max_end(root);
    return root;
}

// 包装删除函数
interval_tree* delete_interval(interval_tree* tree, int start, int end) {
    if (tree == NULL || tree->root == NULL) return tree;
    tree->root = delete_interval_node(tree->root, start, end);
    return tree;
}

interval* find_free_times_interval(interval_tree* tree, int day_start, int day_end, int* num_intervals) {
    *num_intervals = 0;  // 初始化区间计数
    if (!tree) {
        // 如果树为空，整个时间段都空闲
        interval* intervals = (interval*)malloc(sizeof(interval));
        intervals[0].start = day_start;
        intervals[0].end = day_end;
        *num_intervals = 1;
        return intervals;
    }

    interval_node* node = tree->root;
    int last_end = day_start;
    interval_node* stack[100];  // 使用一个栈来存储节点
    int top = -1;
    interval* intervals = (interval*)malloc(100 * sizeof(interval));  // 初始分配，最多支持100个空闲区间

    while (node != NULL || top >= 0) {
        // 向左遍历所有节点
        while (node != NULL) {
            stack[++top] = node;
            node = node->left;
        }

        // 取栈顶元素
        node = stack[top--];

        // 检查当前节点的起始时间与 last_end 之间是否有空闲时间
        if (last_end < node->start) {
            if (node->start - last_end >= 60) {  // 只有空闲时间段大于等于60分钟才记录
                intervals[*num_intervals].start = last_end;
                intervals[*num_intervals].end = node->start;
                (*num_intervals)++;
            }
        }

        // 更新 last_end
        last_end = node->end > last_end ? node->end : last_end;

        // 移动到右子树
        node = node->right;
    }

    // 检查最后一个区间后的空闲时间
    if (last_end < day_end) {
        if (day_end - last_end >= 60) {
            intervals[*num_intervals].start = last_end;
            intervals[*num_intervals].end = day_end;
            (*num_intervals)++;
        }
    }

    // 返回动态分配的空闲区间数组
    return intervals;
}

void print_intervals(interval* intervals, int num_intervals) {
    for (int i = 0; i < num_intervals; i++) {
        printf("空闲时间：%02d:%02d 到 %02d:%02d\n",
            intervals[i].start / 60, intervals[i].start % 60,
            intervals[i].end / 60, intervals[i].end % 60);
    }
}




// 查找并输出一天中的所有空闲时间
void find_free_times(interval_tree* tree, int day_start, int day_end) {
    if (!tree) {
        printf("本影厅全时段空闲!\n");
        return;
    }
    interval_node* node = tree->root;
    int last_end = day_start;
    interval_node* stack[100];  // 使用一个栈来存储节点
    int top = -1;

    while (node != NULL || top >= 0) {
        // 向左遍历所有节点
        while (node != NULL) {
            stack[++top] = node;
            node = node->left;
        }

        // 取栈顶元素
        node = stack[top--];

        // 检查当前节点的起始时间与 last_end 之间是否有空闲时间
        if (last_end < node->start) {
            if (node->start - last_end >= 60)
                printf("空闲时间：%02d:%02d 到 %02d:%02d\n", last_end / 60, last_end % 60, node->start / 60, node->start % 60);
        }

        // 更新 last_end
        last_end = node->end > last_end ? node->end : last_end;

        // 移动到右子树
        node = node->right;
    }

    // 检查最后一个区间后的空闲时间
    if (last_end < day_end) {
        if (day_end - last_end >= 60)
            printf("空闲时间：%02d:%02d 到 %02d:%02d\n", last_end / 60, last_end % 60, day_end / 60, day_end % 60);
    }
}


// 打印区间树（中序遍历）
void print_interval_tree_node(interval_node* root) {
    if (root == NULL) return;
    print_interval_tree_node(root->left);
    printf("排片时间：%d 分钟到 %d 分钟\n", root->start, root->end);
    print_interval_tree_node(root->right);
}

// 包装打印函数
void print_interval_tree(interval_tree* tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("区间树为空\n");
        return;
    }
    print_interval_tree_node(tree->root);
}

// 释放区间树内存
void free_interval_tree_node(interval_node* root) {
    if (root == NULL) return;
    free_interval_tree_node(root->left);
    free_interval_tree_node(root->right);
    free(root);
}

// 包装释放函数
void free_interval_tree(interval_tree* tree) {
    if (tree == NULL) return;
    free_interval_tree_node(tree->root);
    free(tree);
}
