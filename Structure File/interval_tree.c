#include "interval_tree.h"

// ����һ���µ��������ڵ�
interval_node* create_interval_node(int start, int end) {
    interval_node* node = (interval_node*)malloc(sizeof(interval_node));
    node->start = start;
    node->end = end;
    node->max_end = end;
    node->left = node->right = NULL;
    return node;
}
// ���������� [start, end] �Ƿ��������κ������ص�
int is_overlapping(interval_node* root, int start, int end) {
    // �����ڵ��Ƿ�Ϊ��
    if (root == NULL) {
        return 0;  // ���������ص�
    }

    // ��鵱ǰ�ڵ�������Ƿ����²���������ص�
    if (start < root->end && end > root->start) {
        return 1;  // �ص�
    }

    // ѡ����ʵ������������
    if (root->left != NULL && root->left->max_end > start) {
        return is_overlapping(root->left, start, end);
    }

    return is_overlapping(root->right, start, end);
}


// ���½ڵ��������ʱ��
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

// ����һ���µ����䵽������
interval_node* insert_interval_node(interval_node* root, int start, int end) {
    if (is_overlapping(root, start, end)) {
        // �����Ѵ��ڣ����ص�ǰ���ڵ�
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

// ��װ���뺯��
interval_tree* insert_interval(interval_tree* tree, int start, int end) {
    if (tree == NULL) {
        tree = (interval_tree*)malloc(sizeof(interval_tree));
        tree->root = NULL;
    }
    tree->root = insert_interval_node(tree->root, start, end);
    return tree;
}

// ɾ��һ������
interval_node* delete_interval_node(interval_node* root, int start, int end) {
    if (root == NULL) return NULL;

    if (start < root->start) {
        root->left = delete_interval_node(root->left, start, end);
    }
    else if (start > root->start) {
        root->right = delete_interval_node(root->right, start, end);
    }
    else if (end == root->end) {
        // �ҵ�Ҫɾ���Ľڵ�
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
            // �ҵ�����������Сֵ
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

// ��װɾ������
interval_tree* delete_interval(interval_tree* tree, int start, int end) {
    if (tree == NULL || tree->root == NULL) return tree;
    tree->root = delete_interval_node(tree->root, start, end);
    return tree;
}

interval* find_free_times_interval(interval_tree* tree, int day_start, int day_end, int* num_intervals) {
    *num_intervals = 0;  // ��ʼ���������
    if (!tree) {
        // �����Ϊ�գ�����ʱ��ζ�����
        interval* intervals = (interval*)malloc(sizeof(interval));
        intervals[0].start = day_start;
        intervals[0].end = day_end;
        *num_intervals = 1;
        return intervals;
    }

    interval_node* node = tree->root;
    int last_end = day_start;
    interval_node* stack[100];  // ʹ��һ��ջ���洢�ڵ�
    int top = -1;
    interval* intervals = (interval*)malloc(100 * sizeof(interval));  // ��ʼ���䣬���֧��100����������

    while (node != NULL || top >= 0) {
        // ����������нڵ�
        while (node != NULL) {
            stack[++top] = node;
            node = node->left;
        }

        // ȡջ��Ԫ��
        node = stack[top--];

        // ��鵱ǰ�ڵ����ʼʱ���� last_end ֮���Ƿ��п���ʱ��
        if (last_end < node->start) {
            if (node->start - last_end >= 60) {  // ֻ�п���ʱ��δ��ڵ���60���Ӳż�¼
                intervals[*num_intervals].start = last_end;
                intervals[*num_intervals].end = node->start;
                (*num_intervals)++;
            }
        }

        // ���� last_end
        last_end = node->end > last_end ? node->end : last_end;

        // �ƶ���������
        node = node->right;
    }

    // ������һ�������Ŀ���ʱ��
    if (last_end < day_end) {
        if (day_end - last_end >= 60) {
            intervals[*num_intervals].start = last_end;
            intervals[*num_intervals].end = day_end;
            (*num_intervals)++;
        }
    }

    // ���ض�̬����Ŀ�����������
    return intervals;
}

void print_intervals(interval* intervals, int num_intervals) {
    for (int i = 0; i < num_intervals; i++) {
        printf("����ʱ�䣺%02d:%02d �� %02d:%02d\n",
            intervals[i].start / 60, intervals[i].start % 60,
            intervals[i].end / 60, intervals[i].end % 60);
    }
}




// ���Ҳ����һ���е����п���ʱ��
void find_free_times(interval_tree* tree, int day_start, int day_end) {
    if (!tree) {
        printf("��Ӱ��ȫʱ�ο���!\n");
        return;
    }
    interval_node* node = tree->root;
    int last_end = day_start;
    interval_node* stack[100];  // ʹ��һ��ջ���洢�ڵ�
    int top = -1;

    while (node != NULL || top >= 0) {
        // ����������нڵ�
        while (node != NULL) {
            stack[++top] = node;
            node = node->left;
        }

        // ȡջ��Ԫ��
        node = stack[top--];

        // ��鵱ǰ�ڵ����ʼʱ���� last_end ֮���Ƿ��п���ʱ��
        if (last_end < node->start) {
            if (node->start - last_end >= 60)
                printf("����ʱ�䣺%02d:%02d �� %02d:%02d\n", last_end / 60, last_end % 60, node->start / 60, node->start % 60);
        }

        // ���� last_end
        last_end = node->end > last_end ? node->end : last_end;

        // �ƶ���������
        node = node->right;
    }

    // ������һ�������Ŀ���ʱ��
    if (last_end < day_end) {
        if (day_end - last_end >= 60)
            printf("����ʱ�䣺%02d:%02d �� %02d:%02d\n", last_end / 60, last_end % 60, day_end / 60, day_end % 60);
    }
}


// ��ӡ�����������������
void print_interval_tree_node(interval_node* root) {
    if (root == NULL) return;
    print_interval_tree_node(root->left);
    printf("��Ƭʱ�䣺%d ���ӵ� %d ����\n", root->start, root->end);
    print_interval_tree_node(root->right);
}

// ��װ��ӡ����
void print_interval_tree(interval_tree* tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("������Ϊ��\n");
        return;
    }
    print_interval_tree_node(tree->root);
}

// �ͷ��������ڴ�
void free_interval_tree_node(interval_node* root) {
    if (root == NULL) return;
    free_interval_tree_node(root->left);
    free_interval_tree_node(root->right);
    free(root);
}

// ��װ�ͷź���
void free_interval_tree(interval_tree* tree) {
    if (tree == NULL) return;
    free_interval_tree_node(tree->root);
    free(tree);
}
