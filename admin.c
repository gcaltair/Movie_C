//
// Created by Y on 2024/8/27.
//

#include "admin.h"
bool login()
{
    return true;
}
User* Admin_add() {
    // ��̬�����ڴ����ڱ���һ�� User �ṹ��
    Admin* newAdmin = (Admin*)malloc(sizeof(admin));
    if (newAdmin == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // ��̬����ͳ�ʼ�������ֶ�
    newAdmin->admin_ID = (char*)malloc(50 * sizeof(char));
    newAdmin->admin_name = (char*)malloc(50 * sizeof(char));
    newAdmin->admin_password = (char*)malloc(10 * sizeof(char));
    newAdmin->admin_telephone = (char*)malloc(20 * sizeof(char));
    newAdmin->admin_email = (char*)malloc(50 * sizeof(char));
    newAdmin->admin_cinema; = (char*)malloc(50 * sizeof(char));

    if (!newAdmin->admin_ID || !newAdmin->admin_name || !newAdmin->admin_password ||
        !newAdmin->admin_telephone || !newAdmin->admin_email || !newAdmin->admin_cinema) {
        printf("Memory allocation for fields failed!\n");
        free(newAdmin); // �ͷŷ�����ڴ�
        return NULL;
    }

    // ��ȡ�û����벢����洢�ڽṹ����
    printf("Enter Admin ID: ");
    scanf("%49s", newAdmin->admin_ID

    printf("Enter Admin Name: ");
    scanf("%49s", newAdmin->admin_name);

    printf("Enter Admin Password: ");
    scanf("%9s", newAdmin->admin_password);

    printf("Enter Telephone: ");
    scanf("%19s", newAdmin->admin_telephone);

    printf("Enter email: ");
    scanf("%49s", newAdmin->admin_email);

    printf("Enter cinema: ");
    scanf("%49s", newAdmin->admin_cinema);

    return newAdmin;
}
void modify_personalinfo(); //�޸��û���Ϣ