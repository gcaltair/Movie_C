#ifndef MOVIE_C_ORDER_H
#define MOVIE_C_ORDER_H
#define HASH_TABLE_SIZE 100
typedef struct User User;
typedef struct Movie Movie;
typedef struct Theater Theater;
typedef struct Cinema Cinema;
typedef struct Linked_string_list Linked_string_list;
typedef struct Order {
	char* orderID;
	User* usr;
	char* user_id;
	Movie* movie;
	char* movie_id;
	Theater* theater;
	Cinema* cinema;
	char* seats; //可以是二维数组？
	int seat_number;
	int status; //订单状态
	char* time;
	double price;
	struct Order* next;
	struct Order* hash_next;
}Order;
typedef struct Order_hash_table Order_hash_table;

Order* order_create(Order_hash_table* hashTable, const char* orderID, User* usr, const char* user_id, Movie* movie, const char* movie_id,
	Theater* theater, Cinema* cinema, const char* seats, int seat_number, int status, const char* time);
void order_add_to_list(Order** head, Order* new_order);

Order* order_find_by_id(Order* head, char* orderID);

void order_show(const Order* order);

void order_show_all(Order* head);

typedef struct Order_hash_table {
	Order* table[HASH_TABLE_SIZE];
} Order_hash_table;

//订座位，seats为用户视角下，故行与列均-1
// 座位  0 ：不在影院座次范围内
//       1 ：可购买
//       2 ：已售出
//       3 ：因与已售出的座位相隔一个座位导致无法售出
// 创建并初始化一个 Order_hash_table
Order_hash_table* order_hash_table_create();

// 初始化哈希表，将所有的指针设置为 NULL
void init_order_hash_table(Order_hash_table* ht);

// 使用哈希表将订单插入表中
void insert_order_to_hash_table(Order_hash_table* ht, Order* order);

// 在哈希表中查找订单，通过 orderID 查找
Order* find_order_in_hash_table(Order_hash_table* ht, char* orderID);
#endif //MOVIE_C_ORDER_H

//创建并初始化座位图
int(*seat_map_generation())[26];

//展示座位图
void seat_map_show(int(*seat_map)[26]);

//查询场次剩余座位数
int get_remaining_ticket(int(*seat_map)[26]);

//以字符串形式返回当前年月日（2024-8-31）
char* get_current_day();

//获取当前时间
char* get_current_time();

//生成orderID
char* get_orderID();


//时间大小比较
//return 0 ： a在b之前
//       1 ： a与b同时
//       2 ： a在b之后
int time_compare(char* a, char* b);

//历史场次时间冲突判断
//return 0 :查询失败
//       1 :无冲突
//       2 :已购买过该场次的票
//       3 :当天已经购买五个场次的票
//       4 :购买多个影片场次时间冲突
int history_order_time_check(User* usr, Movie* movie, Order_hash_table* hashTable);

//通过seats计算座位数
//retunr 0 : 计算失败
//       1 ：计算成功
int get_seat_number(char* seats);

//检验座位输入
//return NULL ：输入不合法
char* seats_input_check();

//座位数冲突判断
//return 0 : 获取位置信息失败
//       1 ; 订座成功 
//       5 : 剩余座位数不足或超过最大购票限额
//       6 ：输入两个相同的座位号。
//       7 ：不在影院座次范围内
//       8 ：座位已售出
//       9 ：与已售出的座位相隔一个座位
// 座位  0 ：不在影院座次范围内
//       1 ：可购买
//       2 ：已售出
//       3 ：因与已售出的座位相隔一个座位导致无法售出
int saets_check(char* seats, int(*seat_map)[26]);

//判断订单能否生成
//return 0 :查询失败
//       1 :生成订单成功
//       2 :当天已经购买五个场次的票
//       3 :已经购买过该影片的票
//       4 :购买多个影片场次时间冲突
//       5 :剩余座位数不足或超过最大购票限额
//       6 :输入两个相同的座位号。
//       7 :不在影院座次范围内
//       8 :座位已售出
//       9 :与已售出的座位相隔一个座位
int order_generation(User* usr, char* seats, Movie* movie, int(*seat_map)[26], Order_hash_table* hashTable);

//订单价格计算
//discount（用户） = 1 - 0.05 * history_seat_number
//return 0      :计算失败
//       >0 :计算成功
double get_order_price(Order* order, Order_hash_table* hashTable);

//判断余额是否充足
//return 0 : 查询失败
//       1 ：余额充足
//       2 ：余额不足
int balance_check(Order* order, Order_hash_table* hashTable);

//欠款计算
//return 0  ：不欠款
//       >0 ：欠款金额
double  get_debt(Order* order, Order_hash_table* hashTable);

//充值
void recharge(User* usr, double money);

//付款
//return 0 ：查询错误
//       1 : 付款成功
// 座位  0 ：不在影院座次范围内
//       1 ：可购买
//       2 ：已售出
//       3 ：因与已售出的座位相隔一个座位导致无法售出
int process_pay(Order* order, int(*seat_map)[26], Order_hash_table* hashTable);

//取消订单
void order_cancel(Order* order);

//退票
//return 0 ：退款失败
//       1 : 退款成功
// 座位  0 ：不在影院座次范围内
//       1 ：可购买
//       2 ：已售出
//       3 ：因与已售出的座位相隔一个座位导致无法售出
int ticket_refund(Order* order, int(*seat_map)[26], Order_hash_table* hashTable);

//展示用户所有订单（不包括已经取消的订单）
void order_show_mini(User* usr, Order_hash_table* hashTable);

//计算影厅收入
double get_movie_income(User* usr, Movie* movie, Order_hash_table* hashTable);

//智能推荐座位图
//返回距离F13，F14最近的可购买的三个位置，返回格式"F11-F12-F15",进入函数前需判断余票数大于等于3
char* get_great_seats(int(*seat_map)[26]);

//释放order_list
void order_list_free(Order* head);

//
Order* order_copy_info(Order* order);

//
Order* order_list_create_by_user(User* usr, Order_hash_table* order_hash_table);