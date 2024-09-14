#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "../hash.txt"
#include "../Structure File/linked_list.h"

// �����û�
User* user_create(User_hash_table * hashTable,const char* userID, const char* name, const char* gender, const char* telephone,
                  const char* password, const char* email, double balance) {
    User* new_user = (User*)malloc(sizeof(User));
    if (new_user == NULL) {
        printf("�ڴ����ʧ��\n");
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
    new_user->hash_next=NULL;
//idȷ�������
    insert_user_to_hash_table(hashTable,new_user);
    new_user->my_order=NULL;
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
        (*head) = new_user;
        return;
    }
    User* temp = new_user;
    temp->next=(*head);
    (*head)=new_user;
}

// ֱ�����һ���û�������
void user_direct_add_to_list(User_hash_table * hashTable,User** head, const char* userID, const char* name, const char* gender,
                             const char* telephone, const char* password, const char* email, double balance) {
    User* new_user = user_create(hashTable,userID, name, gender, telephone, password, email, balance);
    if(new_user==NULL){
        printf("����û�������ʧ��!");
        return;
    }
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
    printf("�û�ID: %s\n", user->userID);
    printf("����: %s\n", user->user_name);
    printf("�Ա�: %s\n", user->gender);
    printf("�绰��: %s\n", user->telephone);
    printf("����: %s\n", user->email);
    printf("���: %.2f\n", user->user_balance);
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
void user_free_list(User* head) {
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

// ��ʼ����ϣ�������е�ָ������ΪNULL
// ��������ʼ��һ��User_hash_table
User_hash_table* user_hash_table_create() {
    // ��̬�����ڴ��User_hash_table�ṹ
    User_hash_table* ht = (User_hash_table*)malloc(sizeof(User_hash_table));
    if (!ht) {
        // ����ڴ����ʧ�ܣ�����NULL
        return NULL;
    }
    // ��ʼ����ϣ�������е�ָ������ΪNULL
    user_hash_table_init(ht);
    return ht;
}
void user_hash_table_init(User_hash_table* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// ���û������ϣ��ʹ������ַ�������ϣ��ͻ
void insert_user_to_hash_table(User_hash_table* ht, User* user) {
    unsigned int index = hash(user->userID, strlen(user->userID), 0x9747b28c); // ʹ��MurmurHash2��������
    //printf("Inserting user %s at index %u\n", user->userID, index);
    user->hash_next = ht->table[index];  // ����ǰ�Ĺ�ϣ����������Ԫ�ط������û��ĺ���
    ht->table[index] = user;        // �����û����������ͷ��
}

// �ڹ�ϣ���в����û���ͨ��userID����
User* find_user_in_hash_table(User_hash_table* ht, const char* userID) {
    unsigned int index = hash(userID, strlen(userID), 0x9747b28c);
    User* user = ht->table[index];
    while (user) {
        if (strcmp(user->userID, userID) == 0) {
            return user;  // �ҵ��û�������ָ��
        }
        user = user->hash_next;  // �������������е���һ���û�
    }
    return NULL;  // ���δ�ҵ�������NULL
}
void user_delete(User **head, const char *user_id) {
    User* current = *head;
    User* previous = NULL;

    while (current != NULL && strcmp(current->userID, user_id) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("δ�����û�\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    }
    else {
        previous->next = current->next;
    }

    free(current->userID);
    free(current->user_name);
    free(current->gender);
    free(current->telephone);
    free(current->password);
    free(current->email);
    free(current);

    printf("�û�ɾ���ɹ�.\n");
}

//�޸��û���Ϣ
User* user_modify(User* head, char* id, int mode, char* arg) {
    User* user = user_find_by_id(head, id);
    if (user == NULL) {
        printf("�û�������!\n");
        return NULL; // ����Ҳ����û�����ֱ�ӷ���
    }

    switch (mode) {
    case 1: // �޸��û�ID
        free(user->userID); // �ͷž�ID���ڴ�
        user->userID = strdup(arg); // ������ID���ڴ沢����
        break;
    case 2: // �޸��û���
        free(user->user_name);
        user->user_name = strdup(arg);
        break;
    case 6: // �޸��Ա�
        free(user->gender);
        user->gender = strdup(arg);
        break;
    case 4: // �޸ĵ绰
        free(user->telephone);
        user->telephone = strdup(arg);
        break;
    case 5: // �޸�����
        free(user->password);
        user->password = strdup(arg);
        break;
    case 3: // �޸�����
        free(user->email);
        user->email = strdup(arg);
        break;
    default:
        printf("�����޸�ģʽ\n");
        break;
    }
    return user;
}

