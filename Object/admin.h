#ifndef MOVIE_C_ADMIN_H
#define MOVIE_C_ADMIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Cinema Cinema;
//����Ա�ṹ��
typedef struct Admin{
    char* admin_id;
    char* admin_name;
    char* admin_telephone;
    char* admin_password;
    char* admin_email;
    char *cinema_id;
    struct Cinema* cinema;
    struct Admin* next;
}Admin;
//�����޸Ĺ���Ա�Ĺ��ܵļ���mode����ö��
Admin* Admin_create(const char* id, const char* name, const char* telephone,
                    const char* password, const char* email,Cinema *cinema_,const char* cinema_id);
void admin_add_to_list(Admin** head, Admin* new_admin);
void admin_show(const Admin* admin);
//�޸��û���Ϣ
void admin_show_all(Admin* head);
//��ѯ����Ա��Ϣ
Admin* admin_find_by_id(Admin* head, char* id);
//�޸Ĺ���Ա��Ϣ
Admin* admin_modify(Admin* admin, int mode, char* arg);
char* admin_delete(Admin** head, char* id);
void admin_free_list(Admin** head);
#endif //MOVIE_C_ADMIN_H