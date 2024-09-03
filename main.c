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
        case 1://ѡ��������
            new_movie_list = for_admin_movie_sort(new_movie_list);//�����������
            break;
        case 2://ѡ����ɸѡ
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
Movie* for_admin_movie_sort(Movie* new_movie_list)//���������Ӳ˵�
{
    while (1)
    {
        //Movie* temp = new_movie_list;
        system("cls");
        display_admin_sort_menu();
        int option = get_user_input_int(5);
        //������(���򣩣��۸�(����)����������(����)����ʼʱ��(����)��ʣ��Ʊ��(����)
        switch (option)
        {
        case 1:
            new_movie_list=movie_operation_sort(new_movie_list, 1);
            printf("���������������");
            /*movie_list_free(temp);*/
            _sleep(1000);
            //temp = NULL;
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list,2);
            printf("���۸��������");
            //movie_list_free(temp);
            _sleep(1000);
            //temp = NULL;
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 3);
            printf("�����������������");
            //movie_list_free(temp);
            _sleep(1000);
            //temp = NULL;
            break;
        case 4:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("����ʼʱ���������");
            //movie_list_free(temp);
            _sleep(1000);
            //temp = NULL;
            break;
        case 5:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("��ʣ��Ʊ���������");
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

