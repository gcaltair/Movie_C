#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Order.h"
#include "User.h"
#include "Cinema.h"
#include "Movie.h"
#include "Theater.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../hash.txt"
#include "../Structure File/linked_list.h"
#include"../Structure File/String_set.h"
//订座位，seats为用户视角下，故行与列均-1
// 座位  0 ：不在影院座次范围内
//       1 ：可购买
//       2 ：已售出
//       3 ：因与已售出的座位相隔一个座位导致无法售出
//status 1 : 生成订单已付款
//       2 ：生成订单未付款
//       3 ：取消订单
//       4 ：退款
Order* order_create(Order_hash_table* hashTable, const char* orderID, User* usr, const char* user_id, Movie* movie, const char* movie_id,//传入创建订单所需参数
	Theater* theater, Cinema* cinema, const char* seats, int seat_number, int status, const char* time) {
	Order* new_order = (Order*)malloc(sizeof(Order));
	if (new_order == NULL) {//内存分配失败检验
		printf("Memory allocation failed.\n");
		return NULL;
	}
	new_order->orderID = strdup(orderID);//给order填入基本信息
	new_order->usr = usr;//给order填入基本信息
	new_order->user_id = strdup(user_id);//给order填入基本信息
	new_order->movie = movie;//给order填入基本信息
	new_order->movie_id = strdup(movie_id);//给order填入基本信息
	new_order->theater = theater;//给order填入基本信息
	new_order->cinema = cinema;//给order填入基本信息
	new_order->seats = strdup(seats);//给order填入基本信息
	new_order->seat_number = seat_number;//给order填入基本信息
	new_order->status = status;//给order填入基本信息
	new_order->time = strdup(time);//给order填入基本信息
	new_order->price = get_order_price(new_order, hashTable);//给order填入基本信息
	new_order->next = NULL;//给order填入基本信息
	new_order->hash_next = NULL;//给order填入基本信息
	string_direct_add_to_list(&(new_order->usr->my_order), new_order->orderID);//完善User结构体下的my_order链表
	insert_order_to_hash_table(hashTable, new_order);//插入哈希表
	return new_order;
}
// 将一个订单添加到链表中
void order_add_to_list(Order** head, Order* new_order) {
	if (*head == NULL) {//判断头结点地址是否为空
		*head = new_order;
		return;
	}

	Order* temp = new_order;//复制new_order指针
	temp->next = (*head);//链表头插
	(*head) = temp;//更改头结点位置
}

// 通过订单ID查找订单
Order* order_find_by_id(Order* head, char* orderID) {
	while (head != NULL) {//遍历链表
		if (strcmp(head->orderID, orderID) == 0) {
			return head;
		}
		head = head->next;
	}
	return NULL;//查找失败返回NULL
}

// 显示单个订单信息
void order_show(const Order* order) {
	if (order == NULL) {//order找不到提示
		printf("Order not found.\n");
		return;
	}
	printf("OrderID: %s\n", order->orderID);//展示order内容
	printf("UserID: %s\n", order->user_id);//展示order内容
	printf("Movie ID: %s\n", order->movie_id);//展示order内容
	printf("Seats: %s\n", order->seats);//展示order内容
	printf("Seat number: %d\n", order->seat_number);//展示order内容
	printf("Status: %d\n", order->status);//展示order内容
	printf("Time: %s\n", order->time);//展示order内容
	printf("Price:%f\n", order->price);//展示order内容
	movie_show(order->movie);//展示order内容
	// 可以根据需要显示更多的订单信息
}

// 显示所有订单信息
void order_show_all(Order* head) {
	while (head != NULL) {//遍历链表
		order_show(head);
		printf("\n");
		head = head->next;
	}
}

// 初始化哈希表，将所有的指针设置为 NULL
void init_order_hash_table(Order_hash_table* ht) {
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		ht->table[i] = NULL;
	}
}

// 创建并初始化一个 Order_hash_table
Order_hash_table* order_hash_table_create() {
	Order_hash_table* ht = (Order_hash_table*)malloc(sizeof(Order_hash_table));
	if (!ht) {
		return NULL;
	}
	init_order_hash_table(ht);
	return ht;
}

// 使用哈希表将订单插入表中
void insert_order_to_hash_table(Order_hash_table* ht, Order* order) {
	uint32_t index = hash(order->orderID, strlen(order->orderID), 0x9747b28c);
	//printf("add key%s\n",order->orderID);
	order->hash_next = ht->table[index];  // 处理哈希冲突，将新订单插入哈希链表头部
	ht->table[index] = order;
}

// 在哈希表中查找订单，通过 orderID 查找
Order* find_order_in_hash_table(Order_hash_table* ht, char* orderID) {
	uint32_t index = hash(orderID, strlen(orderID), 0x9747b28c);
	Order* order = ht->table[index];
	while (order) {
		if (strcmp(order->orderID, orderID) == 0) {
			return order;  // 找到匹配的订单，返回指针
		}
		order = order->hash_next;  // 使用 hash_next 指针继续查找哈希链表中的下一个订单
	}
	return NULL;  // 如果未找到，返回 NULL
}

//创建并初始化座位图
int(*seat_map_generation())[26] { //创建一个正梯形的座位图，第一行设10个座位，第二行设12个座位，第三行设14个座位至第九行设26个座位
	int(*seat_map)[26] = (int(*)[26])malloc(9 * sizeof(*seat_map));//分配空间
	for (int line = 0; line < 9; line++) {
		for (int row = 0; row < 26; row++) {
			if (row - line >= 18 || row + line <= 7) {//经过数学计算限制梯形形状
				seat_map[line][row] = 0;// 座位  0 ：不在影院座次范围内 
			}
			else {
				seat_map[line][row] = 1;// 1：可购买
			}
		}
	}
	return seat_map;
	}
	//展示座位图
		void seat_map_show(int(*seat_map)[26]) {
		printf("  ");//座位图输出美观
		for (int i = 1; i <= 26; i++) {
			if (i > 9) {//考虑个位数比二位数占空间小，输出美观
				printf("%d ", i);//座位图输出美观
			}
			else {
				printf("%d  ", i);//座位图输出美观
			}
		}
		printf("\n");
		for (int line = 0; line < 9; line++) {
			printf("%c ", line + 65);//把行数转化为字母
			for (int row = 0; row < 26; row++) {
				if (seat_map[line][row] == 1) {
					printf("*  ");//座位图输出美观，*代表可购买
				}
				else {
					printf("   ");//座位图输出美观
				}

			}
			printf("\n");
		}
	}

	//查询场次剩余座位数
	int get_remaining_ticket(int(*seat_map)[26]) {
		int remaining_ticket = 0;
		for (int line = 0; line < 9; line++) {//遍历座位图
			for (int row = 0; row < 26; row++) {
				if (seat_map[line][row] == 1) {//可购买座位数累加
					remaining_ticket++;
				}
			}
		}
		return remaining_ticket;
	}

	//以字符串形式返回当前年月日（2024-8-31）
	char* get_current_day() {
		time_t now = time(0);//time()和localtime()函数获取当前时间
		struct tm* ltm = localtime(&now);
		int current_year = 1900 + ltm->tm_year;
		int current_month = 1 + ltm->tm_mon;
		int current_day = ltm->tm_mday;
		char* current_time = (char*)malloc(11 * sizeof(char));
		if (current_time == NULL) {
			return NULL;
		}
		sprintf(current_time, "%d-%02d-%02d", current_year, current_month, current_day);//以字符串格式输出，方便后续读取
		return current_time;
	}

	//获取当前时间生成订单号
	char* get_current_time() {
		time_t now = time(0);;//time()和localtime()函数获取当前时间
		struct tm* ltm = localtime(&now);
		int current_year = 1900 + ltm->tm_year;//当前年份
		int current_month = 1 + ltm->tm_mon;//当前月份
		int current_day = ltm->tm_mday;//当前日期
		int current_hour = ltm->tm_hour;//当前小时
		int current_min = ltm->tm_min;//当前分钟
		int current_sec = ltm->tm_sec;//当前秒
		char* current_time = (char*)malloc(20 * sizeof(char));
		if (current_time == NULL) {
			return NULL;
		}
		sprintf(current_time, "%d-%02d-%02d %02d:%02d:%02d", current_year, current_month, current_day, current_hour, current_min, current_sec);//以字符串格式输出，方便后续读取
		return current_time;
	}

	//生成orderID
	char* get_orderID() {
		srand(time(0));//考虑单纯的使用时间座位订单号可能出现重复的情况，故在其后补充一个随机数
		int randomNumber = rand();
		char rand[100];//初始化字符串大小
		sprintf(rand, "-%d", randomNumber);//将随机数转化为字符串的格式
		char* orderID = strcat(get_current_time(), rand);//连接字符串生成orderID
		return orderID;
	}

	//时间大小比较
	//return 0 ： 查询失败
	//       1 ： a在b之前
	//       2 ： a与b同时
	//       3 :  a在b之后
	int time_compare(char* a, char* b) {
		struct tm A_time = { 0 }, B_time = { 0 };//用于存储转化后的时间
		if (sscanf(a, "%d-%d-%d %d:%d:%d", &A_time.tm_year, &A_time.tm_mon, &A_time.tm_mday, &A_time.tm_hour, &A_time.tm_min, &A_time.tm_sec) != 6) {//
			return 0;
		}
		if (sscanf(b, "%d-%d-%d %d:%d:%d", &B_time.tm_year, &B_time.tm_mon, &B_time.tm_mday, &B_time.tm_hour, &B_time.tm_min, &B_time.tm_sec) != 6) {
			return 0;
		}
		A_time.tm_year -= 1900;
		A_time.tm_mon -= 1;
		B_time.tm_year -= 1900;
		B_time.tm_mon -= 1;
		time_t a_time = mktime(&A_time), b_time = mktime(&B_time);
		if (a_time < b_time) {
			return 1;
		}
		if (a_time == b_time) {
			return 2;
		}
		else {
			return 3;
		}
	}

	bool is_current_date(char* time)
	{
		char time_date[12];
		strncpy(time_date, time, 10);
		if (strcmp(time_date, get_current_day) != 0) return 0;
		return 1;
	}
	//历史场次时间冲突判断
	//return 0 :查询失败
	//       1 :无冲突
	//       2 :已购买过该场次的票
	//       3 :当天已经购买五个场次的票
	//       4 :购买多个影片场次时间冲突
	//       10 :又买重有冲突
	int history_order_time_check(User* usr, Movie* movie, Order_hash_table* hashTable)
	{
		StringSet* movie_id_set = create_string_set();
		int count = 0;
		bool hint1 = 0;
		bool hint2 = 0;
		if (!usr)
		{
			printf("user not exist");
			return;
		}

		Linked_string_list* order = usr->my_order;//复制头结点防止其更改
		while (order != NULL) {//遍历链表
			Order* order_find = find_order_in_hash_table(hashTable, order->id);
			if (order_find->status != 1) {//确定订单为已付款状态
				order = order->next;
				continue;
			}

			if (is_current_date(order_find->time))
			{
				if (order_find->movie->start_min <= movie->start_min && order_find->movie->end_min >= movie->start_min) hint2 = 1;

				if (string_set_size(movie_id_set) <= 5) {
					if (!string_set_add(movie_id_set, order_find->movie_id)) hint1 = 1;

				}
				else return 3;
			}
			order = order->next;
		}
		if (hint1 && !hint2) return 2;
		if (!hint1 && hint2) return 4;
		if (hint1 && hint2) return 10;
		return 1;
	}

	//通过seats计算座位数
	//retunr 0 : 计算失败
	//       >=1：计算成功
	int get_seat_number(char* seats) {
		int seat_number = 0;//初始化座位数为0
		char* seats_copy = strdup(seats);
		char* token = strtok(seats_copy, "-");//seats格式"A1-Ba-C1",使用seats_copy函数对其进行分段
		int i = 1;//判断点，用于判断计算是否成功
		while (token != NULL) {
			i = 0;//更改判断点
			seat_number++;
			token = strtok(NULL, "-");
		}
		if (i) {
			return 0;
		}
		return seat_number;
	}


	//检验座位输入
	//return NULL ：输入不合法
	char* seats_input_check() {
		char* seats = (char*)malloc(100 * sizeof(char));  // 分配足够的内存
		if (seats == NULL) {
			return NULL;  // 确保内存分配成功
		}
		while (1) {
			printf("请输入座位信息 (格式: A1-B1-C1): ");
			if (scanf("%99s", seats) != 1) {  //读入为字符串检验
				free(seats);  // 释放内存
				return NULL;
			}
			char* seats_copy = (char*)malloc((strlen(seats) + 1) * sizeof(char));  // 分配存储复制字符串的内存
			if (seats_copy == NULL) {
				free(seats);
				return NULL;
			}
			strcpy(seats_copy, seats);
			char* token = strtok(seats_copy, "-");//以-分割输入的字符串
			
			while (token != NULL) {
				if (token == NULL || strlen(token) < 2) {//先判断长度，最短长度为2
					return NULL;
				}
				if (isalpha(token[0]) == 0) {//确保第一个字符为字母
					return NULL;
				}
				for (int i = 1; i < strlen(token); i++) {
					if (isdigit(token[i]) == 0) { // 确保后面的字符是数字
						return NULL;
					}
				}
				token = strtok(NULL, "-");
			}
			free(seats_copy);  // 释放复制的内存
			break;
		}
		return seats;
	}

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
	int saets_check(char* seats, int(*seat_map)[26]) {
		int seat_number;
		if (get_seat_number(seats)) {//通过传入的seats计算座位数，减少参数传入量
			seat_number = get_seat_number(seats);
		}
		else {
			return 0;
		}
		if (seat_number > get_remaining_ticket(seat_map) || seat_number > 3) {//同意订单包含座位数超过三个或大于场次剩余座位数
			return 5;
		}

		char* token = strtok(seats, "-");//利用strtok函数对其进行分段
		char charline[3];//用于存储座位信息
		int line[3];//用于存储座位信息
		int row[3];//用于存储座位信息
		for (int i = 0; i < seat_number; i++) {
			sscanf(token, "%c%d", &charline[i], &row[i]);//记录座位信息
			token = strtok(NULL, "-");
		}
		for (int i = 0; i < seat_number; i++) {
			line[i] = charline[i];//因行数读入是字母，转为数字形式
			line[i] -= 64;
		}
		for (int i = 0; i < seat_number; i++) {
			for (int j = i + 1; j < seat_number; j++) {
				if (line[i] == line[j] && row[i] == row[j]) {//循环，判断是否输入两个相同座位号
					return 6;
				}
			}
		}
		for (int i = 0; i < seat_number; i++) {
			if ((seat_map[line[i] - 1][row[i] - 1]) == 0) {//0代表座位图中梯形两侧位置
				return 7;
			}
			if ((seat_map[line[i] - 1][row[i] - 1]) == 1) {//1代表该座位可购买，故继续检验后续座位
				continue;
			}
			if ((seat_map[line[i] - 1][row[i] - 1]) == 2) {//2代表已售出
				return 8;
			}
			if ((seat_map[line[i] - 1][row[i] - 1]) == 3) {//3代表与已售出的座位相隔一个座位
				return 9;
			}
		}
		return 1;//循环结束座位都可选择即返回1

	}

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
	int order_generation(User* usr, char* seats, Movie* movie, int(*seat_map)[26], Order_hash_table* hashTable) {
		if (history_order_time_check(usr, movie, hashTable) != 1) {//分别调用历史场次冲突判断函数和座位冲突函数判断两个函数，并返回对应值
			return history_order_time_check(usr, movie, hashTable);
		}
		if (saets_check(seats, seat_map) != 1) {
			return saets_check(seats, seat_map);
		}
		return 1;
	}

	//订单价格计算
	//discount（用户） = 1 - 0.05 * history_seat_number
	//return 0  :计算失败
	//       >0 :计算成功
	double get_order_price(Order* order, Order_hash_table* hashTable) {
		Linked_string_list* order_find = order->usr->my_order;//找到用户订单链表
		int history_seat_number = 0;//初始化为0，方便用户无历史订单情况
		double discount;
		while (order_find != NULL) {//遍历链表
			Order* order = find_order_in_hash_table(hashTable, order_find->id);
			if (order == NULL) {
				return 0;
			}
			if (order->status == 1) {//确保订单为已付款状态
				history_seat_number += order->seat_number;//每有一个已下单的订单，历史下单成功座位数加该订单座位数
			}
			order_find = order_find->next;
		}
		discount = 1 - 0.05 * history_seat_number;
		if (discount <= 0.8) {//确保打折不低于八折
			discount = 0.8;
		}
		double order_price = discount * order->seat_number * order->movie->price * order->movie->discount;//订单价格 = 用户折扣 * 座位数 * 电影票价 * 电影折扣
		return order_price;
	}

	//判断余额是否充足
	//return 0 : 余额不足
	//       1 ：余额充足
	int balance_check(Order* order, Order_hash_table* hashTable) {
		double order_price = order->price;

		if (order->usr->user_balance >= order_price) {//比较订单价格与用户余额大小
			return 1;
		}
		else {
			return 0;
		}
	}

	//欠款计算
	//return 0  ：不欠款
	//       >0 ：欠款金额
	double  get_debt(Order* order, Order_hash_table* hashTable) {
		double debt = get_order_price(order, hashTable) - order->usr->user_balance;//计算该订单票价与用户余额之差
		if (debt > 0) {
			return debt;
		}
		else {
			return 0;
		}
	}

	//充值
	void recharge(User* usr, double money) {
		usr->user_balance += money;
	}

	//付款
	//return 0 ：查询错误
	//       1 : 付款成功
	// 座位  0 ：不在影院座次范围内
	//       1 ：可购买
	//       2 ：已售出
	//       3 ：因与已售出的座位相隔一个座位导致无法售出
	int process_pay(Order* order, int(*seat_map)[26], Order_hash_table* hashTable) {
		char* token = strtok(order->seats, "-");//利用strtok函数对其进行分段
		char charline[3];//用于存储座位信息
		int line[3];//用于存储座位信息
		int row[3];//用于存储座位信息
		for (int i = 0; i < order->seat_number; i++) {
			if (sscanf(token, "%c%d", &charline[i], &row[i]) != 2) {
				return 0;
			}
			token = strtok(NULL, "-");
		}
		for (int i = 0; i < order->seat_number; i++) {//因行数读入是字母，转为数字形式
			line[i] = charline[i];
			line[i] -= 64;
		}
		for (int i = 0; i < order->seat_number; i++) {
			seat_map[line[i] - 1][row[i] - 1] = 2;//seats为用户视角下，故行与列均需-1，先更改其为已购买状态，再更改后续座位
		}
		for (int i = 0; i < order->seat_number; i++) {
			if (row[i] == 1 && seat_map[line[i] - 1][row[i]] == 1) {//考虑其在最左一列，左侧无座位
				seat_map[line[i] - 1][row[i]] = 3;//最左侧座位必定为I1,故不考虑右侧座位为“0”又因为订单已生成，故座位合法，故其右侧座位可直接改成”3”状态
				continue;
			}
			if (row[i] == 26 && seat_map[line[i] - 1][row[i] - 2] == 1) {//考虑其在最右一列，右侧无座位
				seat_map[line[i] - 1][row[i] - 2] = 3;//最右侧座位必定为I26,故不考虑左侧座位为“0”又因为订单已生成，故座位合法，故其左侧座位可直接改成”3”状态
				continue;
			}
			else {//对于剩余左右两侧均有座位的座位
				if (seat_map[line[i] - 1][row[i]] == 1) {//因座位右侧可能出现“0”状态的座位，且不可能出现“2”状态座位，故只判断为“1”状态下
					seat_map[line[i] - 1][row[i]] = 3;
				}
				if (seat_map[line[i] - 1][row[i] - 2] == 1) {//因座位左侧可能出现“0”状态的座位，且不可能出现“2”状态座位，故只判断为“1”状态下
					seat_map[line[i] - 1][row[i] - 2] = 3;
				}
				continue;
			}
		}
		order->usr->user_balance -= order->price;//修改用户余额
		order->movie->remaining_ticket = get_remaining_ticket(seat_map);//刷新余票数
		order->status = 1;//更改订单状态为已付款状态
		return 1;
	}

	//取消订单
	void order_cancel(Order* order) {
		order->status = 3;
	}

	//退票
	//return 0 ：查询错误
	//       1 : 退款成功
	// 座位  0 ：不在影院座次范围内
	//       1 ：可购买
	//       2 ：已售出
	//       3 ：因与已售出的座位相隔一个座位导致无法售出
	int ticket_refund(Order* order, int(*seat_map)[26], Order_hash_table* hashTable) {
		char* token = strtok(order->seats, "-");//利用strtok函数对其进行分段
		char charline[4];//用于存储座位信息
		int line[3];//用于存储座位信息
		int row[3];//用于存储座位信息
		for (int i = 0; i < order->seat_number; i++) {
			if (sscanf(token, "%c%d", &charline[i], &row[i]) != 2) {
				return 0;
			}
			token = strtok(NULL, "-");
		}
		for (int i = 0; i < order->seat_number; i++) {//因行数读入是字母，转为数字形式
			line[i] = charline[i];
			line[i] -= 64;
		}
		for (int i = 0; i < order->seat_number; i++) {//先更改退票座位为3状态，此处3状态无任何意义，只是代表其状态存疑（因为会出现同时退F12-F13的状态）
			seat_map[line[i] - 1][row[i] - 1] = 3;
		}
		for (int line = 0; line < 9; line++) {//刷新座位图，遍历整个二维数组
			for (int row = 0; row < 26; row++) {
				if (seat_map[line][row] == 3) {//只有座位状态为3的座位需要更改（座位状态为1的不会因为退票而更改作为状态）
					if (row == 0 && seat_map[line][row + 1] != 2) {//最左侧一列左侧无座位，那么当其右侧不是已购买的座位，则可购买
						seat_map[line][row] = 1;
					}
					if (row == 25 && seat_map[line][row - 1] != 2) {//最右侧一列右侧无座位，那么当其左侧不是已购买的座位，则可购买
						seat_map[line][row] = 1;
					}
					else {
						if (seat_map[line][row - 1] != 2 && seat_map[line][row + 1] != 2) {//其余座位需其左右两侧均不是已购买的状态
							seat_map[line][row] = 1;
						}
					}
				}
			}
		}
		order->usr->user_balance += order->price;//更改用户余额
		order->movie->remaining_ticket = get_remaining_ticket(seat_map);//刷新剩余票数
		order->status = 4;//更改订单状态
		return 1;
	}

	//展示用户所有订单（不包括已经取消的订单）
	void order_show_mini(User* usr, Order_hash_table* hashTable) {
		if (usr == NULL) {//输入检验
			printf("用户不存在");
			return;
		}
		if (usr->my_order == NULL) {//排除其没有历史订单的情况
			printf("您没有历史订单。\n");
		}
		printf("您的历史订单如下：\n");
		int history_order_count = 0;//此处为了输出美观清晰，记录是第几个订单
		Linked_string_list* order = usr->my_order;
		while (order != NULL) {
			Order* order_find = find_order_in_hash_table(hashTable, order->id);
			if (order_find == NULL) {
				printf("查询失败.\n");
				return;
			}
			if (order_find->status == 3) {//不输出已经取消的订单
				order = order->next;
				continue;
			}
			history_order_count++;
			printf("%d.\n", history_order_count);//输出订单信息
			printf("orderID:%s\n", order_find->orderID);//输出订单信息
			printf("user_id:%s\n", order_find->user_id);//输出订单信息
			printf("movie_id:%s\n", order_find->movie_id);//输出订单信息
			printf("seats:%s\n", order_find->seats);//输出订单信息
			printf("seat_number:%d\n", order_find->seat_number);//输出订单信息
			switch (order_find->status) {//输出订单信息
			case 1:
				printf("订单已付款\n");
				break;
			case 2:
				printf("订单未付款\n");
				break;
			case 4:
				printf("订单已退款\n");
				break;
			}
			printf("time:%s\n", order_find->time);//输出订单信息
			printf("price:%f\n", order_find->price);//输出订单信息
			order = order->next;
		}
	}

	//计算影厅收入
	double get_movie_income(User* usr, Movie* movie, Order_hash_table* hashTable) {
		User* head = usr;//展示传入的指针必须是头结点
		double movie_income = 0;//初始化收入值
		while (head != NULL) {//遍历User链表
			Order* order_find = find_order_in_hash_table(hashTable, head->my_order->id);
			while (order_find != NULL) {//遍历my_order链表
				if (order_find->movie->movie_id == movie->movie_id && order_find->status == 1) {//确保订单为已购买状态
					double order_price = order_find->price;
					movie_income += order_price;
				}
				order_find = order_find->next;
			}
			head = head->next;
		}
		return movie_income;
	}

	//智能推荐座位图
	//返回距离F13，F14最近的可购买的三个位置，返回格式"F11-F12-F15",进入函数前需判断余票数大于等于3
	char* get_great_seats(int(*seat_map)[26]) {
		char* great_seats = malloc(13 * sizeof(char));
		memset(great_seats, 0, 13 * sizeof(char));
		int count = 0;
		int line_better[3];//用于存储作为信息
		int row_better[3];//用于存储作为信息
		for (double i = 0.5; i < 18; i++) {//座位图是9行26列，认为第六行中间为最佳位置，可认为第6行，第13.5列，故用double值，最大差值为17.5，故i < 18
			if (count >= 3) {//找到三个后不再循环
				break;
			}
			for (int line = 0; line < 9; line++) {//遍历座位图
				if (count >= 3) {
					break;
				}
				for (int row = 0; row < 26; row++) {
					double difference = 1.0 * abs(line - 6) + fabs(1.0 * row - 13.5);//计算行数，列数到6-13.5距离
					if (count >= 3) {
						break;
					}
					if (seat_map[line][row] == 1 && fabs(difference - i) < 1e-6) {//得到的差值与differemce比较
						line_better[count] = line;
						row_better[count] = row;
						count++;
					}
				}
			}
		}

		for (int i = 0; i < count; i++) {//通过循环把得到的行列数增加到输出的字符串之后
			char better[4];
			sprintf(better, "%c%d-", line_better[i] + 'A', row_better[i] + 1);//需将返回的行数转化为字母的形式
			strcat(great_seats, better);
		}
		size_t len = strlen(great_seats);//删去结尾的 -
		great_seats[len - 1] = '\0';
		return great_seats;
	}

	//释放Order结构体
	void order_list_free(Order* head) {
		Order* temp = head;
		while (head != NULL) {
			temp = head;
			head = head->next;//释放orderID,user_id,movie_id,seats,time
			if (temp->orderID != NULL) {
				free(temp->orderID);
			}
			if (temp->user_id != NULL) {
				free(temp->user_id);
			}
			if (temp->movie_id != NULL) {
				free(temp->movie_id);
			}
			if (temp->seats != NULL) {
				free(temp->seats);
			}
			if (temp->time != NULL) {
				free(temp->time);
			}
			//释放Order结构体本身
			free(temp);
			temp = NULL;
		}
	}

	Order* order_copy_info(Order* order) {
		Order* new_order = (Order*)malloc(sizeof(Order));
		if (new_order == NULL) {
			printf("Memory allocation falied\n");
			return NULL;
		}
		//复制当前的Order信息到新节点
		new_order->orderID = strdup(order->orderID);
		new_order->usr = order->usr;
		new_order->user_id = strdup(order->user_id);
		new_order->movie = order->movie;
		new_order->movie_id = strdup(order->movie_id);
		new_order->cinema = order->cinema;
		new_order->theater = new_order->theater;
		new_order->seats = strdup(order->seats);
		new_order->seat_number = order->seat_number;
		new_order->status = new_order->status;
		new_order->time = strdup(order->time);
		new_order->price = order->price;
		new_order->next = NULL;
		new_order->hash_next = NULL;
		return new_order;
	}

	Order* order_list_create_by_user(User* usr, Order_hash_table* order_hash_table) {
		Order* new_head = NULL;
		Linked_string_list* head_order = usr->my_order;
		while (head_order != NULL) {
			Order* order_find = find_order_in_hash_table(order_hash_table, head_order->id);
			if (order_find != NULL) {
				printf("orderID %s order list create failed\n", head_order->id);
				_sleep(10000);
			}
			Order* new_order = order_copy_info(order_find);
			order_add_to_list(&new_head, new_order);
			head_order = head_order->next;
		}
		return new_head;
	}