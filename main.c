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
static Film* hot_films()//有问题
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
            printf("推荐影片:\n");
            Film* hot_film = hot_films();
            film_print(hot_film);
            printf("是否进入购票>(1/0)");
            if (!get_user_input_int(1)) break;
            Movie* choosed_movie = search_target_film_and_choose_movie(hot_film);
            if (!choosed_movie) break;
            //然后购票
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
    Movie* movie_filtered_list = movie_filter_by_not_played(movie_filtered_list_temp);//得到当天未放映场次
    if (movie_filtered_list == NULL)
    {
        printf("暂无当日场次\n");
        press_zero_to_continue();
        movie_list_free(movie_raw_list);
        movie_list_free(movie_filtered_list_temp);
        return;
    }
    Movie* target_movie = for_user_movie_choose(movie_filtered_list,movieHashTable ); //得到target_movie
    movie_show(target_movie);
    seat_map_show(target_movie->seat_map);
    //printf("该场次的推荐%s.\n", get_great_seats(target_movie->seat_map));
    order_generate_main(user_now, target_movie);
    movie_list_free(movie_raw_list);
    movie_list_free(movie_filtered_list);
    return target_movie;
}
static void sub_purchase_by_name()
{
    Film* target_film;
    while (1) {
        printf("请输入电影名称：");
        char scanf_movie_name[30]; get_user_input_string(scanf_movie_name, 20);
        target_film = find_film_in_hash_table_by_name(filmHashTable, scanf_movie_name);
        if (target_film == NULL) {
            printf("无法找到当前影片,是否重新输入?(1/0)");
            if (!get_user_input_int(1)) return;  //如果输入0退出循环
        }
        if (target_film !=NULL) break;
    }
    Movie* target_movie = search_target_film_and_choose_movie(target_film); //得到target movie然后购买
    order_generate_main(user_now, target_movie);
}
static void sub_purchase_by_name_and_cinema()
{
    char cinema_name[20]; char film_name[20]; Cinema* target_cinema; Film* target_film;
    while (1)
    {
        printf("请输入电影院名称：\n");
        get_user_input_string(cinema_name, 15);
        target_cinema = cinema_find_by_name(cinema_list, cinema_name);
        if (!target_cinema)
        {
            printf("未找到电影院，是否重新输入?(1/0)");
            if (!get_user_input_int(1)) return;
        }
        if (target_cinema) break;
    }
    while (1)
    {
        printf("请输入电影名称：\n");
        get_user_input_string(film_name, 15);
        target_film = find_film_in_hash_table_by_name(filmHashTable, film_name);
        if (!target_film)
        {
            printf("未找到电影，是否重新输入?(1/0)");
            if (!get_user_input_int(1)) return;
        }
        if (target_film) break;
    }
    
    Movie* raw_movie_list = movie_list_create_by_film(target_film, movieHashTable);
    Movie* cinema_film_movie_list = movie_filter_by_cinema_name(film_name, raw_movie_list);
    Movie* choosed_movie = for_user_movie_choose(cinema_film_movie_list, movieHashTable);
    if (!choosed_movie) return;
    //然后进入付款
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
            //购买
            break;
        case 2: 
            sub_purchase_by_name_and_cinema();
            break;
            

        case 3://自定义查找
            user_view_and_count_movie();
            break;
            
        default:
            printf("无效的选项，请重新选择。\n");
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
            printf("请输入新的id：\n");
            get_user_input_string(buffter, 20);
            printf("确认将id从%s 修改为", admin_now->admin_id);
            break;
        case 2:
            printf("请输入新的姓名：\n");
            get_user_input_string(buffter, 20);
            printf("确认将姓名从%s 修改为", admin_now->admin_name);
            break;
        case 3:
            strcpy(buffter, get_valid_phone_number());
            printf("确认将电话号码从%s 修改为", admin_now->admin_telephone);
            break;
        case 4:
            while (!change_password(admin_now->admin_password, buffter));
            printf("确认将密码修改为");
            break;
        case 5:
            get_valid_email(buffter, 20);
            printf("确认将邮箱从%s 修改为", admin_now->admin_email);
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
            printf("修改成功\n");
            
        }
         else printf("已取消");
        press_zero_to_continue();
    }
}
static void admin_movie_manage()//排片管理
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
                printf("场次添加成功\n"); break;
            case 2:
                printf("数据出错...\n"); break;
            case 0:
                printf("已取消添加\n"); break;
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
                printf("场次添加成功\n"); break;
            case 2:
                printf("数据出错...\n"); break;
            case 0:
                printf("已取消添加\n"); break;
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
static void admin_theater_manage()//theater的删除没做
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
                printf("影厅添加成功\n"); break;
            case 2:
                printf("数据出错...\n"); break;
            case 0:
                printf("已取消添加\n"); break;
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
            printf("已展示所有影厅\n");
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

                printf("请输入订单号：\n");
                get_user_input_string(text, 20);
                Order* order = find_order_in_hash_table(orderHashTable, text);
                if (!order)
                {
                    printf("未找到订单,是否重新输入?(1/0)");
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
        printf("当前无可用场\n");
        press_zero_to_continue();
    }
    while (1)
    {
        //system("cls");
        display_user_movie_operate_main_menu();
        int option = get_user_input_int(3);
        switch (option)
        {
        case 1://选择了排序
            new_movie_list = for_user_movie_sort(new_movie_list);//进入排序界面
            break;
        case 2://选择了筛选
            new_movie_list = for_user_movie_filter(new_movie_list);
            break;
        case 3:
            Movie * movie_choice = movie_choose(new_movie_list, movieHashTable);
            if (movie_choice == NULL) break;
            movie_print(movie_choice);
            //然后进入购票，会有返回值
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
        case 1://选择了排序
            new_movie_list = for_admin_movie_sort(new_movie_list);//进入排序界面
            break;
        case 2://选择了筛选
            new_movie_list= for_admin_movie_filter(new_movie_list);
            break;
        case 3:
            Movie * movie_choice = movie_choose(new_movie_list,movieHashTable);
            if (movie_choice == NULL) break;
            movie_print(movie_choice);
            //order_show_all //然后输出所有当前场次的订单
            break;
        case 4:
            printf("当前时间区段总收入为:%.2lf", caculate_movie_income(new_movie_list));
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
        //价格，开始时间，余票数
        switch (option)
        {
        case 1:
            new_movie_list = movie_operation_sort(new_movie_list, 2);
            printf("按价格排序完成");
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("按开始时间排序完成");
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("按剩余票数排序完成");
            break;
        default:
            return new_movie_list;
        }
        press_zero_to_continue();
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
            break;
        case 2:
            new_movie_list = movie_operation_sort(new_movie_list,2);
            printf("按价格排序完成");
            break;
        case 3:
            new_movie_list = movie_operation_sort(new_movie_list, 3);
            printf("按场次收入排序完成");
            break;
        case 4:
            new_movie_list = movie_operation_sort(new_movie_list, 4);
            printf("按开始时间排序完成");
            break;
        case 5:
            new_movie_list = movie_operation_sort(new_movie_list, 5);
            printf("按剩余票数排序完成");
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
    //时间段，影片类型，电影院，影厅类型
    char start_time[20]; char end_time[20]; char text[20];
    switch (option)
    {
    case 1:
        printf("请分别输入起止时间\n");
        get_valid_date_input(start_time);
        get_valid_date_input(end_time);
        printf("对时间段 %s-%s 的筛选已完成", start_time, end_time);
        strcat(start_time, " 00:00:00");
        strcat(end_time, " 00:00:00");
        char* context[] = { start_time,end_time };
        new_movie_list = movie_operation_filter(new_movie_list, 1, context);
        break;
    case 2:
        printf("请输入影片类型:");
        scanf("%s", text);
        new_movie_list = movie_operation_filter(new_movie_list, 5, text);
        printf("已筛选影片类型: %s\n", text);
        break;
    case 3:
        printf("请输入电影院:");
        scanf("%s", text);
        new_movie_list = movie_filter_by_cinema_name(text, new_movie_list);
        printf("已筛选电影院: %s\n", text);
        break;
    case 4:
        printf("请输入影厅类型：");
        get_user_input_string(text, 20);
        new_movie_list = movie_filter_by_theater_type(text, new_movie_list);
        printf("已筛选影厅类型：%s\n", text);
        break;
    default:
        return new_movie_list; //可能返回NULL
    }
    int count = 0; Movie* temp_head = new_movie_list;
    while (temp_head)
    {
        count++; temp_head = temp_head->next;
    }
    printf("当前筛选得到 %d条数据", count);
    if (count != 0)
    {
        movie_list_free(free_temp);
        free_temp = NULL;
    }
    else
    {
        printf(",已回退,请重新筛选\n");
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
        //时间段，已放映，未放映，当日日期，影片类型，电影院id
        char start_time[20]; char end_time[20]; char text[20];
        switch (option)
        {
        case 1:
            printf("请分别输入起止时间\n");
            //if (get_valid_date_input(start_time) == 1 || get_valid_date_input(end_time) == 1) { break; }
            get_valid_date_input(start_time);
            get_valid_date_input(end_time);
            printf("对时间段 %s-%s 的筛选已完成", start_time, end_time);
            strcat(start_time, " 00:00:00");
            strcat(end_time, " 00:00:00");
            char* context[] = { start_time,end_time };
            new_movie_list = movie_operation_filter(new_movie_list, 1, context);
            break;
            
        case 2: 
            new_movie_list = movie_filter_by_played(new_movie_list);
            printf("已筛选已放映场次\n");
            break;
        case 3:
            new_movie_list = movie_filter_by_not_played(new_movie_list);
            printf("已筛选未放映场次\n");
            break;
        case 4:
            new_movie_list = movie_filter_by_current_date(new_movie_list);
            printf("已筛选当日场次\n");
            break;
        case 5:
            printf("请输入影片类型:");
            scanf("%s", text);
            new_movie_list = movie_operation_filter(new_movie_list, 5, text);
            printf("已筛选影片类型: %s\n",text);
            break;
        case 6:
            printf("请输入电影院id:");
            scanf("%s", text);
            new_movie_list = movie_operation_filter(new_movie_list, 6, text);
            printf("已筛选电影院id: %s\n",text);
            break;
        default:
            return new_movie_list; //可能返回NULL
        }
        int count = 0; Movie* temp_head = new_movie_list;
        while (temp_head)
        {
            count++; temp_head = temp_head->next;
        }
        printf("当前筛选得到 %d条数据", count);
        if (count != 0)
        {
            movie_list_free(free_temp);
            free_temp = NULL;
        }
        else
        {
            printf(",已回退,请重新筛选\n");
            new_movie_list = free_temp;
        }
        press_zero_to_continue();
    }
}

//Order main
//
//生成订单
//return 0 : 生成失败
//       1 : 生成成功，支付成功
//       2 : 生成成功，支付失败
int order_generate_main(User* usr, Movie* movie) //判断当前时间是否早于电影开始时间
{                           
    char* seats;
    while (1) {
        printf("请输入您想购买的座位号(形如A1-B1-C1).\n");
        seats = seats_input_check();
        if (seats == NULL) {
            printf("输入无效，请重新输入.\n");
            while (getchar() != '\n');
            continue;
        }
            break;
    }
    int judge = strcmp(get_current_time(), movie->start_time);
    if(judge <= 0)  {
        int check = order_generation(usr, seats, movie, movie->seat_map, orderHashTable);
        switch (check) { //根据生成订单的结果进行不同处理  
        case 0:
            printf("查询失败.\n");
            return 0;
        case 1:
            break;
        case 2:
            printf("您输入的座位数超过了最大购票限额.\n");
            return 0;
        case 3:
            printf("您输入了两个相同的座位号.\n");
            return 0;
        case 4:
            printf("您输入的座位号不在影院座次范围内.\n");
            return 0;
        case 5:
            printf("座位已经售出.\n");
            return 0;
        case 6:
            printf("座位与已售出的座位仅间隔一个座位.\n");
            return 0;
        case 7:
            printf("您已经购买过该场次的票,请确认是否继续购买,继续购买请按1,放弃购买请按0\n");
            int cer = get_user_input_int(1);
            if (cer) {
                break;
            }
            return 0;
        case 8:
            printf("当天已购买过五个场次的票,请明日再行购买.\n");
            return 0;
        case 9:
            printf("该场次和您已经购买的场次时间冲突,请确认是否继续购买,继续购买请按1,放弃购买请按0\n");
            int cer1 = get_user_input_int(1);
            if (cer1) {
                break;
            }
            return 0;
        case 10:
            printf("已购买过该场次的票且购买多个影片场次时间冲突,请确认是否继续购买,继续购买请按1,放弃购买请按0\n");
            int cer2 = get_user_input_int(1);
            if (cer2) {
                break;
            }
            return 0;
        }
        // 订单生成并添加到列表中  
        Order* new_order = order_create(orderHashTable, get_orderID(), usr, usr->userID, movie, movie->movie_id, movie->theater, movie->theater->cinema, seats, get_seat_number(seats), 2, get_current_time);
        order_add_to_list(&order_list, new_order);
        printf("订单生成成功，您的orderID是:%s\n是否付款，确认付款请按1，放弃付款请按0.\n", new_order->orderID);
        int cer=get_user_input_int(1);
        if (cer){
            return process_pay_main_order(new_order);
        }
        else {
            return 2;
        }
    }
    else{
        printf("您购买的影片已经开始.\n");
        return 0;// 影片已开始，无法购买  
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
        while (balance_check(order, orderHashTable) == 2) {
            printf("余额不足,您还需充值%f元`.继续充值请按1，放弃充值请按0\n", get_debt(order, orderHashTable));
            int cer = get_user_input_int(1);
            if (cer) {
                if (balance_check(order, orderHashTable) != 1) {
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
void recharge_main( ) {
    char* userID;
    while (1) {
        if (scanf("%s", userID) != 1) {
            printf("输入无效，请重新输入。\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    if (user_find_by_id(user_list, userID) == NULL) {
        printf("您输入的userID无效.\n");
    }
    else {
        User* usr = user_find_by_id(user_list, userID);
        printf("请输入您的充值金额.\n");// 获取充值金额并调用充值函数  
        double money;
        while (1) {
            if (scanf("%lf", money) != 1) {
                printf("输入无效，请重新输入。\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        recharge(usr, money);
    }
}

//用户根据订单付款
int process_pay_main( ) {
    printf("请输入您要取消的orderID.\n");
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
    Order* order = find_order_in_hash_table(orderHashTable, orderID);
    return process_pay_main_order(order);
}

//取消订单
//return 0 ： 输入无效订单或用户信息获取失败
//       1 ： 取消成功
//       2 ： 取消失败  
int order_cancle_main( ) {
    printf("请输入您要取消的orderID.\n");
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
        printf("Enter your ID:");
        scanf("%s", id);
        if (id=='\n') { printf("ID don't found\n"); _sleep(500); system("cls"); continue; }
        user_now = find_user_in_hash_table(userHashTable, id);
        admin_now = admin_find_by_id(admin_list, id);//注意考虑重名问题
        if ((!user_now) && (!admin_now)) {
            printf("无法找到ID\n");
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
            orderHashTable,   // 订单哈希表
            userHashTable,    // 用户哈希表
            movieHashTable,   // 电影哈希表
            &order_list,      // 订单链表
    };
    load_data_from_csv("C:\\Users\\Lenovo\\Source\\Repos\\Movie_C\\Data\\order.csv", handle_order_data, context7);
}


