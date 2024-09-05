#include "main.h"
static void admin_order_manage();
int main() {
    int mode;
    printf("test\n");
    hash_ini();
    load_file();
    admin_now = admin_find_by_id(admin_list, "A001"); 
    user_now = find_user_in_hash_table(userHashTable, "U001");
    
    /*Film* target_film = find_film_in_hash_table_by_name(filmHashTable, "Inception");
    Movie* movie_raw_list = movie_list_create_by_film(target_film, movieHashTable);*/
    user_operation();
    //admin_operation();
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
static Film* hot_films()//������
{
    Film* copied_list = film_copy_list(film_list);
    Film* film_list_hot = film_sort(copied_list, compare_films_by_ratings);
    static int t = 0;
    for (int i = 0; i < t; ++i)
        film_list_hot = film_list_hot->next;
    ++t;
    if (t >= 5) t %= 5;
    film_list_free(copied_list);
    return film_list_hot;
}
static void user_operation()
{
    while (1)
    {
        //system("cls");
        display_user_greet();
        int option = get_user_input_int(4);
        switch (option)
        {
        case 1:
            user_purchase_ticket();
            break;
        case 2:
            printf("�Ƽ�ӰƬ:\n");
            Film* hot_film = hot_films();
            film_print(hot_film);
            printf("�Ƿ���빺Ʊ>(1/0)");
            if (!get_user_input_int(1)) break;
            Movie* choosed_movie = search_target_film_and_choose_movie(hot_film);
            if (!choosed_movie) break;
            //Ȼ��Ʊ
            break;
        default:
            return;
        }
    }
}
Movie* search_target_film_and_choose_movie(Film* target_film)
{
    Movie* movie_raw_list = movie_list_create_by_film(target_film, movieHashTable);
    Movie* movie_filtered_list_temp = movie_filter_by_current_date(movie_raw_list);
    Movie* movie_filtered_list = movie_filter_by_not_played(movie_filtered_list_temp);//�õ�����δ��ӳ����
    if (movie_filtered_list == NULL)
    {
        printf("���޵��ճ���\n");
        press_zero_to_continue();
        movie_list_free(movie_raw_list);
        movie_list_free(movie_filtered_list_temp);
        return;
    }
    Movie* target_movie = for_user_movie_choose(movie_filtered_list,movieHashTable ); //�õ�target_movie
    movie_show(target_movie);
    seat_map_show(target_movie->seat_map);
    //printf("�ó��ε��Ƽ�%s.\n", get_great_seats(target_movie->seat_map));
    order_generate_main(user_now, target_movie);
    movie_list_free(movie_raw_list);
    movie_list_free(movie_filtered_list);
    return target_movie;
}
static void sub_purchase_by_name()
{
    Film* target_film;
    while (1) {
        printf("�������Ӱ���ƣ�");
        char scanf_movie_name[30]; get_user_input_string(scanf_movie_name, 20);
        target_film = find_film_in_hash_table_by_name(filmHashTable, scanf_movie_name);
        if (target_film == NULL) {
            printf("�޷��ҵ���ǰӰƬ,�Ƿ���������?(1/0)");
            if (!get_user_input_int(1)) return;  //�������0�˳�ѭ��
        }
        if (target_film !=NULL) break;
    }
    Movie* target_movie = search_target_film_and_choose_movie(target_film); //�õ�target movieȻ����
    order_generate_main(user_now, target_movie);
}
static void sub_purchase_by_name_and_cinema()
{
    char cinema_name[20]; char film_name[20]; Cinema* target_cinema; Film* target_film;
    while (1)
    {
        printf("�������ӰԺ���ƣ�\n");
        get_user_input_string(cinema_name, 15);
        target_cinema = cinema_find_by_name(cinema_list, cinema_name);
        if (!target_cinema)
        {
            printf("δ�ҵ���ӰԺ���Ƿ���������?(1/0)");
            if (!get_user_input_int(1)) return;
        }
        if (target_cinema) break;
    }
    while (1)
    {
        printf("�������Ӱ���ƣ�\n");
        get_user_input_string(film_name, 15);
        target_film = find_film_in_hash_table_by_name(filmHashTable, film_name);
        if (!target_film)
        {
            printf("δ�ҵ���Ӱ���Ƿ���������?(1/0)");
            if (!get_user_input_int(1)) return;
        }
        if (target_film) break;
    }
    
    Movie* raw_movie_list = movie_list_create_by_film(target_film, movieHashTable);
    Movie* cinema_film_movie_list = movie_filter_by_cinema_name(film_name, raw_movie_list);
    Movie* choosed_movie = for_user_movie_choose(cinema_film_movie_list, movieHashTable);
    if (!choosed_movie) return;
    //Ȼ����븶��
    movie_list_free(raw_movie_list);
    movie_list_free(cinema_film_movie_list);
    if (choosed_movie) {

        order_generate_main(user_now, choosed_movie);
        
    }
}
static void user_purchase_ticket()
{
    while (1)
    {
        //system("cls");
        display_purchase_ticket();
        int option = get_user_input_int(4);
        switch (option)
        {
        case 1:
            sub_purchase_by_name();
            //����
            break;
        case 2: 
            sub_purchase_by_name_and_cinema();
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
            admin_modify_self_info();
            break;
        default:
            return;
        }
    }
}
static void admin_modify_self_info()
{
    while (1)
    {
        system("cls");
        display_admin_modify_info_menu();
        int option = get_user_input_int(5);
        char* buffter[24];
        switch (option)
        {
        case 1:
            printf("�������µ�id��\n");
            get_user_input_string(buffter, 20);
            printf("ȷ�Ͻ�id��%s �޸�Ϊ", admin_now->admin_id);
            break;
        case 2:
            printf("�������µ�������\n");
            get_user_input_string(buffter, 20);
            printf("ȷ�Ͻ�������%s �޸�Ϊ", admin_now->admin_name);
            break;
        case 3:
            strcpy(buffter, get_valid_phone_number());
            printf("ȷ�Ͻ��绰�����%s �޸�Ϊ", admin_now->admin_telephone);
            break;
        case 4:
            while (!change_password(admin_now->admin_password, buffter));
            printf("ȷ�Ͻ������޸�Ϊ");
            break;
        case 5:
            get_valid_email(buffter, 20);
            printf("ȷ�Ͻ������%s �޸�Ϊ", admin_now->admin_email);
            break;
        case 0:
            return;
        default:
            return;
        }
        printf(" %s\n", buffter);
        int certify = get_user_input_int(1);
        
        if (certify) {
            admin_modify(admin_now, option, buffter);
            printf("�޸ĳɹ�\n");
            
        }
         else printf("��ȡ��");
        press_zero_to_continue();
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
        admin_order_manage_greet(); char text[20];
        int option = get_user_input_int(2);
        switch (option)
        {
        case 1:
            admin_view_and_count_order();
            break;
        case 2:
            while (1)
            {

                printf("�����붩���ţ�\n");
                get_user_input_string(text, 20);
                Order* order = find_order_in_hash_table(orderHashTable, text);
                if (!order)
                {
                    printf("δ�ҵ�����,�Ƿ���������?(1/0)");
                    int cer = get_user_input_int(1);
                    if (!cer) break;
                }
            }
            break;
        default:
            return; break;
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
        //system("cls");
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
            //Ȼ����빺Ʊ�����з���ֵ
            break;
        default:
            movie_list_free(new_movie_list);
            new_movie_list = NULL;
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
Movie* for_user_movie_sort(Movie* new_movie_list)
{
    while (1)
    {
        //Movie* temp = new_movie_list;
        system("cls");
        display_user_sort_menu();
        int option = get_user_input_int(3);
        //�۸񣬿�ʼʱ�䣬��Ʊ��
        switch (option)
        {
        case 1:
            new_movie_list = movie_operation_sort(new_movie_list, 2);
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
        default:
            return new_movie_list;
        }
        press_zero_to_continue();
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
        while (balance_check(order, orderHashTable) == 2) {
            printf("����,�������ֵ%fԪ`.������ֵ�밴1��������ֵ�밴0\n", get_debt(order, orderHashTable));
            int cer = get_user_input_int(1);
            if (cer) {
                if (balance_check(order, orderHashTable) != 1) {
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
void recharge_main( ) {
    char* userID;
    while (1) {
        if (scanf("%s", userID) != 1) {
            printf("������Ч�����������롣\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (user_find_by_id(user_list, userID) == NULL) {
        printf("�������userID��Ч.\n");
    }
    else {
        User* usr = user_find_by_id(user_list, userID);
        printf("���������ĳ�ֵ���.\n");// ��ȡ��ֵ�����ó�ֵ����  
        double money;
        while (1) {
            if (scanf("%lf", money) != 1) {
                printf("������Ч�����������롣\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        recharge(usr, money);
    }
}

//�û����ݶ�������
int process_pay_main( ) {
    printf("��������Ҫȡ����orderID.\n");
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
    Order* order = find_order_in_hash_table(orderHashTable, orderID);
    return process_pay_main_order(order);
}

//ȡ������
//return 0 �� ������Ч�������û���Ϣ��ȡʧ��
//       1 �� ȡ���ɹ�
//       2 �� ȡ��ʧ��  
int order_cancle_main( ) {
    printf("��������Ҫȡ����orderID.\n");
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
        printf("Enter your ID:");
        scanf("%s", id);
        if (id=='\n') { printf("ID don't found\n"); _sleep(500); system("cls"); continue; }
        user_now = find_user_in_hash_table(userHashTable, id);
        admin_now = admin_find_by_id(admin_list, id);//ע�⿼����������
        if ((!user_now) && (!admin_now)) {
            printf("�޷��ҵ�ID\n");
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
static void load_file() {
    void* context1[] = { userHashTable,&user_list };
    load_data_from_csv("C:\\Users\\Lenovo\\Source\\Repos\\Movie_C\\Data\\users.csv", handle_user_data, context1);
    void* context2[] = { &film_list,filmHashTable };
    load_data_from_csv("C:\\Users\\Lenovo\\Source\\Repos\\Movie_C\\Data\\films.csv", handle_film_data, context2);
    void* context3[] = { &cinema_list };
    load_data_from_csv("C:\\Users\\Lenovo\\Source\\Repos\\Movie_C\\Data\\cinemas.csv", handle_cinema_data, context3);
    void* context4[] = { cinema_list,&admin_list };
    load_data_from_csv("C:\\Users\\Lenovo\\Source\\Repos\\Movie_C\\Data\\admins.csv", handle_admin_data, context4);
    void* context5[] = { &theater_list,&cinema_list,theaterHashTable };
    load_data_from_csv("C:\\Users\\Lenovo\\Source\\Repos\\Movie_C\\Data\\theaters.csv", handle_theater_data, context5);
    void* context6[] = { &movie_list,movieHashTable,theaterHashTable,filmHashTable };
    load_data_from_csv("C:\\Users\\Lenovo\\Source\\Repos\\Movie_C\\Data\\movies.csv", handle_movie_data, context6);

    void* context7[] = {
            orderHashTable,   // ������ϣ��
            userHashTable,    // �û���ϣ��
            movieHashTable,   // ��Ӱ��ϣ��
            &order_list,      // ��������
    };
    load_data_from_csv("C:\\Users\\Lenovo\\Source\\Repos\\Movie_C\\Data\\order.csv", handle_order_data, context7);
}


