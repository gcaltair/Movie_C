//
// Created by G on 2024/8/27.
//
//
// Created by G on 2024/8/27.
//
//�ۿۻ��movie->discount = 1 - 0.1*���û��ѹ����Ʊ����-0.05*(�û����ι�����λ��)
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
		printf("�ó���ʣ��Ʊ�����㣬��ѡ���������Ρ�\n");
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
				printf("���Ѿ�������ó��ε�Ʊ����ȷ���Ƿ���ȡ�������밴0�����������밴1��\n");
				int j;
				scanf("%d", &j);
				if (j != 0) {
					return head;
				}
			}
			if (hst <= et && het >= et && movie->session_number != temp->movie->session_number) {
				printf("�ó��������Ѿ�����ĳ��γ�ͻ����ȷ���Ƿ���ȡ�������밴0�����������밴1��\n");
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
		printf("���Ѿ��ﵽ���ն�Ʊ�޶�����������й�Ʊ��\n");
		return head;
	}
	printf("��������Ҫ�������λ�������ɹ��������Ҳ��ܺ����۳�����λ�����һ����λ��ȡ����Ʊ�밴0��\n");
	int seat_number;
	while ((scanf("%d", &seat_number) != EOF)) {
		if (seat_number == 0) {
			return head;
		}
		if (seat_number > 3) {
			printf("���ѳ�����๺�����λ�������������룬ȡ����Ʊ�밴0��\n");
		}
		else {
			break;
		}
	}
	movie->discount = 1 - 0.1 * count - 0.05 * seat_number;
	printf("��ȷ�Ϲ�Ʊ��Ϣ�����븶����档\n");
	while ((usr->user_balance < movie->price * movie->discount)) {
		printf("�˻����㣬����ǰ�����Ϊ��%f,�����ֵ�Ľ��Ϊ��%f.����г�ֵ����ֵ�밴0��������ֵ�밴1��\n", usr->user_balance, movie->price * movie->discount - usr->user_balance);
		int k;
		scanf("%d", &k);
		if (k) {
			return head;
		}
		else {
			printf("���������ĳ�ֵ����ɳ�ֵ��\n");
			double n;
			scanf("%lf", &n);
			usr->user_balance += n;
			if (usr->user_balance >= movie->price * movie->discount) {
				printf("��ֵ�ɹ���\n");
				break;
			}
		}
	}
	printf("���������밴0�����������밴1��\n");
	int m;
	scanf("%d", &m);
	if (m) {
		return head;
	}
	else {
		usr->user_balance -= movie->price * movie->discount;
		printf("��Ϊ����ɸ�������˻����Ϊ%f��\n", usr->user_balance);
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
			printf("������ʷ��������\n%d.�����ţ� %s ӰԺ�� %s\nӰ���� %s\n��Ӱ���� %s\n��ʼʱ�䣺 %s\n����ʱ�䣺 %s\n�������ҩ�� %d\n", count, temp->orderID, temp->cinema->cinema_name, temp->theater->theater_name, temp->movie->movie_name, temp->movie->start_time, temp->movie->end_time, temp->status);
		}
		temp = temp->next;
	}
	if (count == 0) {
		printf("δ��ѯ�����Ķ�����\n");
	}
}
