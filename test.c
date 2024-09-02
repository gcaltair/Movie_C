//
// Created by G on 2024/8/27.
//
//#include <synchapi.h>
#include "test.h"


int main(){
    int mode;
    hash_ini();
    load_file();
    //film_show_all(film_list);
    //film_show(find_film_in_hash_table_by_id(filmHashTable, "FLM001"));
    //Seat_map_show(seat_map);

    do {
        mode =login();
    } while (!mode);
    if(mode==admin_mode)
    {
        printf("\nWelcome admin");
    }
    else if(mode==user_mode)
    {
        printf("\nWelcome user");
    }
    
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
            _sleep(500);
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
    filmHashTable = film_hash_table_create();
}
static void load_file()
{
    void* context1[]={userHashTable,&user_list};
    load_data_from_csv("D:\\cccc\\Data\\users.csv",handle_user_data,context1);
    void* context2[] = { &film_list,filmHashTable };
    load_data_from_csv("D:\\cccc\\Data\\films.csv", handle_film_data, context2);
    void* context3[] = { &cinema_list };
    load_data_from_csv("D:\\cccc\\Data\\cinemas.csv", handle_cinema_data, context3);
    void *context4[]={cinema_list,&admin_list};
    load_data_from_csv("D:\\cccc\\Data\\admins.csv",handle_admin_data,context4);
    void* context5[] = { &theater_list,&cinema_list,theaterHashTable };
    load_data_from_csv("D:\\cccc\\Data\\theaters.csv", handle_theater_data, context5);
    void *context6[]={&movie_list,movieHashTable,theaterHashTable,filmHashTable};
    load_data_from_csv("D:\\cccc\\Data\\movies.csv",handle_movie_data,context6);
    
    void* context7[] = {
            orderHashTable,   // 订单哈希表
            userHashTable,    // 用户哈希表
            movieHashTable,   // 电影哈希表
            &order_list,      // 订单链表
    };
    load_data_from_csv("D:\\cccc\\Data\\order.csv",handle_order_data,context7);


}
