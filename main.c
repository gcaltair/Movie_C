#include "main.h"

int main() {
    int mode;
    hash_ini();
    load_file();
    order_show_mini(user_list,orderHashTable);
    /*while (1) {
        do {
            mode = login();
        } while (!mode);
        if (mode == admin_mode)
        {
            system("cls");
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
        admin_greet();
        int option = get_user_input_int(5);
        switch (option)
        {
        case 0:
            return;
        case 1:
            admin_order_manage(admin_now,movie_list);
        

        default:
            break;
        }
    }
}
static int login()
{
    char password[20]; char id[20]; bool key = 0;
    do {
        printf("Enter your ID:");
        scanf("%s", id);
        //��֪զ��
        //if (id=='\n') { printf("ID don't found\n"); _sleep(500); system("cls"); continue; }
        user_now = find_user_in_hash_table(userHashTable, id);
        admin_now = admin_find_by_id(admin_list, id);//ע�⿼����������
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
            orderHashTable,   // ������ϣ��
            userHashTable,    // �û���ϣ��
            movieHashTable,   // ��Ӱ��ϣ��
            &order_list,      // ��������
    };
    load_data_from_csv("D:\\cccc\\Data\\order.csv", handle_order_data, context7);


}
void admin_greet()
{
    printf("*************************************************\n");
    printf("*               ��ӭʹ�õ�ӰԺ����ϵͳ          *\n");
    printf("*************************************************\n");
    printf("* 1. ��������                                   *\n");
    printf("* 2. Ӱ������                                   *\n");
    printf("* 3. ���ι���                                   *\n");
    printf("* 4. ������Ϣ����                               *\n");
    printf("* 5. �û���Ϣ����                               *\n");
    printf("*                                               *\n");
    printf("* 0.�˳�                                        *\n");
    printf("*************************************************\n");
}