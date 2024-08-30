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
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // 动态分配内存并复制参数内容到结构体字段
    admin->admin_id = strdup(id);
    admin->admin_name = strdup(name);
    admin->admin_telephone = strdup(telephone);
    admin->admin_password = strdup(password);
    admin->admin_email = strdup(email);
    admin->cinema_id=strdup(cinema_id);
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

    printf("Admin ID: %s\n", admin->admin_id);
    printf("Name: %s\n", admin->admin_name);
    printf("Telephone: %s\n", admin->admin_telephone);
    printf("Password: %s\n", admin->admin_password);  // 注意：实际系统中通常不会打印密码
    printf("Email: %s\n", admin->admin_email);
    printf("\n");

}
//修改用户信息
void modify_personalinfo(); 
//查询管理员信息
Admin* admin_find_by_id(Admin* head, char* id) {
    Admin* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->admin_id, id) == 0 ) {
            return temp;
        }
        temp = temp->next;
    }
    printf("Not found Admin ID %s\n", id);
    return NULL; // 如果没有找到匹配的ID，返回NULL
}