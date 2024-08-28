#ifndef MOVIE_C_ADMIN_H
#define MOVIE_C_ADMIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Cinema.h"

//����Ա�ṹ��
typedef struct {
    char* admin_id;
    char* admin_name;
    char* admin_telephone;
    char* admin_password;
    char* admin_email;
    Cinema* cinema;
}Admin;
Admin* Admin_add(const char* id, const char* name, const char* telephone,
                 const char* password, const char* email, Cinema* cinema);
void admin_show(const Admin* admin);
//�޸��û���Ϣ
void modify_personalinfo(); 
//��ѯ����Ա��Ϣ
Admin* find_admin(char* name);
//�޸Ĺ���Ա��Ϣ
void modify_admin(Admin* admin);

#endif //MOVIE_C_ADMIN_H