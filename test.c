//
// Created by G on 2024/8/27.
//
//#include <synchapi.h>
#include "test.h"

int main(){
    int mode;
    hash_ini();
    load_file();

    
    //Seat_map_show(seat_map);

//    do {
//        mode =login();
//    } while (!mode);
//    if(mode==admin_mode)
//    {
//        printf("\nWelcome admin");
//    }
//    else if(mode==user_mode)
//    {
//        printf("\nWelcome user");
//    }
//    sleep(100);
}
static int login()
{
    char password[20];char id[20];bool key=0;
    do {
        printf("Enter your ID:");
        scanf("%s",id);
        user_now= find_user_in_hash_table(userHashTable,id);
        admin_now= admin_find_by_id(admin_list,id);//注意考虑重名问题
        if((!user_now)&&(!admin_now)) {
            printf("ID don't found\n");
            //Sleep(500);
            system("cls");
        }
    } while ((!user_now)&&(!admin_now));
    if(admin_password_check(admin_now,admin_list)) return 2;
    if(user_password_check(user_now,userHashTable)) return 1;
    system("cls");
    return 0;
}
static void hash_ini()
{
    userHashTable=user_hash_table_create();
    theaterHashTable=theater_hash_table_create();
    orderHashTable=order_hash_table_create();
    movieHashTable=movie_hash_table_create();
}
static void load_file()
{
    void* context1[]={userHashTable,&user_list};
    load_data_from_csv("users.csv",handle_user_data,context1);
    void* context2[]= {&cinema_list};
    load_data_from_csv("cinemas.csv",handle_cinema_data,context2);
    void *context3[]={cinema_list,&admin_list};
    load_data_from_csv("admins.csv",handle_admin_data,context3);
    void* context4[] = { &theater_list,&cinema_list,theaterHashTable };
    load_data_from_csv("theaters.csv", handle_theater_data, context4);
    void *context5[]={&movie_list,movieHashTable,theaterHashTable};
    load_data_from_csv("movies.csv",handle_movie_data,context5);
    
    void* context6[] = {
            orderHashTable,   // 订单哈希表
            userHashTable,    // 用户哈希表
            movieHashTable,   // 电影哈希表
            &order_list,      // 订单链表
    };
    load_data_from_csv("order.csv",handle_order_data,context6);

}
//修改用户信息
User* user_modify(User* head, char* id, int mode, char* arg) {
    User* user = user_find_by_id(head, id);
    if (user == NULL) {
        printf("The user is not existed!\n");
        return NULL; // 如果找不到用户，则直接返回
    }

    switch (mode) {
    case 1: // 修改用户ID
        free(user->userID); // 释放旧ID的内存
        user->userID = strdup(arg); // 分配新ID的内存并复制
        break;
    case 2: // 修改用户名
        free(user->user_name);
        user->user_name = strdup(arg);
        break;
    case 3: // 修改性别
        free(user->gender);
        user->gender = strdup(arg);
        break;
    case 4: // 修改电话
        free(user->telephone);
        user->telephone = strdup(arg);
        break;
    case 5: // 修改密码
        free(user->password);
        user->password = strdup(arg);
        break;
    case 6: // 修改邮箱
        free(user->email);
        user->email = strdup(arg);
        break;
    default:
        printf("Invalid modification mode\n");
        break;
    }
    return user;
}
