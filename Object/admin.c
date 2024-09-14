//
// Created by Y on 2024/8/27.
//

#include "admin.h"
#include "string.h"
#include "Cinema.h"
#include "stdio.h"
Admin* Admin_create(const char* id, const char* name, const char* telephone,
                    const char* password, const char* email, Cinema *cinema_,const char* cinema_id) {
    // ��̬�����ڴ��Admin�ṹ��
    Admin* admin = (Admin*)malloc(sizeof(Admin));
    if (admin == NULL) {
        printf("�ڴ����ʧ��.\n");
        return NULL;
    }

    // ��̬�����ڴ沢���Ʋ������ݵ��ṹ���ֶ�
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

    printf("����Ա ID: %s\n", admin->admin_id);
    printf("����: %s\n", admin->admin_name);
    printf("�绰: %s\n", admin->admin_telephone);
    printf("Password: %s\n", admin->admin_password);  // ע�⣺ʵ��ϵͳ��ͨ�������ӡ����
    printf("����: %s\n", admin->admin_email);
    cinema_show(admin->cinema);
    printf("\n");

}
//�޸��û���Ϣ
Admin* admin_modify(Admin* admin, int modify_mode, char* arg) {
    if (admin == NULL) {
        printf("����Ա������!");
        return NULL; // ����Ҳ�������Ա����ֱ�ӷ���
    }

    switch (modify_mode) {
        case 1:
            // ͨ�����Ƽ��޸�ID����Ϊ�������԰����˹���
            free(admin->admin_id); // �ͷž�ID���ڴ�
            admin->admin_id = strdup(arg); // ������ID���ڴ沢����
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
            printf("��Ч�޸�ģʽ\n");
            break;
    }
    return admin;
}
//��ѯ����Ա��Ϣ
Admin* admin_find_by_id(Admin* head, char* id) {
    Admin* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->admin_id, id) == 0 ) {
            return temp;
        }
        temp = temp->next;
    }
    //printf("Not found Admin ID %s\n", id);
    return NULL; // ���û���ҵ�ƥ���ID������NULL
}

char* admin_delete(Admin** head, char* id){
    Admin* target = admin_find_by_id(*head, id); // ���� admin_find_by_id �����ҽڵ�
    if (target != NULL) {
        char* temp=target->admin_id;
        Admin* prev = NULL;
        Admin* current = *head;
        // ����Ҫɾ���Ľڵ��ǰһ���ڵ�
        while (current != target) {
            prev = current;
            current = current->next;
        }

        // ����ɾ���߼�
        if (prev == NULL) {
            // ���Ҫɾ���Ľڵ���ͷ�ڵ�
            *head = current->next; // ����ͷ�ڵ�
        }
        else {
            // ���Ҫɾ���Ľڵ㲻��ͷ�ڵ�
            prev->next = current->next; // �Ͽ�����
        }

        // �ͷ�Ҫɾ���Ľڵ���ڴ�
        free(current);
        return temp;
    }
}
void admin_free_list(Admin** head) {
    Admin* current = *head;
    Admin* next;

    while (current != NULL) {
        next = current->next; // ������һ���ڵ��ָ��

        // �ͷ�Cinema�ṹ��
        //if (current->cinema != NULL) {
        //    cinema_free(current->cinema);
        //    current->cinema = NULL; //�����ڱ���Ұָ��
        //}

        // �ͷ�Admin�ṹ��
        free(current->admin_id);
        free(current->admin_name);
        free(current->admin_telephone);
        free(current->admin_password);
        free(current->admin_email);
        free(current->cinema_id);
        free(current);

        current = next; // �ƶ�����һ���ڵ�
    }

    *head = NULL; // ��ͷָ������ΪNULL����ʾ����Ϊ��
}