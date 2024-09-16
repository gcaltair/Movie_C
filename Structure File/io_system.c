#include"io_system.h"
#include<stdlib.h>
#include <stdbool.h>
#include<stdio.h>
#include "../Object/Movie.h"
#include "../Object/Order.h"
#include"../Object/Cinema.h"
#include"../Object/Film.h"
void get_user_input_string(char* input, int max_length) {
    printf("请输入最多%d位的字符串: ", max_length);
    fgets(input, max_length + 1, stdin);  // 读取输入，最多max_length个字符

    // 去除末尾的换行符（如果有）
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
}

double get_user_input_double(double min, double max) {
    double option;
    char c;

    while (1) {
        printf("请输入一个数值 (范围: %.2f - %.2f): ", min, max);

        // 尝试读取一个 double 输入
        if (scanf("%lf", &option) == 1) {
            // 检查输入是否在指定范围内
            if (option >= min && option <= max) {
                // 清理输入缓冲区
                while ((c = getchar()) != '\n' && c != EOF) {}
                return option;
            }
            else {
                printf("输入无效，超出范围，请重新输入。\n");
            }
        }
        else {
            printf("输入无效，请输入一个数值。\n");

            // 清理输入缓冲区，处理非 double 输入
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
}
int get_user_input_int(int max) {
    int option;
    char c;
    while (1) {
        if (max != 0)
            printf("请输入您的选项 0-%d:", max);
        else
            printf("输入0以继续...\n");
        // 尝试读取一个整数输入
        if (scanf("%d", &option) == 1) {
            // 检查输入是否在指定范围内
            if (option >= 0 && option <= max) {
                // 清理输入缓冲区
                while ((c = getchar()) != '\n' && c != EOF) {}
                return option;
            }
            else {
                printf("输入错误,");
            }
        }
        else {
            printf("输入错误,");
            // 清理输入缓冲区，处理非整数输入
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
}

bool get_password(char* password, int maxLen) {
    int i = 0;
    char ch;
    while (i < maxLen - 1) {
        ch = _getch(); // 读取一个字符但不显示
        if (ch == 26 || ch == 3) return 0;
        if (ch == '\r') { // 检测到回车符（Enter键）
            break;
        }
        else if (ch == '\b') { // 处理退格键
            if (i > 0) {
                i--;
                printf("\b \b"); // 删除一个字符
            }
        }
        else {
            password[i++] = ch;

            printf("*"); // 显示星号
        }
    }
    password[i] = '\0'; // 字符串末尾添加终止符
    return 1;
}
// 检查日期格式是否为 YYYY-MM-DD
// 判断闰年
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 验证日期是否为有效的格式和有效日期
bool is_valid_date_format(const char* date) {
    // 长度必须为 10
    if (strlen(date) != 10) {
        return false;
    }

    // 检查格式是否为 YYYY-MM-DD
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') {
                return false;
            }
        }
        else {
            if (!isdigit(date[i])) {
                return false;
            }
        }
    }

    // 提取年份、月份、天数
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);

    // 检查月份是否有效
    if (month < 1 || month > 12) {
        return false;
    }

    // 检查天数是否有效
    int max_days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // 如果是闰年，2 月有 29 天
    if (is_leap_year(year)) {
        max_days_in_month[1] = 29;
    }

    // 检查天数是否有效
    if (day < 1 || day > max_days_in_month[month - 1]) {
        return false;
    }

    return true;
}


// 获取用户输入并确保格式正确
int get_valid_date_input(char* date) {
    while (true) {
        printf("请输入日期（格式: YYYY-MM-DD）：");
        scanf("%s", date);

        if (is_valid_date_format(date)) {
            break;
        }
        //else if (strcmp(date, "exit") == 0)
        //{
        //    return 1;
        //}
        else {
            printf("输入格式错误，请重新输入。\n");
        }
    }
    return 0;
}
// 验证邮箱是否合法的函数
bool is_valid_email(const char* email) {
    int at_pos = -1;
    int dot_pos = -1;
    int len = strlen(email);

    // 邮箱长度至少需要有 5 个字符（如 a@b.co）
    if (len < 5) {
        return false;
    }

    // 遍历邮箱字符串
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            // 如果有多个 '@' 符号，则不合法
            if (at_pos != -1) {
                return false;
            }
            at_pos = i;
        }
        if (email[i] == '.') {
            // 记录最后一个 '.' 符号的位置
            dot_pos = i;
        }
    }

    // 检查 '@' 符号的位置及其后面是否有 '.'
    if (at_pos == -1 || dot_pos == -1 || at_pos == 0 || dot_pos <= at_pos + 1 || dot_pos == len - 1) {
        return false;
    }

    // 进一步检查是否包含无效字符（非字母、数字、下划线、点和连字符）
    for (int i = 0; i < len; i++) {
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.' && email[i] != '_' && email[i] != '-') {
            return false;
        }
    }

    return true;
}

// 获取合法邮箱输入的函数
void get_valid_email(char* email, int max_length) {
    while (1) {
        printf("请输入您的邮箱地址: ");
        fgets(email, max_length, stdin);

        // 去除末尾的换行符
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }

        // 验证邮箱是否合法
        if (is_valid_email(email)) {
            printf("邮箱地址合法。\n");
            break;
        }
        else {
            printf("邮箱地址不合法，请重新输入。\n");
        }
    }
}
// 判断电话号码是否合法的函数
int is_valid_phone_number(const char* phone) {
    // 判断长度是否为11位
    if (strlen(phone) != 11) {
        return 0; // 长度不合法
    }

    // 判断首位是否为1
    if (phone[0] != '1') {
        return 0; // 首位不是1
    }

    // 判断是否全为数字
    for (int i = 0; i < 11; i++) {
        if (!isdigit(phone[i])) {
            return 0; // 发现非数字字符
        }
    }

    return 1; // 合法电话号码
}

// 获取合法的电话号码，并返回char*类型
char* get_valid_phone_number() {
    char* phone = (char*)malloc(12 * sizeof(char)); // 11位数字加1个结束符'\0'

    while (1) {
        printf("请输入新的电话号码: ");
        scanf("%s", phone);

        if (is_valid_phone_number(phone)) {
            return phone; // 合法，返回电话号码
        }
        else {
            printf("输入不合法，请重新输入。\n");
        }
    }
}

void from_user_print_order(Movie* movie,Order* order_list)
{
    Order* new_head = order_list;
    while (new_head)
    {
        if (!strcmp(movie->movie_id, new_head->movie_id))
        {
            order_print_for_user(new_head);
        }
        new_head = new_head->next;
    }
}
void movie_list_print(const Movie* movie_list)
{
    while (movie_list)
    {
        movie_print(movie_list);
        movie_list = movie_list->next;
    }
}
void film_print(const Film* film) {
    if (film) {
        printf("Film ID: %s\n", film->film_id);
        printf("Name: %s\n", film->film_name);
        printf("Type: %s\n", film->film_type);
        printf("Language: %s\n", film->film_language);
        printf("Summary: %s\n", film->film_summary);
        printf("Rating: %d\n", film->film_rating);
    }
}
void movie_print(const Movie* movie) {
    if (movie == NULL) { printf("当前信息为空"); return; }
    printf("场次ID: %s\n", movie->movie_id);
    printf("电影ID: %s\n", movie->film_id);
    printf("影厅ID: %s\n", movie->theater_id);
    printf("开始时间: %s\n", movie->start_time);
    printf("结束时间: %s\n", movie->end_time);
    printf("余票数: %d\n", movie->remaining_ticket);
    printf("价格: %.2f\n", movie->price);
    printf("折扣: %.2f\n", movie->discount);
    printf("------------\n");
}
void movie_print_for_user_ticket(const Movie* movie, char* seat) {
    if (movie == NULL) {
        printf("当前信息为空\n");
        return;
    }

    printf("==========================================\n");
    printf("|              电影票信息                |\n");
    printf("==========================================\n");
    printf("| %-10s: %-26s |\n", "电影名称", movie->film->film_name);
    printf("| %-10s: %-26s |\n", "影院名称", movie->theater->cinema->cinema_name);
    printf("| %-10s: %-26s |\n", "影厅名称", movie->theater->theater_name);
    printf("| %-10s: %-26s |\n", "座位号", seat);
    printf("| %-10s: %-26s |\n", "影厅类型", movie->theater->theater_type);
    printf("| %-10s: %-26s |\n", "语言", movie->film->film_language);
    printf("| %-10s: %-26s |\n", "开始时间", movie->start_time);
    printf("| %-10s: %-26s |\n", "结束时间", movie->end_time);
    printf("| %-10s: %-26.2f |\n", "价格", movie->price);
    printf("| %-10s: %-26.2f |\n", "折扣", movie->discount);
    printf("==========================================\n\n");
}
void order_print_for_user(const Order* order)
{
    if (order == NULL) {//order找不到提示
        printf("Order not found.\n");
        return;
    }
    printf("订单ID: %s\n", order->orderID);//展示order内容
    printf("用户ID: %s\n", order->user_id);//展示order内容
    printf("场次 ID: %s\n", order->movie_id);//展示order内容
    printf("座位 %s\n", order->seats);//展示order内容
    printf("座位个数: %d\n", order->seat_number);//展示order内容
    printf("订单状态: %d\n", order->status);//展示order内容
    printf("订单时间: %s\n", order->time);//展示order内容
    printf("订单价格: %f\n", order->price);//展示order内容
    printf("-----------------");
    //movie_print(order->movie);//展示order内容
    // 可以根据需要显示更多的订单信息
}
void theater_print(const Theater* theater) {
    if (theater == NULL) {
        printf("Theater Data is NULL.\n");
        return;
    }

    printf("Theater ID: %s\n", theater->theater_id);
    printf("Theater Name: %s\n", theater->theater_name);
    printf("Capacity: %d\n", theater->theater_capacity);
    printf("Cinema ID: %s\n", theater->cinema_id);
    printf("Theater Type: %s\n", theater->theater_type);
    printf("------------\n");
}

void display_user_greet()
{
    printf("*************************************************\n");
    printf("*               欢迎使用云上影院                *\n");
    printf("*************************************************\n");
    printf("* 1. 电影购票                                   *\n");
    printf("* 2. 正在热映                                   *\n");
    printf("* 3. 我的订单                                   *\n");
    printf("* 4. 充值                                       *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void display_purchase_ticket()
{
    printf("*************************************************\n");
    printf("*                 电影购票                      *\n");
    printf("*************************************************\n");
    printf("* 1. 影片查询                                   *\n");
    printf("* 2. 影片+影院查询                              *\n");
    //printf("* 3. 优惠折扣                                   *\n");
    printf("* 3. 自定义查询                                 *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void admin_greet()
{
    printf("*************************************************\n");
    printf("*             欢迎使用电影院管理系统            *\n");
    printf("*************************************************\n");
    printf("* 1. 订单管理                                   *\n");
    printf("* 2. 影厅管理                                   *\n");
    printf("* 3. 场次管理                                   *\n");
    printf("* 4. 个人信息管理                               *\n");
    printf("* 5. 用户信息管理                               *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void display_admin_modify_info_menu()
{
    printf("*************************************************\n");
    printf("*               修改管理员信息                  *\n");
    printf("*************************************************\n");
    printf("* 1. 修改ID                                     *\n");
    printf("* 2. 修改姓名                                   *\n");
    printf("* 3. 修改电话                                   *\n");
    printf("* 4. 修改密码                                   *\n");
    printf("* 5. 修改邮箱                                   *\n");
    printf("*                                               *\n");
    printf("* 0. 退出                                       *\n");
    printf("*************************************************\n");
}

void admin_order_manage_greet()
{
    printf("*************************************************\n");
    printf("*                  订单管理                     *\n");
    printf("*************************************************\n");
    printf("* 1. 查看与统计用户订单                         *\n");
    printf("* 2. 订单搜索                                   *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void admin_theater_manage_greet()
{
    printf("*************************************************\n");
    printf("*                  影厅管理                     *\n");
    printf("*************************************************\n");
    printf("* 1. 添加影厅                                   *\n");
    printf("* 2. 查看影厅                                   *\n");
    //printf("* 3. 删除影厅                                   *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}
void display_admin_movie_manage_greet()
{
    printf("*************************************************\n");
    printf("*                  场次管理                     *\n");
    printf("*************************************************\n");
    printf("* 1. 智能排片                                   *\n");
    printf("* 2. 查看排片                                   *\n");
    printf("* 3. 自定义排片                                 *\n");
    printf("*                                               *\n");
    printf("* 0.退出                                        *\n");
    printf("*************************************************\n");
}


//场次操作菜单
void display_movie_operate_main_menu() {
    printf("\n==== 操作主菜单 ====\n");
    printf("1. 排序\n");
    printf("2. 筛选\n");
    printf("3. 查看与选择场次\n");
    printf("4. 查看影院在当前结果的收入\n\n");
    printf("0. 返回订单管理（重置操作结果）\n");

}

void display_user_movie_operate_main_menu() {
    printf("\n==== 操作主菜单 ====\n");
    printf("1. 排序\n");
    printf("2. 筛选\n");
    printf("3. 查看与选择场次\n\n");
    printf("0. 返回购票（重置操作结果）\n");

}

//管理员排序菜单
void display_admin_sort_menu() {
    printf("\n==== 排序菜单 ====\n");
    printf("1. 上座率 (降序)\n");
    printf("2. 价格 (升序)\n");
    printf("3. 场次收入 (降序)\n");
    printf("4. 开始时间 (升序)\n");
    printf("5. 剩余票数 (升序)\n\n");
    printf("0. 返回操作主菜单\n");
}
void display_user_sort_menu() {
    printf("\n==== 排序菜单 ====\n");
    printf("1. 价格 (升序)\n");
    printf("2. 开始时间 (升序)\n");
    printf("3. 剩余票数 (升序)\n\n");
    printf("0. 返回操作主菜单\n");
}
void display_admin_filter_menu() {
    printf("\n==== 筛选菜单 ====\n");
    printf("1. 时间段\n");
    printf("2. 已放映\n");
    printf("3. 未放映\n");
    printf("4. 当日日期\n");
    printf("5. 影片类型\n");
    printf("6. 电影院ID\n\n");
    printf("0. 返回操作主菜单\n");
}
void display_user_filter_menu() {
    printf("\n==== 筛选菜单 ====\n");
    printf("1. 时间段\n");
    printf("2. 影片类型\n");
    printf("3. 电影院\n");
    printf("4. 影厅类型\n\n");
    printf("0. 返回操作主菜单\n");
}