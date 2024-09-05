#include "main.h"
static void admin_order_manage();
int main() {
    int mode;
    printf("test\n");
    hash_ini();
    load_file();
    admin_now = admin_find_by_id(admin_list, "A001"); 

    
    admin_opreation();
    //while (1) {
    //    system("cls");
    //    do {
    //        mode = login();
    //    } while (!mode);
    //    if (mode == admin_mode)
    //    {
    //        admin_opreation();
    //    }
    //    else if (mode == user_mode)
    //    {
    //        printf("\nWelcome user");
    //    }
    //}
}
static void admin_opreation()
{
    while (1) {
        //system("cls");
        admin_greet();
        int option = get_user_input_int(5);
        switch (option)
        {
        case 0:
            return;
        case 1:
            admin_order_manage();
            break;
        case 2:
            admin_theater_manage(); 
            break;
        case 3:
            admin_movie_manage();
            break;
        case 4:
            movie_show_all(movie_list);
        default:
            return;
        }
    }
}

static void admin_movie_manage()//��Ƭ����
{
    while (1)
    {
        //system("cls");
        display_admin_movie_manage_greet();
        int option = get_user_input_int(3);
        switch (option)
        {
        case 1:
            Film * film_choosed2 = film_choose(film_list, filmHashTable);
            int add_status2 = admin_auto_find_movie_to_theater(admin_now->cinema, film_choosed2, theaterHashTable, movieHashTable, movie_list);
            switch (add_status2)
            {
            case 1:
                printf("������ӳɹ�\n"); break;
            case 2:
                printf("���ݳ���...\n"); break;
            case 0:
                printf("��ȡ�����\n"); break;
            }
            press_zero_to_continue();
            break;
        case 2:
            Movie * movie_list_new = movie_list_create_by_cinema(admin_now->cinema,theaterHashTable,movieHashTable);
            movie_list_print(movie_list_new);
            press_zero_to_continue();
            movie_list_free(movie_list_new);
            break;
        case 3:
            Film* film_choosed = film_choose(film_list,filmHashTable);
            if (!film_choosed) break;
            Theater* theater_new_list = theater_list_create_by_cinema(admin_now->cinema, theaterHashTable);
            Theater* theater_choosed = theater_choose_for_admin(theater_new_list,theaterHashTable);
            if (!theater_choosed) break;
            
            int add_status = admin_add_a_movie_to_theater(theater_choosed, film_choosed, movie_list, movieHashTable);
            switch (add_status)
            {
            case 1:
                printf("������ӳɹ�\n"); break;
            case 2:
                printf("���ݳ���...\n"); break;
            case 0:
                printf("��ȡ�����\n"); break;
            }
            press_zero_to_continue();
            theater_free_copied_list(theater_new_list);
            theater_new_list = NULL;
            break;
        default:
            return;
            break;
        }
    }
}
static void admin_theater_manage()//theater��ɾ��û��
{
    while (1)
    {
        //system("cls");
        admin_theater_manage_greet();
        int option = get_user_input_int(3);
        switch (option)
        {
        case 1:
            int add_status=admin_add_a_theater(admin_now,theater_list,theaterHashTable);
            switch (add_status)
            {
            case 1:
                printf("Ӱ����ӳɹ�\n"); break;
            case 2:
                printf("���ݳ���...\n"); break;
            case 0:
                printf("��ȡ�����\n"); break;
            }
            press_zero_to_continue();
            break;
        case 2:
            Linked_string_list * head = admin_now->cinema->my_theater;
            while (head)
            {
                theater_print(find_theater_in_hash_table(theaterHashTable,head->id));
                head = head->next;
            }
            printf("��չʾ����Ӱ��\n");
            press_zero_to_continue();
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
        //system("cls");
        admin_order_manage_greet();
        int option = get_user_input_int(2);
        switch (option)
        {
        case 1:
            admin_view_and_count_order();
        case 2:
            
        default:
            return;
        }
    }

}

static void admin_view_and_count_order(){
    
    Movie* new_movie_list = movie_list_create_by_cinema(admin_now->cinema, theaterHashTable, movieHashTable);
    
    while (1)
    {
        //system("cls");
        display_movie_operate_main_menu();
        int option = get_user_input_int(4);
        switch (option)
        {
        case 1://ѡ��������
            new_movie_list = for_admin_movie_sort(new_movie_list);//�����������
            break;
        case 2://ѡ����ɸѡ
            new_movie_list= for_admin_movie_filter(new_movie_list);
            break;
        case 3:
            Movie * movie_choice = movie_choose(new_movie_list,movieHashTable);
            if (movie_choice == NULL) break;
            movie_print(movie_choice);
            //order_show_all //Ȼ��������е�ǰ���εĶ���
            break;
        case 4:
            printf("��ǰʱ������������Ϊ:%.2lf", caculate_movie_income(new_movie_list));
            while (get_user_input_int(0));
            break;
        default:
            movie_list_free(new_movie_list);
            new_movie_list = NULL;
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
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list,2);
            printf("���۸��������");
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 3);
            printf("�����������������");
            break;
        case 4:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("����ʼʱ���������");
            break;
        case 5:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("��ʣ��Ʊ���������");
            break;
        default:
            return new_movie_list;
        }
        _sleep(1000);
    }
}
Movie* for_admin_movie_filter(Movie* new_movie_list)
{
    while (1)
    {
        system("cls");
        display_admin_filter_menu();
        int option = get_user_input_int(6);
        Movie* free_temp = new_movie_list;
        //ʱ��Σ��ѷ�ӳ��δ��ӳ���������ڣ�ӰƬ���ͣ���ӰԺid
        char start_time[20]; char end_time[20]; char text[20];
        switch (option)
        {
        case 1:
            printf("��ֱ�������ֹʱ��\n");
            //if (get_valid_date_input(start_time) == 1 || get_valid_date_input(end_time) == 1) { break; }
            get_valid_date_input(start_time);
            get_valid_date_input(end_time);
            printf("��ʱ��� %s-%s ��ɸѡ�����", start_time, end_time);
            strcat(start_time, " 00:00:00");
            strcat(end_time, " 00:00:00");
            char* context[] = { start_time,end_time };
            new_movie_list = movie_operation_filter(new_movie_list, 1, context);
            break;
            
        case 2: 
            new_movie_list = movie_filter_by_played(new_movie_list);
            printf("��ɸѡ�ѷ�ӳ����\n");
            break;
        case 3:
            new_movie_list = movie_filter_by_not_played(new_movie_list);
            printf("��ɸѡδ��ӳ����\n");
            break;
        case 4:
            new_movie_list = movie_filter_by_current_date(new_movie_list);
            printf("��ɸѡ���ճ���\n");
            break;
        case 5:
            printf("������ӰƬ����:");
            scanf("%s", text);
            new_movie_list = movie_operation_filter(new_movie_list, 5, text);
            printf("��ɸѡӰƬ����: %s\n",text);
            break;
        case 6:
            printf("�������ӰԺid:");
            scanf("%s", text);
            new_movie_list = movie_operation_filter(new_movie_list, 6, text);
            printf("��ɸѡ��ӰԺid: %s\n",text);
            break;
        default:
            return new_movie_list; //���ܷ���NULL
        }
        int count = 0; Movie* temp_head = new_movie_list;
        while (temp_head)
        {
            count++; temp_head = temp_head->next;
        }
        printf("��ǰɸѡ�õ� %d������", count);
        //if (count != 0)
        //{
            movie_list_free(free_temp);
            free_temp = NULL;
        //}
        //else
        //{
        //    printf(",�ѻ���,������ɸѡ");
        //    new_movie_list = free_temp;
        //}
        _sleep(1000);
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

