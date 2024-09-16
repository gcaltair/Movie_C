#include "main.h"

int main() {
    int mode;
    hash_ini();
    load_file();
    
    //user_now = find_user_in_hash_table(userHashTable, "U001");
    //admin_now = admin_find_by_id(admin_list, "A00001");
    //user_operation();
    //admin_operation();
    while (1)
    {
        system("cls");
        do
        {
            mode = login();
        }while(!mode);
        if (mode == admin_mode) admin_operation();
        else if (mode == user_mode) user_operation();
        if(user_now||admin_now) write_file();
    }
    
}

static void user_operation()
{
    while (1)
    {
        system("cls");
        display_user_greet();
        int option = get_user_input_int(4);
        switch (option)
        {
        case 1:
            user_purchase_system(filmHashTable, movieHashTable,orderHashTable, user_now, cinema_list, movie_list, &order_list);
            break;
        case 2:
            Film_recommend(film_list, movieHashTable, user_now, &order_list, orderHashTable, filmHashTable);
            break;
        case 3:
            order_system_for_user(user_now, orderHashTable, &order_list);
            break;
        case 4:
            order_show_all(order_list);
            //recharge_main();
            press_zero_to_continue();
            break;
        default:
            return;
            break;
        }
    }
}

static void admin_operation()
{
    while (1) {
        system("cls");
        admin_greet();
        int option = get_user_input_int(5);
        switch (option)
        {
        case 1:
            admin_order_manage(admin_now,theaterHashTable,movieHashTable,orderHashTable,order_list);
            break;
        case 2:
            admin_theater_manage(admin_now,&theater_list,theaterHashTable); 
            break;
        case 3:
            admin_movie_manage(film_list,filmHashTable,movieHashTable,theaterHashTable,&movie_list,admin_now);
            break;
        case 4:
            admin_modify_self_info(admin_now);
            break;
        default:
            write_movies_to_csv("Data\\movies.csv", movie_list);
            return;
        }
    }
}
static int login(){
    char password[20]; char id[20]; bool key = 0;
    do {
        printf("请输入您的ID:");
        scanf("%s", id);
        if (id=='\n') { printf("您输入的ID不存在\n"); _sleep(500); system("cls"); continue; }//对于回车特判
        user_now = find_user_in_hash_table(userHashTable, id);
        admin_now = admin_find_by_id(admin_list, id);//注意考虑重名问题
        if ((!user_now) && (!admin_now)) {
            printf("您输入的ID不存在\n");
            _sleep(500);
            system("cls");
        }
    } while ((!user_now) && (!admin_now));
    if(admin_now)
    if (admin_password_check(admin_now, admin_list)) return 2;
    if(user_now)
    if (user_password_check(user_now, userHashTable)) return 1;
    system("cls");
    return 0;
}
//哈希表初始化
static void hash_ini()
{
    userHashTable = user_hash_table_create();
    theaterHashTable = theater_hash_table_create();
    orderHashTable = order_hash_table_create();
    movieHashTable = movie_hash_table_create();
    filmHashTable = film_hash_table_create();
}

static void load_file() {
    void* context1[] = { userHashTable,&user_list };
    load_data_from_csv("Data\\users.csv", handle_user_data, context1);
    void* context2[] = { &film_list,filmHashTable };
    load_data_from_csv("Data\\films.csv", handle_film_data, context2);
    void* context3[] = { &cinema_list };
    load_data_from_csv("Data\\cinemas.csv", handle_cinema_data, context3);
    void* context4[] = { cinema_list,&admin_list };
    load_data_from_csv("Data\\admins.csv", handle_admin_data, context4);
    void* context5[] = { &theater_list,&cinema_list,theaterHashTable };
    load_data_from_csv("Data\\theaters.csv", handle_theater_data, context5);
    void* context6[] = { &movie_list,movieHashTable,theaterHashTable,filmHashTable };
    load_data_from_csv("Data\\movies.csv", handle_movie_data, context6);

    void* context7[] = {
            orderHashTable,   // 订单哈希表
            userHashTable,    // 用户哈希表
            movieHashTable,   // 电影哈希表
            &order_list,      // 订单链表
    };
    load_data_from_csv("Data\\orders.csv", handle_order_data, context7);
}
static void write_file()
{
    write_users_to_csv("users.csv", user_list);
    write_cinemas_to_csv("cinemas.csv", cinema_list);
    write_films_to_csv("films.csv", film_list);
    write_movies_to_csv("movies.csv", movie_list);
    write_orders_to_csv("orders.csv", order_list);
    write_theaters_to_csv("theaters.csv", theater_list);
    write_admins_to_csv("admins.csv", admin_list);
 
}

