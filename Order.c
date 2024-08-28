//
// Created by G on 2024/8/27.
//
//
// Created by G on 2024/8/27.
//
//折扣活动：movie->discount = 1 - 0.1*（用户已购买的票数）-0.05*(用户单次购买座位数)
#include "Order.h"
#include <time.h>
#include <stdlib.h>

Order* get_tail(Order* head) {
	Order* current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	return current;
}

Order* add_order(User* usr, Movie* movie) {
	Order* head = get_head();
	Order* tail = get_tail(head);
	Order* temp = head;
	if (movie->remaining_ticket <= 0) {
		printf("该场次剩余票数不足，请选择其他场次。\n");
		return head;
	}
	int start_day, start_hour, start_minute, end_day, end_hour, end_minute;
	sscanf(movie->start_time, "%d %d %d", &start_day, &start_hour, &start_minute);
	sscanf(movie->end_time, "%d %d %d", &end_day, &end_hour, &end_minute);
	long st = start_day * 1440 + start_hour * 60 + start_minute;
	long et = end_day * 1440 + end_hour * 60 + end_minute;
	int count = 0;
	while (temp != NULL) {
		if (strcmp(temp->usr->userID, usr->userID) == 0) {
			count++;
			int hstart_day, hstart_hour, hstart_minute, hend_day, hend_hour, hend_minute;
			sscanf(temp->movie->start_time, "%d %d %d", &hstart_day, &hstart_hour, &hstart_minute);
			sscanf(temp->movie->end_time, "%d %d %d", &hend_day, &hend_hour, &hend_minute);
			long hst = hstart_day * 1440 + hstart_hour * 60 + hstart_minute;
			long het = hend_day * 1440 + hend_hour * 60 + hend_minute;
			if (movie->session_number == temp->movie->session_number) {
				printf("您已经购买过该场次的票，请确定是否购买。取消购买请按0，继续购买请按1。\n");
				int j;
				scanf("%d", &j);
				if (j != 0) {
					return head;
				}
			}
			if (hst <= et && het >= et && movie->session_number != temp->movie->session_number) {
				printf("该场次与您已经购买的场次冲突，请确定是否购买。取消购买请按0，继续购买请按1。\n");
				int j;
				scanf("%d", &j);
				if (j != 0) {
					return head;
				}
			}
		}
		temp = temp->next;
	}
	if (count > 4) {
		printf("您已经达到当日订票限额，请在明日再行购票。\n");
		return head;
	}
	printf("请输入您要购买的座位数（最多可购买三个且不能和已售出的座位仅相隔一个座位，取消购票请按0。\n");
	int seat_number;
	while ((scanf("%d", &seat_number) != EOF)) {
		if (seat_number == 0) {
			return head;
		}
		if (seat_number > 3) {
			printf("您已超过最多购买的座位数，请重新输入，取消购票请按0。\n");
		}
		else {
			break;
		}
	}
	movie->discount = 1 - 0.1 * count - 0.05 * seat_number;
	printf("请确认购票信息并进入付款界面。\n");
	while ((usr->user_balance < movie->price * movie->discount)) {
		printf("账户余额不足，您当前的余额为：%f,还需充值的金额为：%f.请进行充值。充值请按0，放弃充值请按1。\n", usr->user_balance, movie->price * movie->discount - usr->user_balance);
		int k;
		scanf("%d", &k);
		if (k) {
			return head;
		}
		else {
			printf("请输入您的充值金额并完成充值。\n");
			double n;
			scanf("%lf", &n);
			usr->user_balance += n;
			if (usr->user_balance >= movie->price * movie->discount) {
				printf("充值成功。\n");
				break;
			}
		}
	}
	printf("继续付款请按0，放弃付款请按1。\n");
	int m;
	scanf("%d", &m);
	if (m) {
		return head;
	}
	else {
		usr->user_balance -= movie->price * movie->discount;
		printf("已为您完成付款，您的账户余额为%f。\n", usr->user_balance);
	}
	movie->discount = 1;
	tail->next = (Order*)malloc(sizeof(Order));
	if (tail->next == NULL) {
		return head;
	}
	srand(time(NULL));
	tail->next->oderID = rand();
	tail->next->usr = usr;
	tail->next->movie = movie;
	tail->next->movie->remaining_ticket -= 1;
	tail->next->theater = movie->play_theater;
	//int seats
	tail->next->status = 1;
	time_t current_time = time(NULL);
	strcpy(tail->next->time, ctime(&current_time));
	tail = tail->next;
	return head;
}

void user_historyorder(User* usr) {
	Order* head = get_head();
	Order* tail = get_tail(head);
	Order* temp = head;
	int count = 0;
	while (temp != NULL) {
		if (temp->usr->userID == usr->userID) {
			count++;
			printf("您的历史订单如下\n%d.订单号： %s 影院： %s\n影厅： %s\n电影名： %s\n开始时间： %s\n结束时间： %s\n订单编号药： %d\n", count, temp->orderID, temp->cinema->cinema_name, temp->theater->theater_name, temp->movie->movie_name, temp->movie->start_time, temp->movie->end_time, temp->status);
		}
		temp = temp->next;
	}
	if (count == 0) {
		printf("未查询到您的订单。\n");
	}
}
