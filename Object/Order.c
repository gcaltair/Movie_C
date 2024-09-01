#include <stdlib.h>
#include <string.h>
#include "Order.h"
#include "User.h"
#include "Cinema.h"
#include "Movie.h"
#include "Theater.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "../hash.txt"
#include"../Structure File/linked_list.h"
//订座位，seats为用户视角下，故行与列均-1
// 座位  0 ：不在影院座次范围内
//       1 ：可购买
//       2 ：已售出
//       3 ：因与已售出的座位相隔一个座位导致无法售出
//status 1 : 生成订单已付款
//       2 ：生成订单未付款
//       3 ：取消订单
//       4 ：退款

Order* order_create(Order_hash_table* hashTable, const char* orderID, User* usr, const char* user_id, Movie* movie, const char* movie_id,
	Theater* theater, Cinema* cinema, const char* seats, int seat_number, const char* time) {
	Order* new_order = (Order*)malloc(sizeof(Order));
	if (new_order == NULL) {
		printf("Memory allocation failed.\n");
		return NULL;
	}

	new_order->orderID = strdup(orderID);
	new_order->usr = usr;
	new_order->user_id = strdup(user_id);
	new_order->movie = movie;
	new_order->movie_id = strdup(movie_id);
	new_order->theater = theater;
	new_order->cinema = cinema;
	new_order->seats = strdup(seats);
	new_order->seat_number = seat_number;
	new_order->status = 2;
	new_order->time = strdup(time);
	vector_push_back((new_order->usr->my_order), new_order->orderID);
	new_order->next = NULL;
	new_order->hash_next = NULL;

	insert_order_to_hash_table(hashTable, new_order);
	return new_order;
}
// 将一个订单添加到链表中
void order_add_to_list(Order** head, Order* new_order) {
	if (*head == NULL) {
		*head = new_order;
		return;
	}

	Order* temp = new_order;
	temp->next = (*head);
	(*head) = temp;
}

// 通过订单ID查找订单
Order* order_find_by_id(Order* head, char* orderID) {
	while (head != NULL) {
		if (strcmp(head->orderID, orderID) == 0) {
			return head;
		}
		head = head->next;
	}
	return NULL;
}

// 显示单个订单信息
void order_show(const Order* order) {
	if (order == NULL) {
		printf("Order not found.\n");
		return;
	}
	printf("OrderID: %s\n", order->orderID);
	printf("UserID: %s\n", order->user_id);
	printf("Movie ID: %s\n", order->movie_id);
	printf("Seats: %s\n", order->seats);
	printf("Seat number: %d\n", order->seat_number);
	printf("Status: %d\n", order->status);
	printf("Time: %s\n", order->time);
	movie_show(order->movie);
	// 可以根据需要显示更多的订单信息
}

// 显示所有订单信息
void order_show_all(Order* head) {
	while (head != NULL) {
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
int (*seat_map_generation())[26] {
	int (*seat_map)[26] = (int(*)[26])malloc(9 * sizeof(*seat_map));
	for (int line = 0; line < 9; line++) {
		for (int row = 0; row < 26; row++) {
			if (row - line >= 18 || row + line <= 7) {
				seat_map[line][row] = 0;
			}
			else {
				seat_map[line][row] = 1;
			}
		}
	}
	return seat_map;
}

//展示座位图
void seat_map_show(int (*seat_map)[26]) {
	printf("   ");
	for (int i = 1; i <= 26; i++) {
		if (i > 9) {
			printf("%d ", i);
		}
		else {
			printf("%d  ", i);
		}
	}
	printf("\n");
	for (int line = 0; line < 9; line++) {
		printf("%c ", line + 65);
		for (int row = 0; row < 26; row++) {
			if (seat_map[line][row] == 1) {
				printf("*  ");
			}
			else {
				printf("   ");
			}
		}
		printf("\n");
	}
}

//查询场次剩余座位数
int get_remaining_ticket(int (*seat_map)[26]) {
	int remaining_ticket = 0;
	for (int line = 0; line < 9; line++) {
		for (int row = 0; row < 26; row++) {
			if (seat_map[line][row] == 1) {
				remaining_ticket++;
			}
		}
	}
	return remaining_ticket++;
}

//以字符串形式返回当前年月日（2024-8-31）
char* get_current_day() {
	time_t now = time(0);
	struct tm* ltm = localtime(&now);
	char* current_time;
	int current_year = 1900 + ltm->tm_year;
	int current_month = 1 + ltm->tm_mon;
	int current_day = ltm->tm_mday;
	sprintf(current_time, "%d-%d-%d", current_year, current_month, current_day);
}

//获取当前时间生成订单号
char* get_current_time() {
	time_t now = time(0);
	struct tm* ltm = localtime(&now);
	int current_year = 1900 + ltm->tm_year;
	int current_month = 1 + ltm->tm_mon;
	int current_day = ltm->tm_mday;
	int current_hour = ltm->tm_hour;
	int current_min = ltm->tm_min;
	int current_sec = ltm->tm_sec;
	char* current_time = (char*)malloc(20 * sizeof(char));
	if (current_time == NULL) {
		return NULL;
	}
	sprintf(current_time, "%d-%d-%d %d:%d:%d", current_year, current_month, current_day, current_hour, current_min, current_sec);
	return current_time;
}

////生成orderID
char* get_orderID() {
	srand(time(0));
	int randomNumber = rand();
	char* rand;
	sprintf(rand, "-%d", randomNumber);
	char* orderID = strcat(get_current_time(), rand);
	return orderID;
}


//历史场次时间冲突判断
//return 0 :查询失败
//       1 :无冲突
//       2 :已购买过该场次的票
//       3 :当天已经购买五个场次的票
int history_order_time_check(User* usr, Movie* movie, Order_hash_table* hashTable) {
	int count = 0;
	int history_order_year[100];
	int history_order_month[100];
	int history_order_day[100];
	Linked_string_list* movie_id_list = NULL;
	if (!usr) { printf("User is NULL!\n"); return 0; }
	Linked_string_list* order = usr->my_order;
	while (order != NULL) {
		Order* order_find = find_order_in_hash_table(hashTable, order->id);
		if (order_find->status != 1) continue;
		if ((sscanf(order_find->time, "%d-%d-%d", &history_order_year[count], &history_order_month[count], &history_order_day[count])) != 3) {
			printf("%d\n", history_order_day[count]);
			printf("%s", order_find->time);
			return 0;
		}
		string_direct_add_to_list(&movie_id_list, order_find->movie_id);
		count++;
		order = order->next;
	}
	int current_year, current_month, current_day;
	sscanf(get_current_day(), "%d-%d-%d", &current_year, &current_month, &current_day);
	int history_order_count = 0;
	for (int i = count; i > 0; i--) {
		if (history_order_year[i] == current_year && history_order_month[i] == current_month && history_order_day[i] == current_day && strcmp(movie_id_list->id, movie->movie_id)) {
			history_order_count++;
		}
		if (strcmp(movie_id_list->id, movie->movie_id) == 0) {
			return 2;
		}
		movie_id_list = movie_id_list->next;
	}
	free_list(movie_id_list);

	if (history_order_count >= 5) {
		return 3;
	}
	return 1;
}

//通过seats计算座位数
//retunr 0 : 计算失败
//       >=1：计算成功
int get_seat_number(char* seats) {
	int seat_number = 0;
	char* seats_copy = strdup(seats);
	char* token = strtok(seats_copy, "-");
	int i = 1;
	while (token != NULL) {
		i = 0;
		seat_number++;
		token = strtok(NULL, "-");
	}
	if (i) {
		return 0;
	}
	return seat_number;
}

//座位数冲突判断
//return 0 : 获取位置信息失败
//       1 ; 订座成功 
//       4 : 剩余座位数不足或超过最大购票限额
//       5 ：输入两个相同的座位号。
//       6：不在影院座次范围内
//       7 ：座位已售出
//       8 ：与已售出的座位相隔一个座位
int saets_check(char* seats, int (*seat_map)[26]) {
	int seat_number;
	if (get_seat_number(seats)) {
		seat_number = get_seat_number(seats);
	}
	else {
		return 0;
	}
	if (seat_number > get_remaining_ticket(seat_map) || seat_number > 3) {
		return 4;
	}

	char* seats_copy = strdup(seats);
	char* token = strtok(seats_copy, "-");
	char charline[3];
	int line[3];
	int row[3];
	for (int i = 0; i < seat_number; i++) {
		sscanf(token, "%c%d", &charline[i], &row[i]);
		token = strtok(NULL, "-");
	}
	for (int i = 0; i < seat_number; i++) {
		line[i] = charline[i];
		line[i] -= 64;
	}
	for (int i = 0; i < seat_number; i++) {
		for (int j = i + 1; j < seat_number; j++) {
			if (line[i] == line[j] && row[i] == row[j]) {
				return 5;
			}
		}
	}
	for (int i = 0; i < seat_number; i++) {
		if ((seat_map[line[i] - 1][row[i] - 1]) == 0) {
			return 6;
		}
		if ((seat_map[line[i] - 1][row[i] - 1]) == 1) {
			continue;
		}
		if ((seat_map[line[i] - 1][row[i] - 1]) == 2) {
			return 7;
		}
		if ((seat_map[line[i] - 1][row[i] - 1]) == 3) {
			return 8;
		}
	}
	return 1;

}

//判断订单能否生成
//return 0 :查询失败
//       1 :生成订单成功
//       2 :当天已经购买五个场次的票
//       3 :已经购买过该影片的票
//       4 : 剩余座位数不足或超过最大购票限额
//       5 ：输入两个相同的座位号。
//       6：不在影院座次范围内
//       7 ：座位已售出
//       8 ：与已售出的座位相隔一个座位
int order_generation(User* usr, char* seats, Movie* movie, int (*seat_map)[26], Order_hash_table* hashTable) {
	if (history_order_time_check(usr, movie, hashTable) != 1) {
		return history_order_time_check(usr, movie, hashTable);
	}
	if (saets_check(seats, seat_map) != 1) {
		return saets_check(seats, seat_map);
	}
	return 1;
}

//discount计算
//discount = 1 - 0.05 * history_seat_number
//return 0      :计算失败
//       >=0。5 :计算成功
double get_discount(Order* order, Order_hash_table* hashTable) {
	Linked_string_list* order_find = order->usr->my_order;
	int history_seat_number = 0;
	int i;
	double discount;
	while (order_find != NULL) {
		if (strcmp(order_find->id, order->orderID) == 0) {
			order_find = order_find->next;
			i = 0;
			break;
		}
		order_find = order_find->next;
	}
	if (i) {
		return 0;
	}
	while (order_find != NULL) {
		Order* order = find_order_in_hash_table(hashTable, order_find->id);
		if (order->status == 1) {
			history_seat_number += order->seat_number;
		}
		order_find = order_find->next;
	}
	discount = 1 - 0.05 * history_seat_number;
	if (discount <= 0.5) {
		discount = 0.5;
	}
	return discount;
}

//取消订单
//return 2 ：订单状态不合法
//       1 ：取消成功
int order_cancel(Order* order) {
	if (order->status != 2) {
		return 0;
	}
	else {
		order->status = 3;
		return 1;
	}
}

//充值
void recharge(Order* order, double money) {
	order->usr->user_balance += money;
}

//判断余额是否充足
//return 0 : 查询失败
//       1 ：余额充足
//       2 ：余额不足
int balanece_check(Order* order, Order_hash_table* hashTable) {
	double discount;
	if (get_discount(order, hashTable)) {
		discount = get_discount(order, hashTable);
	}
	else {
		return 0;
	}
	if (order->usr->user_balance >= discount * order->seat_number * order->movie->price) {
		return 1;
	}
	else {
		return 2;
	}
}

//付款
//return 0 ：查询错误
//       1 : 付款成功
//       2 ：订单状态不合法
//       3 : 余额不足
int process_pay(Order* order, int (*seat_map)[26], Order_hash_table* hashTable) {
	if (order->status != 2) {
		return 2;
	}
	double discount;
	if (get_discount(order, hashTable)) {
		discount = get_discount(order, hashTable);
	}
	else {
		return 0;
	}
	char* seats_copy = strdup(order->seats);
	char* token = strtok(seats_copy, "-");
	char charline[3];
	int line[3];
	int row[3];
	for (int i = 0; i < order->seat_number; i++) {
		sscanf(token, "%c%d", &charline[i], &row[i]);
		token = strtok(NULL, "-");
	}
	for (int i = 0; i < order->seat_number; i++) {
		line[i] = charline[i];
		line[i] -= 64;
	}
	for (int i = 0; i < order->seat_number; i++) {
		if (row[i] == 1) {
			seat_map[line[i] - 1][row[i] - 1] = 2;
			seat_map[line[i] - 1][row[i]] = 3;
			continue;
		}
		if (row[i] == 26) {
			seat_map[line[i] - 1][row[i] - 1] = 2;
			seat_map[line[i] - 1][row[i] - 2] = 3;
			continue;
		}
		else {
			if (seat_map[line[i] - 1][row[i]] == 1) {
				seat_map[line[i] - 1][row[i]] = 3;
			}
			if (seat_map[line[i] - 1][row[i] - 2] == 1) {
				seat_map[line[i] - 1][row[i] - 2] = 3;
			}
			continue;
		}
	}
	if (order->usr->user_balance >= discount * order->seat_number * order->movie->price) {
		order->usr->user_balance -= discount * order->seat_number * order->movie->price;
		order->movie->remaining_ticket = get_remaining_ticket(seat_map);
		order->status = 1;
		return 1;
	}
	else {
		return 3;
	}
}

//展示用户所有订单（不包括已经取消的订单）
void order_show_mini(User* usr, Order_hash_table* hashTable) {
	if (usr->my_order = NULL) {
		printf("您没有历史订单。\n");
	}
	printf("您的历史订单如下：\n");
	int history_order_count = 0;
	Linked_string_list* order = usr->my_order;
	while (order != NULL) {
		Order* order_find = find_order_in_hash_table(hashTable, order);
		if (order_find->status == 3) {
			order = order->next;
			continue;
		}
		history_order_count++;
		printf("%d.\n", history_order_count);
		printf("orderID:%s\n", order_find->orderID);
		printf("user_id:%s\n", order_find->user_id);
		printf("movie_id:%s\n", order_find->movie_id);
		printf("seats:%s\n", order_find->seats);
		printf("seat_number:%d\n", order_find->seat_number);
		switch (order_find->status) {
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
		printf("time:%s\n", order_find->time);
		order = order->next;
	}
}


//退票
//return 0 ：查询错误
//       1 : 退款成功
//       2 ：订单状态不合法
int ticket_refund(Order* order, int (*seat_map)[26], Order_hash_table* hashTable) {
	if (order->seat_number != 1) {
		return 2;
	}
	double discount;
	if (get_discount(order, hashTable)) {
		discount = get_discount(order, hashTable);
	}
	else {
		return 0;
	}
	char* seats_copy = strdup(order->seats);
	char* token = strtok(seats_copy, "-");
	char charline[3];
	int line[3];
	int row[3];
	for (int i = 0; i < order->seat_number; i++) {
		sscanf(token, "%c%d", &charline[i], &row[i]);
		token = strtok(NULL, "-");
	}
	for (int i = 0; i < order->seat_number; i++) {
		line[i] = charline[i];
		line[i] -= 64;
	}
	for (int i = 0; i < order->seat_number; i++) {
		if (row[i] == 1) {
			seat_map[line[i] - 1][row[i] - 1] = 1;
			if (seat_map[line[i] - 1][row[i] + 1] != 2) {
				seat_map[line[i] - 1][row[i]] = 1;
			}
			continue;
		}
		if (row[i] == 26) {
			seat_map[line[i] - 1][row[i] - 1] = 1;
			if (seat_map[line[i] - 1][row[i] - 3] != 2) {
				seat_map[line[i] - 1][row[i] - 2] = 1;
			}
			continue;
		}
		else {
			seat_map[line[i] - 1][row[i] - 1] = 1;
			if (seat_map[line[i] - 1][row[i] + 1] != 2) {
				seat_map[line[i] - 1][row[i]] = 1;
			}
			if (seat_map[line[i] - 1][row[i] - 3] != 2) {
				seat_map[line[i] - 1][row[i] - 2] = 1;
			}
			continue;
		}
	}
	order->usr->user_balance += discount * order->seat_number * order->movie->price;
	order->movie->remaining_ticket = get_remaining_ticket(seat_map);
	order->status = 4;
	return 1;
}

//计算影厅收入
double get_movie_income(User* usr, Movie* movie, Order_hash_table* hashTable) {
	User* head = usr;
	double movie_income = 0;
	while (head != NULL) {
		Order* order_find = find_order_in_hash_table(hashTable, head->my_order->id);
		while (order_find != NULL) {
			if (order_find->movie->movie_id == movie->movie_id && order_find->status == 1) {
				double discount = get_discount(order_find, hashTable);
				movie_income += order_find->seat_number * discount * movie->price;
			}
			order_find = order_find->next;
		}
		head = head->next;
	}
	return movie_income;
}
