//
// Created by Y on 2024/8/27.
//

#include "admin.h"
#include "string.h"

Admin* Admin_add(const char* id, const char* name, const char* telephone,
                 const char* password, const char* email, Cinema * cinema_) {
    // ��̬�����ڴ��Admin�ṹ��
    Admin* admin = (Admin*)malloc(sizeof(Admin));
    if (admin == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // ��̬�����ڴ沢���Ʋ������ݵ��ṹ���ֶ�
    admin->admin_ID = strdup(id);
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

    printf("Admin ID: %s\n", admin->admin_ID);
    printf("Name: %s\n", admin->admin_name);
    printf("Telephone: %s\n", admin->admin_telephone);
    printf("Password: %s\n", admin->admin_password);  // ע�⣺ʵ��ϵͳ��ͨ�������ӡ����
    printf("Email: %s\n", admin->admin_email);
    cinema_show(admin->cinema);

}

void modify_personalinfo(); //�޸��û���Ϣ