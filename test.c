//
// Created by G on 2024/8/27.
//
//#include <synchapi.h>
#include "test.h"

int main(){
    int mode;
    hash_ini();
    load_file();

    //login ����

   /* do {
        mode =login();
    } while (!mode);
    if(mode==admin_mode)
    {
        printf("\nWelcome admin");
    }
    else if(mode==user_mode)
    {
        printf("\nWelcome user");
    }*/
    //sleep(100);
    
    //���ݷ�ӳʱ������

     // ��ʼ����ϣ��
    //Theater_hash_table* ht = theater_hash_table_create();
    Cinema* cinema = malloc(sizeof(Cinema));
    //cinema->cinema_id = strdup("Cinema1");
    cinema->my_theater = NULL;

    // ��������Ӿ�Ժ  
    Theater* theater1 = theater_create(theaterHashTable, "T1", "Theater One", 100, cinema, "Cinema1", "3D");
    Theater* theater2 = theater_create(theaterHashTable, "T2", "Theater Two", 150, cinema, "Cinema1", "IMAX");

    // ʵ����һЩMovie����  
    Movie* movie1 = movie_create(movieHashTable, "M001", "Inception", theater1, "2024-09-01 21:00", "2024-09-01 23:30", 50, 12.00, 0.90, "IMAX");
    Movie* movie2 = movie_create(movieHashTable, "M002", "Interstellar", theater2, "2024-09-01 18:00", "2024-09-01 21:00", 30, 10.00, 0.85, "Standard");
    Movie* movie3 = movie_create(movieHashTable, "M003", "The Dark Knight", theater1, "2024-09-02 11:00", "2024-09-02 13:45", 40, 11.50, 0.80, "IMAX");

    // ����һ������  
    Movie* head = NULL;
    movie_add_to_list(&head, movie1);
    movie_add_to_list(&head, movie2);
    movie_add_to_list(&head, movie3);

    // ��ӡ����ǰ�ĵ�Ӱ�б�  
    printf("Before sorting:\n");
    movie_show_all(head);

    // ����ӳʱ������  
    head = movie_sort_by_start_time(head);

    // ��ӡ�����ĵ�Ӱ�б�  
    printf("\nAfter sorting by start time:\n");
    movie_show_all(head);

    // �ͷ��ڴ棨��ȥ����ʵ�֣�������ʾ��  
    // ... free all allocated memory ...  

    return 0;
}
static int login()
{
    char password[20];char id[20];bool key=0;
    do {
        printf("Enter your ID:");
        scanf("%s",id);
        user_now= find_user_in_hash_table(userHashTable,id);
        admin_now= admin_find_by_id(admin_list,id);//ע�⿼����������
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
            orderHashTable,   // ������ϣ��
            userHashTable,    // �û���ϣ��
            movieHashTable,   // ��Ӱ��ϣ��
            &order_list,      // ��������
    };
    load_data_from_csv("order.csv",handle_order_data,context6);

}
