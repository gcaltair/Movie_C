#include "main.h"

int main() {
    int mode;
    printf("test\n");
    hash_ini();
    load_file();
    
    user_now = find_user_in_hash_table(userHashTable, "U001");
    admin_now = admin_find_by_id(admin_list, "A00001");
    user_operation();
    //while (1)
    //{
    //    system("cls");
    //    do
    //    {
    //        mode = login();
    //    }while(!mode);
    //    if (mode == admin_mode) admin_operation();
    //    else if (mode == user_mode) user_operation();
    //    if(user_now||admin_now) write_file();
    //}
    
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
            user_purchase_ticket(filmHashTable, movieHashTable,orderHashTable, user_now, cinema_list, movie_list, &order_list);
            break;
        case 2:
            printf("推荐影片:\n");
            Film* hot_film = hot_films(film_list);
            film_print(hot_film);
            printf("是否进入购票>(1/0)");
            if (!get_user_input_int(1)) break;
            Movie* choosed_movie = search_target_film_and_choose_movie(hot_film,movieHashTable,user_now);
            if (!choosed_movie) break;
            press_zero_to_continue();
            break;
        case 3:
            printf("请选择您的功能:\n1.查看订单.\n2.付款\n3.取消订单\n4.退款\n\n0.退出\n");
            int cer = get_user_input_int(4);
            switch (cer) {
            case 1:
                printf("请输入您的userID:\n");
                char userID[100];
                while (1) {
                    if (scanf("%99s", userID) != 1) { // 使用宽度限制来防止缓冲区溢出  
                        printf("输入无效，请重新输入。\n");
                        while (getchar() != '\n'); // 清除输入缓冲区中的剩余字符  
                        continue;
                    }
                    break;
                }
                User* usr = user_find_by_id(user_list, userID);
                if (usr == NULL) {
                    printf("您输入的userID无效.\n");
                    break;
                }
                else {
                    order_list_show_by_user(usr, orderHashTable);
                    press_zero_to_continue();
                    break;
                }
            case 2:
                process_pay_main();
                press_zero_to_continue();
                break;
            case 3:
                order_cancle_main();
                press_zero_to_continue();
                break;
            case 4:
                ticket_refund_main();
                press_zero_to_continue();
                break;
            case 0:
                 break;
            }
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
        case 0:
            return;
        case 1:
            admin_order_manage(admin_now,theaterHashTable,movieHashTable,orderHashTable,order_list);
            break;
        case 2:
            admin_theater_manage(admin_now,theater_list,theaterHashTable); 
            break;
        case 3:
            admin_movie_manage(film_list,filmHashTable,movieHashTable,theaterHashTable,movie_list,admin_now);
            break;
        case 4:
            admin_modify_self_info(admin_now);
            break;
        default:
            return;
        }
    }
}







//付款
//return 1 ： 付款成功
//       2 ： 付款失败
int process_pay_main_order(Order* order) {
    if (order->status != 2) {// 检查订单状态并尝试付款
        printf("订单状态不合法.\n");
        return 2;
    }
    if (balance_check(order, orderHashTable) == 1) { // 检查余额并付款  
        if (process_pay(order, order->movie->seat_map, orderHashTable) == 0) {
            printf("订单查询失败.\n");
            return 0;
        }
        else {
            printf("付款成功.\n");
            return 1;
        }
    }
    else {
        while (balance_check(order, orderHashTable) == 0) {
            printf("余额不足,您还需充值%f元`.继续充值请按1，放弃充值请按0\n", get_debt(order, orderHashTable));
            int cer = get_user_input_int(1);
            if (cer) {
                if (balance_check(order, orderHashTable) == 0) {
                    continue;
                }
                else {
                    process_pay(order, order->movie->seat_map, orderHashTable);
                    printf("付款成功.\n");
                    return 1;
                }
            }
            return 2;
        }
    }
}

//充值
void recharge_main(void) {
    

    printf("输入金额");
    double money = get_user_input_double(50, 5000);
    scanf("%lf", &money);
        
    recharge(user_now, money);
    
}
//用户根据订单付款
int process_pay_main(void) {
    char orderID[100]; // 假设订单ID不会超过99个字符  
    printf("请输入您要取消的orderID.\n");
    while (1) {
        if (scanf("%99s", orderID) != 1) { // 使用宽度限制来防止缓冲区溢出  
            printf("输入无效，请重新输入。\n");
            while (getchar() != '\n'); // 清除输入缓冲区中的剩余字符  
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("您输入的订单号无效.\n");
        return 0;
    }
    Order* order = find_order_in_hash_table(orderHashTable, orderID);
    return process_pay_main_order(order);
}  

//取消订单
//return 0 ： 输入无效订单或用户信息获取失败
//       1 ： 取消成功
//       2 ： 取消失败  
int order_cancle_main( ) {
    printf("请输入您要取消的orderID.\n");
    char orderID[20];
    while (1) {
        if (scanf("%s", orderID) != 1) {
            printf("输入无效，请重新输入。\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("您输入的订单号无效.\n");
        return 0;
    }
    else {
        Order* order = find_order_in_hash_table(orderHashTable, orderID);
        if (order->status != 2) {
            printf("订单状态不合法,取消失败.\n");// 检查订单状态并尝试取消  
            return 2;
        }
        else {
            order_cancel(order);
            printf("取消成功.\n");
            return 1;
        }
    }
}

//退款
//return 0 ： 输入无效订单或用户信息获取失败
//       1 ： 退款成功
//       2 ： 退款失败  
int ticket_refund_main(  ) {
    printf("请输入您退款的orderID.\n");
    char* orderID;
    while (1) {
        if (scanf("%s", orderID) != 1) {
            printf("输入无效，请重新输入。\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("您输入的订单号无效.\n");
        return 0;
    }
    else {
        Order* order = find_order_in_hash_table(orderHashTable, orderID);
        if (order->status != 1) {    // 检查订单状态并尝试退款
            printf("订单状态不合法.\n");
            return 2;
        }
        if (order->status != 1) {
            printf("退款失败.\n");
            return 2;
        }
        else {
            return ticket_refund(order, order->movie->seat_map, orderHashTable);
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

