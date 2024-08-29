#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

// �����û�
User* user_create(const char* userID, const char* name, const char* gender, const char* telephone,
                  const char* password, const char* email, double balance) {
    User* new_user = (User*)malloc(sizeof(User));
    if (new_user == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    new_user->userID = strdup(userID);
    new_user->user_name = strdup(name);
    new_user->gender = strdup(gender);
    new_user->telephone = strdup(telephone);
    new_user->password = strdup(password);
    new_user->email = strdup(email);
    new_user->user_balance = balance;
    new_user->next = NULL;

    return new_user;
}
// ��������ͷ�ڵ�
User* user_create_list(User* new_user) {
    new_user->next = NULL;
    return new_user;
}

// ���һ��Ԫ�ص�����ͷ�巨
void user_add_to_list(User** head, User* new_user) {
    if (*head == NULL) {
        *head = new_user;
        return;
    }

    User* temp = new_user;
    temp->next=(*head);
    (*head)=temp;
}

// ֱ�����һ���û�������
void user_direct_add_to_list(User** head, const char* userID, const char* name, const char* gender,
                             const char* telephone, const char* password, const char* email, double balance) {
    User* new_user = user_create(userID, name, gender, telephone, password, email, balance);
    user_add_to_list(head, new_user);
}

// ͨ���û�ID�����û�
User* user_find_by_id(User* head, const char* userID) {
    while (head != NULL) {
        if (strcmp(head->userID, userID) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// ��ʾ�����û���Ϣ
void user_show(const User* user) {
    if (user == NULL) {
        printf("User not found.\n");
        return;
    }
    printf("UserID: %s\n", user->userID);
    printf("Name: %s\n", user->user_name);
    printf("Gender: %s\n", user->gender);
    printf("Telephone: %s\n", user->telephone);
    printf("Email: %s\n", user->email);
    printf("Balance: %.2f\n", user->user_balance);
}

// ��ʾ�����û���Ϣ
void user_show_all(User* head) {
    while (head != NULL) {
        user_show(head);
        printf("\n");
        head = head->next;
    }
}

// �ͷ��û�����ռ�õ��ڴ�
void user_free(User* head) {
    while (head != NULL) {
        User* temp = head;
        head = head->next;

        free(temp->userID);
        free(temp->user_name);
        free(temp->gender);
        free(temp->telephone);
        free(temp->password);
        free(temp->email);
        free(temp);
    }
}

