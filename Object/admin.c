//
// Created by Y on 2024/8/27.
//

#include "admin.h"
#include "string.h"
#include "Cinema.h"
#include "stdio.h"
Admin* Admin_create(const char* id, const char* name, const char* telephone,
                    const char* password, const char* email, Cinema *cinema_,const char* cinema_id) {
    // 动态分配内存给Admin结构体
    Admin* admin = (Admin*)malloc(sizeof(Admin));
    if (admin == NULL) {
        printf("内存分配失败.\n");
        return NULL;
    }

    // 动态分配内存并复制参数内容到结构体字段
    admin->admin_id = strdup(id);
    admin->admin_name = strdup(name);
    admin->admin_telephone = strdup(telephone);
    admin->admin_password = strdup(password);
    admin->admin_email = strdup(email);
    admin->cinema_id=strdup(cinema_id);
    admin->cinema=cinema_;
    admin->next=NULL;
    return admin;
}
void admin_add_to_list(Admin** head, Admin* new_admin) {
    if (*head == NULL) {
        *head = new_admin;
        return;
    }
    Admin* temp = new_admin;
    temp->next = *head;
    *head = temp;
}
void admin_show_all(Admin* head) {
    Admin* temp = head;
    while (temp != NULL) {
        admin_show(temp);
        temp = temp->next;
    }
}
void admin_show(const Admin *admin) {
    if (admin == NULL) {
        printf("Admin Data is NULL.\n");
        return;
    }

    printf("管理员 ID: %s\n", admin->admin_id);
    printf("姓名: %s\n", admin->admin_name);
    printf("电话: %s\n", admin->admin_telephone);
    printf("Password: %s\n", admin->admin_password);  // 注意：实际系统中通常不会打印密码
    printf("邮箱: %s\n", admin->admin_email);
    cinema_show(admin->cinema);
    printf("\n");

}
//修改用户信息
Admin* admin_modify(Admin* admin, int modify_mode, char* arg) {
    if (admin == NULL) {
        printf("管理员不存在!");
        return NULL; // 如果找不到管理员，则直接返回
    }

    switch (modify_mode) {
        case 1:
            // 通常不推荐修改ID，但为了完整性包含此功能
            free(admin->admin_id); // 释放旧ID的内存
            admin->admin_id = strdup(arg); // 分配新ID的内存并复制
            break;
        case 2:
            free(admin->admin_name);
            admin->admin_name = strdup(arg);
            break;
        case 3:
            free(admin->admin_telephone);
            admin->admin_telephone = strdup(arg);
            break;
        case 4:
            free(admin->admin_password);
            admin->admin_password = strdup(arg);
            break;
        case 5:
            free(admin->admin_email);
            admin->admin_email = strdup(arg);
            break;
        default:
            printf("无效修改模式\n");
            break;
    }
    return admin;
}
//查询管理员信息
Admin* admin_find_by_id(Admin* head, char* id) {
    Admin* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->admin_id, id) == 0 ) {
            return temp;
        }
        temp = temp->next;
    }
    //printf("Not found Admin ID %s\n", id);
    return NULL; // 如果没有找到匹配的ID，返回NULL
}

char* admin_delete(Admin** head, char* id){
    Admin* target = admin_find_by_id(*head, id); // 调用 admin_find_by_id 来查找节点
    if (target != NULL) {
        char* temp=target->admin_id;
        Admin* prev = NULL;
        Admin* current = *head;
        // 查找要删除的节点的前一个节点
        while (current != target) {
            prev = current;
            current = current->next;
        }

        // 处理删除逻辑
        if (prev == NULL) {
            // 如果要删除的节点是头节点
            *head = current->next; // 更新头节点
        }
        else {
            // 如果要删除的节点不是头节点
            prev->next = current->next; // 断开连接
        }

        // 释放要删除的节点的内存
        free(current);
        return temp;
    }
}
void admin_free_list(Admin** head) {
    Admin* current = *head;
    Admin* next;

    while (current != NULL) {
        next = current->next; // 保存下一个节点的指针

        // 释放Cinema结构体
        //if (current->cinema != NULL) {
        //    cinema_free(current->cinema);
        //    current->cinema = NULL; //有助于避免野指针
        //}

        // 释放Admin结构体
        free(current->admin_id);
        free(current->admin_name);
        free(current->admin_telephone);
        free(current->admin_password);
        free(current->admin_email);
        free(current->cinema_id);
        free(current);

        current = next; // 移动到下一个节点
    }

    *head = NULL; // 将头指针设置为NULL，表示链表为空
}