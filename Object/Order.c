#include <stdlib.h>
#include <string.h>
#include "Order.h"
#include "User.h"
#include "Cinema.h"
#include "Movie.h"
#include "Theater.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include "../hash.txt"
#include "../Structure File/linked_list.h"
#include "../Structure File/String_set.h"
//����λ��seatsΪ�û��ӽ��£��������о�-1
// ��λ  0 ������ӰԺ���η�Χ��
//       1 ���ɹ���
//       2 �����۳�
//       3 ���������۳�����λ���һ����λ�����޷��۳�
//status 1 : ���ɶ����Ѹ���
//       2 �����ɶ���δ����
//       3 ��ȡ������
//       4 ���˿�
Order* order_create(Order_hash_table* hashTable, const char* orderID, User* usr, const char* user_id, Movie* movie, const char* movie_id,
	Theater* theater, Cinema* cinema, const char* seats, int seat_number, int status, const char* time) {
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
	new_order->status = status;
	new_order->time = strdup(time);
	new_order->next = NULL;
	new_order->hash_next = NULL;

	string_direct_add_to_list(&(new_order->usr->my_order), new_order->orderID);

	insert_order_to_hash_table(hashTable, new_order);
	return new_order;
}
// ��һ��������ӵ�������
void order_add_to_list(Order** head, Order* new_order) {
	if (*head == NULL) {
		*head = new_order;
		return;
	}

	Order* temp = new_order;
	temp->next = (*head);
	(*head) = temp;
}

// ͨ������ID���Ҷ���
Order* order_find_by_id(Order* head, char* orderID) {
	while (head != NULL) {
		if (strcmp(head->orderID, orderID) == 0) {
			return head;
		}
		head = head->next;
	}
	return NULL;
}

// ��ʾ����������Ϣ
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
	// ���Ը�����Ҫ��ʾ����Ķ�����Ϣ
}

// ��ʾ���ж�����Ϣ
void order_show_all(Order* head) {
	while (head != NULL) {
		order_show(head);
		printf("\n");
		head = head->next;
	}
}

// ��ʼ����ϣ�������е�ָ������Ϊ NULL
void init_order_hash_table(Order_hash_table* ht) {
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		ht->table[i] = NULL;
	}
}

// ��������ʼ��һ�� Order_hash_table
Order_hash_table* order_hash_table_create() {
	Order_hash_table* ht = (Order_hash_table*)malloc(sizeof(Order_hash_table));
	if (!ht) {
		return NULL;
	}
	init_order_hash_table(ht);
	return ht;
}

// ʹ�ù�ϣ�������������
void insert_order_to_hash_table(Order_hash_table* ht, Order* order) {
	uint32_t index = hash(order->orderID, strlen(order->orderID), 0x9747b28c);
	//printf("add key%s\n",order->orderID);
	order->hash_next = ht->table[index];  // �����ϣ��ͻ�����¶��������ϣ����ͷ��
	ht->table[index] = order;
}

// �ڹ�ϣ���в��Ҷ�����ͨ�� orderID ����
Order* find_order_in_hash_table(Order_hash_table* ht, char* orderID) {
	uint32_t index = hash(orderID, strlen(orderID), 0x9747b28c);
	Order* order = ht->table[index];
	while (order) {
		if (strcmp(order->orderID, orderID) == 0) {
			return order;  // �ҵ�ƥ��Ķ���������ָ��
		}
		order = order->hash_next;  // ʹ�� hash_next ָ��������ҹ�ϣ�����е���һ������
	}
	return NULL;  // ���δ�ҵ������� NULL
}

//��������ʼ����λͼ
int(*seat_map_generation())[26] { //����һ�������ε���λͼ����һ����10����λ���ڶ�����12����λ����������14����λ���ھ�����26����λ
	int(*seat_map)[26] = (int(*)[26])malloc(9 * sizeof(*seat_map));//����ռ�
	for (int line = 0; line < 9; line++) {
		for (int row = 0; row < 26; row++) {
			if (row - line >= 18 || row + line <= 7) {//������ѧ��������������״
				seat_map[line][row] = 0;// ��λ  0 ������ӰԺ���η�Χ�� 
			}
			else {
				seat_map[line][row] = 1;// 1���ɹ���
			}
		}
	}
	return seat_map;
	}
	//չʾ��λͼ
		void seat_map_show(int(*seat_map)[26]) {
		printf("  ");//��λͼ�������
		for (int i = 1; i <= 26; i++) {
			if (i > 9) {//���Ǹ�λ���ȶ�λ��ռ�ռ�С���������
				printf("%d ", i);//��λͼ�������
			}
			else {
				printf("%d  ", i);//��λͼ�������
			}
		}
		printf("\n");
		for (int line = 0; line < 9; line++) {
			printf("%c ", line + 65);//������ת��Ϊ��ĸ
			for (int row = 0; row < 26; row++) {
				if (seat_map[line][row] == 1) {
					printf("*  ");//��λͼ������ۣ�*����ɹ���
				}
				else {
					printf("   ");//��λͼ�������
				}

			}
			printf("\n");
		}
	}

	//��ѯ����ʣ����λ��
	int get_remaining_ticket(int(*seat_map)[26]) {
		int remaining_ticket = 0;
		for (int line = 0; line < 9; line++) {//������λͼ
			for (int row = 0; row < 26; row++) {
				if (seat_map[line][row] == 1) {//�ɹ�����λ���ۼ�
					remaining_ticket++;
				}
			}
		}
		return remaining_ticket++;
	}

	//���ַ�����ʽ���ص�ǰ�����գ�2024-8-31��
	char* get_current_day() {
		time_t now = time(0);//time()��localtime()������ȡ��ǰʱ��
		struct tm* ltm = localtime(&now);
		int current_year = 1900 + ltm->tm_year;
		int current_month = 1 + ltm->tm_mon;
		int current_day = ltm->tm_mday;
		char* current_time = (char*)malloc(11 * sizeof(char));
		if (current_time == NULL) {
			return NULL;
		}
		sprintf(current_time, "%02d-%02d-%02d", current_year, current_month, current_day);//���ַ�����ʽ��������������ȡ
		return current_time;
	}

	//��ȡ��ǰʱ�����ɶ�����
	char* get_current_time() {
		time_t now = time(0);;//time()��localtime()������ȡ��ǰʱ��
		struct tm* ltm = localtime(&now);
		int current_year = 1900 + ltm->tm_year;//��ǰ���
		int current_month = 1 + ltm->tm_mon;//��ǰ�·�
		int current_day = ltm->tm_mday;//��ǰ����
		int current_hour = ltm->tm_hour;//��ǰСʱ
		int current_min = ltm->tm_min;//��ǰ����
		int current_sec = ltm->tm_sec;//��ǰ��
		char* current_time = (char*)malloc(20 * sizeof(char));
		if (current_time == NULL) {
			return NULL;
		}
		sprintf(current_time, "%02d-%02d-%02d %02d:%02d:%02d", current_year, current_month, current_day, current_hour, current_min, current_sec);//���ַ�����ʽ��������������ȡ
		return current_time;
	}

	//����orderID
	char* get_orderID() {
		srand(time(0));//���ǵ�����ʹ��ʱ����λ�����ſ��ܳ����ظ��������������󲹳�һ�������
		int randomNumber = rand();
		char rand[100];//��ʼ���ַ�����С
		sprintf(rand, "-%d", randomNumber);//�������ת��Ϊ�ַ����ĸ�ʽ
		char* orderID = strcat(get_current_time(), rand);//�����ַ�������orderID
		return orderID;
	}

	//Waring:δ��ȫ����
	//��ʷ����ʱ���ͻ�ж�
	//return 0 :��ѯʧ��
	//       1 :�޳�ͻ
	//       2 :�ѹ�����ó��ε�Ʊ
	//       3 :�����Ѿ�����������ε�Ʊ
	int history_order_time_check(User* usr, Movie* movie, Order_hash_table* hashTable) {

		int count = 0;
		int history_order_year[100];//��ʼ���ַ�����С
		int history_order_month[100];//��ʼ���ַ�����С
		int history_order_day[100];//��ʼ���ַ�����С
		Linked_string_list* movie_id_list = NULL;//��ʼ��ͷ���
		if (!usr)
		{
			printf("user not exist");
			return;
		}
		Linked_string_list* my_order = usr->my_order;//����ͷ����ֹ�����
		StringSet* movie_id_set = create_string_set();
		while (my_order) {//��������
			Order* order_find = find_order_in_hash_table(hashTable, my_order->id);
			//if(order_find->next->movie->start_time)
			if (order_find->status != 1) {//ȷ������Ϊ�Ѹ���״̬
				my_order = my_order->next;
				continue;
			}
			string_set_add(movie_id_set, order_find->movie_id);
			if ((sscanf(order_find->time, "%d-%d-%d", &history_order_year[count], &history_order_month[count], &history_order_day[count])) != 3) {//��ȡ��ʷ�������ڣ��Ӷ��ж��µ�ʱ��
				return 0;
			}
			string_direct_add_to_list(&movie_id_list, order_find->movie_id);//��movie_id_listΪͷ��㣬�����¼movie_id
			count++;
			my_order = my_order->next;
		}
		int current_year, current_month, current_day;//���뵱ǰʱ��ɹ���֤
		if (sscanf(get_current_day(), "%d-%d-%d", &current_year, &current_month, &current_day) != 3) {
			return 0;
		}
		int history_order_count = 0;
		for (int i = count; i > 0; i--) {
			if (history_order_year[i] == current_year && history_order_month[i] == current_month && history_order_day[i] == current_day && string_set_add(movie_id_set,movie->movie_id)) {//ǰ�����ж�ȷ������Ϊ�����µ������һ���ж�ȷ�����Ǹó���
				history_order_count++;
			}
			if (strcmp(movie_id_list->id, movie->movie_id) == 0) {//�ж��Ƿ�����ͬӰƬ��Ʊ
				return 2;
			}
			movie_id_list = movie_id_list->next;
		}
		//free_list(movie_id_list);//�ͷ��ڴ�ռ�

		if (history_order_count >= 5) {
			return 3;
		}
		return 1;
	}

	//ͨ��seats������λ��
	//retunr 0 : ����ʧ��
	//       >=1������ɹ�
	int get_seat_number(char* seats) {
		int seat_number = 0;//��ʼ����λ��Ϊ0
		char* seats_copy = strdup(seats);
		char* token = strtok(seats_copy, "-");//seats��ʽ"A1-Ba-C1",ʹ��seats_copy����������зֶ�
		int i = 1;//�жϵ㣬�����жϼ����Ƿ�ɹ�
		while (token != NULL) {
			i = 0;//�����жϵ�
			seat_number++;
			token = strtok(NULL, "-");
		}
		if (i) {
			return 0;
		}
		return seat_number;
	}

	//��λ����ͻ�ж�
	//return 0 : ��ȡλ����Ϣʧ��
	//       1 ; �����ɹ� 
	//       4 : ʣ����λ������򳬹����Ʊ�޶�
	//       5 ������������ͬ����λ�š�
	//       6�� ����ӰԺ���η�Χ��
	//       7 ����λ���۳�
	//       8 �������۳�����λ���һ����λ
	int saets_check(char* seats, int(*seat_map)[26]) {
		int seat_number;
		if (get_seat_number(seats)) {//ͨ�������seats������λ�������ٲ���������
			seat_number = get_seat_number(seats);
		}
		else {
			return 0;
		}
		if (seat_number > get_remaining_ticket(seat_map) || seat_number > 3) {//ͬ�ⶩ��������λ��������������ڳ���ʣ����λ��
			return 4;
		}

		char* seats_copy = strdup(seats);//���ƴ����seats
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

	//�ж϶����ܷ�����
	//return 0 :��ѯʧ��
	//       1 :���ɶ����ɹ�
	//       2 :�����Ѿ�����������ε�Ʊ
	//       3 :�Ѿ��������ӰƬ��Ʊ
	//       4 : ʣ����λ������򳬹����Ʊ�޶�
	//       5 ������������ͬ����λ�š�
	//       6������ӰԺ���η�Χ��
	//       7 ����λ���۳�
	//       8 �������۳�����λ���һ����λ
	int order_generation(User* usr, char* seats, Movie* movie, int(*seat_map)[26], Order_hash_table* hashTable) {
		if (history_order_time_check(usr, movie, hashTable) != 1) {
			return history_order_time_check(usr, movie, hashTable);
		}
		if (saets_check(seats, seat_map) != 1) {
			return saets_check(seats, seat_map);
		}
		return 1;
	}

	//�����۸����
	//discount���û��� = 1 - 0.05 * history_seat_number
	//return 0      :����ʧ��
	//       >0 :����ɹ�
	double get_order_price(Order* order, Order_hash_table* hashTable) {
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
		if (discount <= 0.8) {
			discount = 0.8;
		}
		double order_price = discount * order->seat_number * order->movie->price * order->movie->discount;
		return order_price;
	}

	//�ж�����Ƿ����
	//return 0 : ��ѯʧ��
	//       1 ��������
	//       2 ������
	int balanece_check(Order* order, Order_hash_table* hashTable) {
		double order_price;
		if (get_order_price(order, hashTable)) {
			order_price = get_order_price(order, hashTable);
		}
		else {
			return 0;
		}
		if (order->usr->user_balance >= order_price) {
			return 1;
		}
		else {
			return 2;
		}
	}

	//Ƿ�����
	//return 0  ����Ƿ��
	//       >0 ��Ƿ����
	double  get_debt(Order* order, Order_hash_table* hashTable) {
		double debt = get_order_price(order, hashTable) - order->usr->user_balance;
		if (debt > 0) {
			return debt;
		}
		else {
			return 0;
		}
	}

	//��ֵ
	void recharge(Order* order, double money) {
		order->usr->user_balance += money;
	}

	//����
	//return 0 ����ѯ����
	//       1 : ����ɹ�
	//       2 ������״̬���Ϸ�
	int process_pay(Order* order, int(*seat_map)[26], Order_hash_table* hashTable) {
		if (order->status != 2) {
			return 2;
		}
		double order_price;
		if (get_order_price(order, hashTable)) {
			order_price = get_order_price(order, hashTable);
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
			seat_map[line[i] - 1][row[i] - 1] = 2;
		}
		for (int i = 0; i < order->seat_number; i++) {
			if (row[i] == 1 && seat_map[line[i] - 1][row[i]] == 1) {
				seat_map[line[i] - 1][row[i]] = 3;
				continue;
			}
			if (row[i] == 26 && seat_map[line[i] - 1][row[i] - 2] == 1) {
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
		order->usr->user_balance -= order_price;
		order->movie->remaining_ticket = get_remaining_ticket(seat_map);
		order->status = 1;
		return 1;
	}

	//ȡ������
	//return 2 ������״̬���Ϸ�
	//       1 ��ȡ���ɹ�
	int order_cancel(Order* order) {
		if (order->status != 2) {
			return 0;
		}
		else {
			order->status = 3;
			return 1;
		}
	}

	//��Ʊ
	//return 0 ����ѯ����
	//       1 : �˿�ɹ�
	//       2 ������״̬���Ϸ�
	int ticket_refund(Order* order, int(*seat_map)[26], Order_hash_table* hashTable) {
		if (order->status != 1) {
			return 2;
		}
		double order_price;
		if (get_order_price(order, hashTable)) {
			order_price = get_order_price(order, hashTable);
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
			seat_map[line[i] - 1][row[i] - 1] = 3;
			printf("%d-%d", line[i], row[i]);
		}
		for (int line = 0; line < 9; line++) {
			for (int row = 0; row < 26; row++) {
				if (seat_map[line][row] == 3) {
					if (row == 0 && seat_map[line][row + 1] != 2) {
						seat_map[line][row] = 1;
					}
					if (row == 25 && seat_map[line][row - 1] != 2) {
						seat_map[line][row] = 1;
					}
					else {
						if (seat_map[line][row - 1] != 2 && seat_map[line][row + 1] != 2) {
							seat_map[line][row] = 1;
						}
					}
				}
			}
		}
		order->usr->user_balance += order_price;
		order->movie->remaining_ticket = get_remaining_ticket(seat_map);
		order->status = 4;
		return 1;
	}

	//չʾ�û����ж������������Ѿ�ȡ���Ķ�����
	void order_show_mini(User* usr, Order_hash_table* hashTable) {
		if (!usr) {
			printf("�û�������");
			return;
		}
		if (usr->my_order == NULL) {
			printf("��û����ʷ������\n");
		}
		printf("������ʷ�������£�\n");
		int history_order_count = 0;
		Linked_string_list* order = usr->my_order;
		while (order != NULL) {
			Order* order_find = find_order_in_hash_table(hashTable, order->id);
			if (!order_find) {
				printf("order find is null\n");
				return;
			}
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
				printf("�����Ѹ���\n");
				break;
			case 2:
				printf("����δ����\n");
				break;
			case 4:
				printf("�������˿�\n");
				break;
			}
			printf("time:%s\n", order_find->time);
			order = order->next;
		}
	}

	//����Ӱ������
	double get_movie_income(User* usr, Movie* movie, Order_hash_table* hashTable) {
		User* head = usr;
		double movie_income = 0;
		while (head != NULL) {
			Order* order_find = find_order_in_hash_table(hashTable, head->my_order->id);
			while (order_find != NULL) {
				if (order_find->movie->movie_id == movie->movie_id && order_find->status == 1) {
					double order_price = get_order_price(order_find, hashTable);
					movie_income += order_price;
				}
				order_find = order_find->next;
			}
			head = head->next;
		}
		return movie_income;
	}

	//�����Ƽ���λͼ
	//���ؾ���F13��F14����Ŀɹ��������λ�ã����ظ�ʽ"F11-F12-F15",���뺯��ǰ���ж���Ʊ�����ڵ���3
	char* get_great_seats(int(*seat_map)[26]) {
		char* great_seats = (char*)malloc(12 * sizeof(char));
		if (great_seats == NULL) {
			return NULL;
		}
		great_seats[0] = '\0';
		int count = 0;
		int line_better[3];
		int row_better[3];
		for (double i = 0.5; i < 18; i++) {
			if (count >= 3) {
				break;
			}
			for (int line = 0; line < 9; line++) {
				if (count >= 3) {
					break;
				}
				for (int row = 0; row < 26; row++) {
					double difference = 1.0 * abs(line - 6) + fabs(1.0 * row - 13.5);
					if (count >= 3) {
						break;
					}
					if (seat_map[line][row] == 1 && fabs(difference - i) < 1e-6) {
						line_better[count] = line;
						row_better[count] = row;
						count++;
					}
				}
			}
		}

		for (int i = 0; i < count; i++) {
			char better[5];
			sprintf(better, "%c%d-", line_better[i] + 'A', row_better[i] + 1);
			strcat(great_seats, better);
		}

		size_t len = strlen(great_seats);
		if (len > 0) {
			great_seats[len - 1] = '\0';
		}

		return great_seats;
	}