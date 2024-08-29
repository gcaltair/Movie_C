//
// Created by Y on 2024/8/27.
//

#include "admin.h"
#include "string.h"
#include "Cinema.h"
#include "stdio.h"
Admin* Admin_add(const char* id, const char* name, const char* telephone,
                 const char* password, const char* email, Cinema * cinema_) {
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
    admin->cinema=cinema_;

    return admin;
}
void admin_show(const Admin *admin) {
    if (admin == NULL) {
        printf("Admin data is NULL.\n");
        return;
    }

    printf("Admin ID: %s\n", admin->admin_id);
    printf("Name: %s\n", admin->admin_name);
    printf("Telephone: %s\n", admin->admin_telephone);
    printf("Password: %s\n", admin->admin_password);  // 注意：实际系统中通常不会打印密码
    printf("Email: %s\n", admin->admin_email);
    cinema_show(admin->cinema);

}
//修改用户信息
void modify_personalinfo(); 
//查询管理员信息
Admin* find_admin(char* name) {
    Admin *admin = (Admin *) malloc(sizeof(Admin));
    if (admin == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    //return admin;
    //遍历id计算管理员个数
    int count = 0;
    int i = 0;
    if (admin[i].admin_id) {
        i++;
        count++;
    }
    //通过id查找管理员信息
    char search_adminid[50];
    int k = 0;
    printf("Enter admin id to update: ");
    scanf("%49s", search_adminid);
    for (int j = 0; j < count; j++) {
        if (strcmp(admin[j].admin_id, search_adminid) == 0) {
            //找到管理员,输出id，name等
            printf("%s %s", admin->admin_id, admin->admin_name);
            k++;
        }
    }
    if (k == 0) {
        printf("The admin is not existed!");
    }

//修改管理员信息
    void modify_admin(Admin *admin);

}