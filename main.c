#include "main.h"
#include "main.h"
static void admin_order_manage();
int main() {
    int mode;
    hash_ini();
    load_file();
    admin_now = admin_find_by_id(admin_list, "A001");
    admin_opreation();
    /*while (1) {
        system("cls");
        do {
            mode = login();
        } while (!mode);
        if (mode == admin_mode)
        {
            admin_opreation();
        }
        else if (mode == user_mode)
        {
            printf("\nWelcome user");
        }
    }*/
}
static void admin_opreation()
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
            admin_order_manage();
            break;

        default:
            return;
        }
    }
}
static void admin_order_manage()
{
    while (1)
    {
        system("cls");
        admin_order_manage_greet();
        int option = get_user_input_int(2);
        switch (option)
        {
        case 1:
            admin_view_order();
        case 2:

        default:
            return;
        }
    }

}
static void admin_view_order(){
    Movie* my_cinema_movie_list = movie_list_create_by_cinema(admin_now->cinema, theaterHashTable, movieHashTable);
    Movie* new_movie_list = movie_list;
    Movie* free_temp = NULL;
    Movie* para_temp = NULL;
    while (1)
    {
        system("cls");
        display_movie_operate_main_menu();
        int option = get_user_input_int(3);
        switch (option)
        {
        case 1://选择了排序
            new_movie_list = for_admin_movie_sort(new_movie_list);//进入排序界面
            break;
        case 2://选择了筛选
            para_temp = new_movie_list;
            free_temp = new_movie_list;
            break;
        case 3:
            movie_show_all(new_movie_list);
            _sleep(10000);
            break;
        default:
            return;
        }
    }  
}
Movie* for_admin_movie_sort(Movie* new_movie_list)//进入排序子菜单
{
    while (1)
    {
        //Movie* temp = new_movie_list;
        system("cls");
        display_admin_sort_menu();
        int option = get_user_input_int(5);
        //上座率(降序），价格(升序)，场次收入(降序)，开始时间(升序)，剩余票数(升序)
        switch (option)
        {
        case 1:
            new_movie_list=movie_operation_sort(new_movie_list, 1);
            printf("按上座率排序完成");
            /*movie_list_free(temp);*/
            _sleep(1000);
            //temp = NULL;
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list,2);
            printf("按价格排序完成");
            //movie_list_free(temp);
            _sleep(1000);
            //temp = NULL;
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 3);
            printf("按场次收入排序完成");
            //movie_list_free(temp);
            _sleep(1000);
            //temp = NULL;
            break;
        case 4:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("按开始时间排序完成");
            //movie_list_free(temp);
            _sleep(1000);
            //temp = NULL;
            break;
        case 5:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("按剩余票数排序完成");
            //movie_list_free(temp);
            _sleep(1000);
            //temp = NULL;
            break;
        default:
            return new_movie_list;
        }
    }
}
Movie* for_admin_movie_filter(Movie* new_movie_list)
{
    while (1)
    {

    }
}
Movie* movie_choose(Movie* head, Movie_hash_table* movie_hash_table)
{

}
static int login()
{
    char password[20]; char id[20]; bool key = 0;
    do {
        printf("Enter your ID:");
        scanf("%s", id);
        //不知咋办
        //if (id=='\n') { printf("ID don't found\n"); _sleep(500); system("cls"); continue; }
        user_now = find_user_in_hash_table(userHashTable, id);
        admin_now = admin_find_by_id(admin_list, id);//注意考虑重名问题
        if ((!user_now) && (!admin_now)) {
            printf("ID don't found\n");
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
static void hash_ini()
{
    userHashTable = user_hash_table_create();
    theaterHashTable = theater_hash_table_create();
    orderHashTable = order_hash_table_create();
    movieHashTable = movie_hash_table_create();
    filmHashTable = film_hash_table_create();
}
static void load_file()
{
    void* context1[] = { userHashTable,&user_list };
    load_data_from_csv("D:\\cccc\\Data\\users.csv", handle_user_data, context1);
    void* context2[] = { &film_list,filmHashTable };
    load_data_from_csv("D:\\cccc\\Data\\films.csv", handle_film_data, context2);
    void* context3[] = { &cinema_list };
    load_data_from_csv("D:\\cccc\\Data\\cinemas.csv", handle_cinema_data, context3);
    void* context4[] = { cinema_list,&admin_list };
    load_data_from_csv("D:\\cccc\\Data\\admins.csv", handle_admin_data, context4);
    void* context5[] = { &theater_list,&cinema_list,theaterHashTable };
    load_data_from_csv("D:\\cccc\\Data\\theaters.csv", handle_theater_data, context5);
    void* context6[] = { &movie_list,movieHashTable,theaterHashTable,filmHashTable };
    load_data_from_csv("D:\\cccc\\Data\\movies.csv", handle_movie_data, context6);

    void* context7[] = {
            orderHashTable,   // 订单哈希表
            userHashTable,    // 用户哈希表
            movieHashTable,   // 电影哈希表
            &order_list,      // 订单链表
    };
    load_data_from_csv("D:\\cccc\\Data\\order.csv", handle_order_data, context7);
}

