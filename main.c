#include "main.h"

int main() {
    int mode;
    printf("test\n");
    hash_ini();
    load_file();

    user_now = find_user_in_hash_table(userHashTable, "U001");
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
            user_purchase_ticket();
            break;
        case 2:
            printf("�Ƽ�ӰƬ:\n");
            Film* hot_film = hot_films(film_list);
            film_print(hot_film);
            printf("�Ƿ���빺Ʊ>(1/0)");
            if (!get_user_input_int(1)) break;
            Movie* choosed_movie = search_target_film_and_choose_movie(hot_film,movieHashTable,user_now);
            if (!choosed_movie) break;
            press_zero_to_continue();
            break;
        case 3:
            printf("��ѡ�����Ĺ���:\n1.�鿴����.\n2.����\n3.ȡ������\n4.�˿�\n\n0.�˳�\n");
            int cer = get_user_input_int(4);
            switch (cer) {
            case 1:
                printf("����������userID:\n");
                char userID[100];
                while (1) {
                    if (scanf("%99s", userID) != 1) { // ʹ�ÿ����������ֹ���������  
                        printf("������Ч�����������롣\n");
                        while (getchar() != '\n'); // ������뻺�����е�ʣ���ַ�  
                        continue;
                    }
                    break;
                }
                User* usr = user_find_by_id(user_list, userID);
                if (usr == NULL) {
                    printf("�������userID��Ч.\n");
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
            recharge_main();
            press_zero_to_continue();
            break;
        default:
            return;
            break;
        }
    }
}



static void user_purchase_ticket()
{
    while (1)
    {
        system("cls");
        display_purchase_ticket();
        int option = get_user_input_int(4);
        switch (option)
        {
        case 1:
            sub_purchase_by_name(filmHashTable, movieHashTable, user_now);
            //����
            break;
        case 2: 
            sub_purchase_by_name_and_cinema(cinema_list,filmHashTable,movieHashTable,user_now);
            break;
           
        case 3://�Զ������
            user_view_and_count_movie();
            break;
            
        default:
            printf("��Ч��ѡ�������ѡ��\n");
            return;
            
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
 


static void user_view_and_count_movie()
{
    Movie* new_movie_list = movie_filter_by_not_played(movie_list);
    if (!new_movie_list)
    {
        printf("��ǰ�޿��ó�\n");
        press_zero_to_continue();
    }
    while (1)
    {
        system("cls");
        
        display_user_movie_operate_main_menu();
        
        int option = get_user_input_int(3);
        switch (option)
        {
        case 1://ѡ��������
            new_movie_list = for_user_movie_sort(new_movie_list);//�����������

            break;
        case 2://ѡ����ɸѡ
            new_movie_list = for_user_movie_filter(new_movie_list);
            break;
        case 3:
            
            Movie * movie_choice = movie_choose(new_movie_list, movieHashTable);
            
            if (movie_choice == NULL) break;
            movie_print(movie_choice);
            order_generate_main(user_now, movie_choice);
            seat_map_show(movie_choice->seat_map);
            printf("�ó��ε��Ƽ�%s.\n", get_great_seats(movie_choice->seat_map));
            order_generate_main(user_now, movie_choice);
            break;
        default:
            movie_list_free(new_movie_list);
            new_movie_list = NULL;
            return;
        }
    }
}


Movie* for_user_movie_sort(Movie* new_movie_list)
{
    while (1)
    {
        
        system("cls");
        display_user_sort_menu();
        int option = get_user_input_int(3);
        //�۸񣬿�ʼʱ�䣬��Ʊ��
        switch (option)
        {
        case 1:
            new_movie_list = movie_operation_sort(new_movie_list, 2);
            //movie_print(new_movie_list);
            printf("���۸��������");
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("����ʼʱ���������");
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("��ʣ��Ʊ���������");
            break;
        case 0:

            return new_movie_list;
        }
        press_zero_to_continue();
    }
}

Movie* for_user_movie_filter(Movie* new_movie_list)
{
    system("cls");
    display_user_filter_menu();
    int option = get_user_input_int(6);
    Movie* free_temp = new_movie_list;
    //ʱ��Σ�ӰƬ���ͣ���ӰԺ��Ӱ������
    char start_time[20]; char end_time[20]; char text[20];
    switch (option)
    {
    case 1:
        printf("��ֱ�������ֹʱ��\n");
        get_valid_date_input(start_time);
        get_valid_date_input(end_time);
        printf("��ʱ��� %s-%s ��ɸѡ�����", start_time, end_time);
        strcat(start_time, " 00:00:00");
        strcat(end_time, " 00:00:00");
        char* context[] = { start_time,end_time };
        new_movie_list = movie_operation_filter(new_movie_list, 1, context);
        break;
    case 2:
        printf("������ӰƬ����:");
        scanf("%s", text);
        new_movie_list = movie_operation_filter(new_movie_list, 5, text);
        printf("��ɸѡӰƬ����: %s\n", text);
        break;
    case 3:
        printf("�������ӰԺ:");
        scanf("%s", text);
        new_movie_list = movie_filter_by_cinema_name(text, new_movie_list);
        printf("��ɸѡ��ӰԺ: %s\n", text);
        break;
    case 4:
        printf("������Ӱ�����ͣ�");
        get_user_input_string(text, 20);
        new_movie_list = movie_filter_by_theater_type(text, new_movie_list);
        printf("��ɸѡӰ�����ͣ�%s\n", text);
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
    if (count != 0)
    {
        movie_list_free(free_temp);
        free_temp = NULL;
    }
    else
    {
        printf(",�ѻ���,������ɸѡ\n");
        new_movie_list = free_temp;
    }
    press_zero_to_continue();
}



//Order main
//
//���ɶ���
//return 0 : ����ʧ��
//       1 : ���ɳɹ���֧���ɹ�
//       2 : ���ɳɹ���֧��ʧ��
int order_generate_main(User* usr, Movie* movie) //�жϵ�ǰʱ���Ƿ����ڵ�Ӱ��ʼʱ��
{                           
    char* seats;
    while (1) {
        printf("���������빺�����λ��(����A1-B1-C1).\n");
        seats = seats_input_check();
        if (seats == NULL) {
            printf("������Ч������������.\n");
            while (getchar() != '\n');
            continue;
        }
            break;
    }
    int judge = strcmp(get_current_time(), movie->start_time);
    if(judge <= 0)  {
        int check = order_generation(usr, seats, movie, movie->seat_map, orderHashTable);
        switch (check) { //�������ɶ����Ľ�����в�ͬ����  
        case 0:
            printf("��ѯʧ��.\n");
            return 0;
        case 1:
            break;
        case 2:
            printf("���������λ�����������Ʊ�޶�.\n");
            return 0;
        case 3:
            printf("��������������ͬ����λ��.\n");
            return 0;
        case 4:
            printf("���������λ�Ų���ӰԺ���η�Χ��.\n");
            return 0;
        case 5:
            printf("��λ�Ѿ��۳�.\n");
            return 0;
        case 6:
            printf("��λ�����۳�����λ�����һ����λ.\n");
            return 0;
        case 7:
            printf("���Ѿ�������ó��ε�Ʊ,��ȷ���Ƿ��������,���������밴1,���������밴0\n");
            int cer = get_user_input_int(1);
            if (cer) {
                break;
            }
            return 0;
        case 8:
            printf("�����ѹ����������ε�Ʊ,���������й���.\n");
            return 0;
        case 9:
            printf("�ó��κ����Ѿ�����ĳ���ʱ���ͻ,��ȷ���Ƿ��������,���������밴1,���������밴0\n");
            int cer1 = get_user_input_int(1);
            if (cer1) {
                break;
            }
            return 0;
        case 10:
            printf("�ѹ�����ó��ε�Ʊ�ҹ�����ӰƬ����ʱ���ͻ,��ȷ���Ƿ��������,���������밴1,���������밴0\n");
            int cer2 = get_user_input_int(1);
            if (cer2) {
                break;
            }
            return 0;
        }
        // �������ɲ���ӵ��б���  
        Order* new_order = order_create(orderHashTable, get_orderID(), usr, usr->userID, movie, movie->movie_id, movie->theater, movie->theater->cinema, seats, get_seat_number(seats), 2, get_current_time);
        order_add_to_list(&order_list, new_order);
        printf("�������ɳɹ�������orderID��:%s\n�Ƿ񸶿ȷ�ϸ����밴1�����������밴0.\n", new_order->orderID);
        int cer=get_user_input_int(1);
        if (cer){
            return process_pay_main_order(new_order);
        }
        else {
            return 2;
        }
    }
    else{
        printf("�������ӰƬ�Ѿ���ʼ.\n");
        return 0;// ӰƬ�ѿ�ʼ���޷�����  
    }
}

//����
//return 1 �� ����ɹ�
//       2 �� ����ʧ��
int process_pay_main_order(Order* order) {
    if (order->status != 2) {// ��鶩��״̬�����Ը���
        printf("����״̬���Ϸ�.\n");
        return 2;
    }
    if (balance_check(order, orderHashTable) == 1) { // ���������  
        if (process_pay(order, order->movie->seat_map, orderHashTable) == 0) {
            printf("������ѯʧ��.\n");
            return 0;
        }
        else {
            printf("����ɹ�.\n");
            return 1;
        }
    }
    else {
        while (balance_check(order, orderHashTable) == 0) {
            printf("����,�������ֵ%fԪ`.������ֵ�밴1��������ֵ�밴0\n", get_debt(order, orderHashTable));
            int cer = get_user_input_int(1);
            if (cer) {
                if (balance_check(order, orderHashTable) == 0) {
                    continue;
                }
                else {
                    process_pay(order, order->movie->seat_map, orderHashTable);
                    printf("����ɹ�.\n");
                    return 1;
                }
            }
            return 2;
        }
    }
}

//��ֵ
void recharge_main(void) {
    

    printf("������");
    double money = get_user_input_double(50, 5000);
    scanf("%lf", &money);
        
    recharge(user_now, money);
    
}
//�û����ݶ�������
int process_pay_main(void) {
    char orderID[100]; // ���趩��ID���ᳬ��99���ַ�  
    printf("��������Ҫȡ����orderID.\n");
    while (1) {
        if (scanf("%99s", orderID) != 1) { // ʹ�ÿ����������ֹ���������  
            printf("������Ч�����������롣\n");
            while (getchar() != '\n'); // ������뻺�����е�ʣ���ַ�  
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("������Ķ�������Ч.\n");
        return 0;
    }
    Order* order = find_order_in_hash_table(orderHashTable, orderID);
    return process_pay_main_order(order);
}  

//ȡ������
//return 0 �� ������Ч�������û���Ϣ��ȡʧ��
//       1 �� ȡ���ɹ�
//       2 �� ȡ��ʧ��  
int order_cancle_main( ) {
    printf("��������Ҫȡ����orderID.\n");
    char orderID[20];
    while (1) {
        if (scanf("%s", orderID) != 1) {
            printf("������Ч�����������롣\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("������Ķ�������Ч.\n");
        return 0;
    }
    else {
        Order* order = find_order_in_hash_table(orderHashTable, orderID);
        if (order->status != 2) {
            printf("����״̬���Ϸ�,ȡ��ʧ��.\n");// ��鶩��״̬������ȡ��  
            return 2;
        }
        else {
            order_cancel(order);
            printf("ȡ���ɹ�.\n");
            return 1;
        }
    }
}

//�˿�
//return 0 �� ������Ч�������û���Ϣ��ȡʧ��
//       1 �� �˿�ɹ�
//       2 �� �˿�ʧ��  
int ticket_refund_main(  ) {
    printf("���������˿��orderID.\n");
    char* orderID;
    while (1) {
        if (scanf("%s", orderID) != 1) {
            printf("������Ч�����������롣\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (find_order_in_hash_table(orderHashTable, orderID) == NULL) {
        printf("������Ķ�������Ч.\n");
        return 0;
    }
    else {
        Order* order = find_order_in_hash_table(orderHashTable, orderID);
        if (order->status != 1) {    // ��鶩��״̬�������˿�
            printf("����״̬���Ϸ�.\n");
            return 2;
        }
        if (order->status != 1) {
            printf("�˿�ʧ��.\n");
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
        printf("����������ID:");
        scanf("%s", id);
        if (id=='\n') { printf("�������ID������\n"); _sleep(500); system("cls"); continue; }//���ڻس�����
        user_now = find_user_in_hash_table(userHashTable, id);
        admin_now = admin_find_by_id(admin_list, id);//ע�⿼����������
        if ((!user_now) && (!admin_now)) {
            printf("�������ID������\n");
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
//��ϣ���ʼ��
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
            orderHashTable,   // ������ϣ��
            userHashTable,    // �û���ϣ��
            movieHashTable,   // ��Ӱ��ϣ��
            &order_list,      // ��������
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

