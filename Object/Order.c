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
//����λ��seatsΪ�û��ӽ��£��������о�-1
// ��λ  0 ������ӰԺ���η�Χ��
//       1 ���ɹ���
//       2 �����۳�
//       3 ���������۳�����λ���һ����λ�����޷��۳�
//status 1 : ���ɶ����Ѹ���
//       2 �����ɶ���δ����
//       3 ��ȡ������
//       4 ���˿�
Order* order_create(Order_hash_table* hashTable, const char* orderID, User* usr, const char* user_id, Movie* movie, const char* movie_id,//���봴�������������
	Theater* theater, Cinema* cinema, const char* seats, int seat_number, int status, const char* time) {
	Order* new_order = (Order*)malloc(sizeof(Order));
	if (new_order == NULL) {//�ڴ����ʧ�ܼ���
		printf("Memory allocation failed.\n");
		return NULL;
	}
	new_order->orderID = strdup(orderID);//��order���������Ϣ
	new_order->usr = usr;//��order���������Ϣ
	new_order->user_id = strdup(user_id);//��order���������Ϣ
	new_order->movie = movie;//��order���������Ϣ
	new_order->movie_id = strdup(movie_id);//��order���������Ϣ
	new_order->theater = theater;//��order���������Ϣ
	new_order->cinema = cinema;//��order���������Ϣ
	new_order->seats = strdup(seats);//��order���������Ϣ
	new_order->seat_number = seat_number;//��order���������Ϣ
	new_order->status = status;//��order���������Ϣ
	new_order->time = strdup(time);//��order���������Ϣ
	new_order->price = get_order_price(new_order, hashTable);//��order���������Ϣ
	new_order->next = NULL;//��order���������Ϣ
	new_order->hash_next = NULL;//��order���������Ϣ
	string_direct_add_to_list(&(new_order->usr->my_order), new_order->orderID);//����User�ṹ���µ�my_order����
	insert_order_to_hash_table(hashTable, new_order);//�����ϣ��
	return new_order;
}
// ��һ��������ӵ�������
void order_add_to_list(Order** head, Order* new_order) {
	if (*head == NULL) {//�ж�ͷ����ַ�Ƿ�Ϊ��
		*head = new_order;
		return;
	}

	Order* temp = new_order;//����new_orderָ��
	temp->next = (*head);//����ͷ��
	(*head) = temp;//����ͷ���λ��
}

// ͨ������ID���Ҷ���
Order* order_find_by_id(Order* head, char* orderID) {
	while (head != NULL) {//��������
		if (strcmp(head->orderID, orderID) == 0) {
			return head;
		}
		head = head->next;
	}
	return NULL;//����ʧ�ܷ���NULL
}

// ��ʾ����������Ϣ
void order_show(const Order* order) {
	if (order == NULL) {//order�Ҳ�����ʾ
		printf("Order not found.\n");
		return;
	}
	printf("OrderID: %s\n", order->orderID);//չʾorder����
	printf("UserID: %s\n", order->user_id);//չʾorder����
	printf("Movie ID: %s\n", order->movie_id);//չʾorder����
	printf("Seats: %s\n", order->seats);//չʾorder����
	printf("Seat number: %d\n", order->seat_number);//չʾorder����
	printf("Status: %d\n", order->status);//չʾorder����
	printf("Time: %s\n", order->time);//չʾorder����
	printf("Price:%f\n", order->price);//չʾorder����
	movie_show(order->movie);//չʾorder����
	// ���Ը�����Ҫ��ʾ����Ķ�����Ϣ
}

// ��ʾ���ж�����Ϣ
void order_show_all(Order* head) {
	while (head != NULL) {//��������
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
		return remaining_ticket;
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
		sprintf(current_time, "%d-%02d-%02d", current_year, current_month, current_day);//���ַ�����ʽ��������������ȡ
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
		sprintf(current_time, "%d-%02d-%02d %02d:%02d:%02d", current_year, current_month, current_day, current_hour, current_min, current_sec);//���ַ�����ʽ��������������ȡ
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

	//ʱ���С�Ƚ�
	//return 0 �� ��ѯʧ��
	//       1 �� a��b֮ǰ
	//       2 �� a��bͬʱ
	//       3 :  a��b֮��
	int time_compare(char* a, char* b) {
		struct tm A_time = { 0 }, B_time = { 0 };//���ڴ洢ת�����ʱ��
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
	//��ʷ����ʱ���ͻ�ж�
	//return 0 :��ѯʧ��
	//       1 :�޳�ͻ
	//       2 :�ѹ�����ó��ε�Ʊ
	//       3 :�����Ѿ�����������ε�Ʊ
	//       4 :������ӰƬ����ʱ���ͻ
	//       10 :�������г�ͻ
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

		Linked_string_list* order = usr->my_order;//����ͷ����ֹ�����
		while (order != NULL) {//��������
			Order* order_find = find_order_in_hash_table(hashTable, order->id);
			if (order_find->status != 1) {//ȷ������Ϊ�Ѹ���״̬
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


	//������λ����
	//return NULL �����벻�Ϸ�
	char* seats_input_check() {
		char* seats = (char*)malloc(100 * sizeof(char));  // �����㹻���ڴ�
		if (seats == NULL) {
			return NULL;  // ȷ���ڴ����ɹ�
		}
		while (1) {
			printf("��������λ��Ϣ (��ʽ: A1-B1-C1): ");
			if (scanf("%99s", seats) != 1) {  //����Ϊ�ַ�������
				free(seats);  // �ͷ��ڴ�
				return NULL;
			}
			char* seats_copy = (char*)malloc((strlen(seats) + 1) * sizeof(char));  // ����洢�����ַ������ڴ�
			if (seats_copy == NULL) {
				free(seats);
				return NULL;
			}
			strcpy(seats_copy, seats);
			char* token = strtok(seats_copy, "-");//��-�ָ�������ַ���
			
			while (token != NULL) {
				if (token == NULL || strlen(token) < 2) {//���жϳ��ȣ���̳���Ϊ2
					return NULL;
				}
				if (isalpha(token[0]) == 0) {//ȷ����һ���ַ�Ϊ��ĸ
					return NULL;
				}
				for (int i = 1; i < strlen(token); i++) {
					if (isdigit(token[i]) == 0) { // ȷ��������ַ�������
						return NULL;
					}
				}
				token = strtok(NULL, "-");
			}
			free(seats_copy);  // �ͷŸ��Ƶ��ڴ�
			break;
		}
		return seats;
	}

	//��λ����ͻ�ж�
	//return 0 : ��ȡλ����Ϣʧ��
	//       1 ; �����ɹ� 
	//       5 : ʣ����λ������򳬹����Ʊ�޶�
	//       6 ������������ͬ����λ�š�
	//       7 ������ӰԺ���η�Χ��
	//       8 ����λ���۳�
	//       9 �������۳�����λ���һ����λ
	// ��λ  0 ������ӰԺ���η�Χ��
	//       1 ���ɹ���
	//       2 �����۳�
	//       3 ���������۳�����λ���һ����λ�����޷��۳�
	int saets_check(char* seats, int(*seat_map)[26]) {
		int seat_number;
		if (get_seat_number(seats)) {//ͨ�������seats������λ�������ٲ���������
			seat_number = get_seat_number(seats);
		}
		else {
			return 0;
		}
		if (seat_number > get_remaining_ticket(seat_map) || seat_number > 3) {//ͬ�ⶩ��������λ��������������ڳ���ʣ����λ��
			return 5;
		}

		char* token = strtok(seats, "-");//����strtok����������зֶ�
		char charline[3];//���ڴ洢��λ��Ϣ
		int line[3];//���ڴ洢��λ��Ϣ
		int row[3];//���ڴ洢��λ��Ϣ
		for (int i = 0; i < seat_number; i++) {
			sscanf(token, "%c%d", &charline[i], &row[i]);//��¼��λ��Ϣ
			token = strtok(NULL, "-");
		}
		for (int i = 0; i < seat_number; i++) {
			line[i] = charline[i];//��������������ĸ��תΪ������ʽ
			line[i] -= 64;
		}
		for (int i = 0; i < seat_number; i++) {
			for (int j = i + 1; j < seat_number; j++) {
				if (line[i] == line[j] && row[i] == row[j]) {//ѭ�����ж��Ƿ�����������ͬ��λ��
					return 6;
				}
			}
		}
		for (int i = 0; i < seat_number; i++) {
			if ((seat_map[line[i] - 1][row[i] - 1]) == 0) {//0������λͼ����������λ��
				return 7;
			}
			if ((seat_map[line[i] - 1][row[i] - 1]) == 1) {//1�������λ�ɹ��򣬹ʼ������������λ
				continue;
			}
			if ((seat_map[line[i] - 1][row[i] - 1]) == 2) {//2�������۳�
				return 8;
			}
			if ((seat_map[line[i] - 1][row[i] - 1]) == 3) {//3���������۳�����λ���һ����λ
				return 9;
			}
		}
		return 1;//ѭ��������λ����ѡ�񼴷���1

	}

	//�ж϶����ܷ�����
	//return 0 :��ѯʧ��
	//       1 :���ɶ����ɹ�
	//       2 :�����Ѿ�����������ε�Ʊ
	//       3 :�Ѿ��������ӰƬ��Ʊ
	//       4 :������ӰƬ����ʱ���ͻ
	//       5 :ʣ����λ������򳬹����Ʊ�޶�
	//       6 :����������ͬ����λ�š�
	//       7 :����ӰԺ���η�Χ��
	//       8 :��λ���۳�
	//       9 :�����۳�����λ���һ����λ
	int order_generation(User* usr, char* seats, Movie* movie, int(*seat_map)[26], Order_hash_table* hashTable) {
		if (history_order_time_check(usr, movie, hashTable) != 1) {//�ֱ������ʷ���γ�ͻ�жϺ�������λ��ͻ�����ж����������������ض�Ӧֵ
			return history_order_time_check(usr, movie, hashTable);
		}
		if (saets_check(seats, seat_map) != 1) {
			return saets_check(seats, seat_map);
		}
		return 1;
	}

	//�����۸����
	//discount���û��� = 1 - 0.05 * history_seat_number
	//return 0  :����ʧ��
	//       >0 :����ɹ�
	double get_order_price(Order* order, Order_hash_table* hashTable) {
		Linked_string_list* order_find = order->usr->my_order;//�ҵ��û���������
		int history_seat_number = 0;//��ʼ��Ϊ0�������û�����ʷ�������
		double discount;
		while (order_find != NULL) {//��������
			Order* order = find_order_in_hash_table(hashTable, order_find->id);
			if (order == NULL) {
				return 0;
			}
			if (order->status == 1) {//ȷ������Ϊ�Ѹ���״̬
				history_seat_number += order->seat_number;//ÿ��һ�����µ��Ķ�������ʷ�µ��ɹ���λ���Ӹö�����λ��
			}
			order_find = order_find->next;
		}
		discount = 1 - 0.05 * history_seat_number;
		if (discount <= 0.8) {//ȷ�����۲����ڰ���
			discount = 0.8;
		}
		double order_price = discount * order->seat_number * order->movie->price * order->movie->discount;//�����۸� = �û��ۿ� * ��λ�� * ��ӰƱ�� * ��Ӱ�ۿ�
		return order_price;
	}

	//�ж�����Ƿ����
	//return 0 : ����
	//       1 ��������
	int balance_check(Order* order, Order_hash_table* hashTable) {
		double order_price = order->price;

		if (order->usr->user_balance >= order_price) {//�Ƚ϶����۸����û�����С
			return 1;
		}
		else {
			return 0;
		}
	}

	//Ƿ�����
	//return 0  ����Ƿ��
	//       >0 ��Ƿ����
	double  get_debt(Order* order, Order_hash_table* hashTable) {
		double debt = get_order_price(order, hashTable) - order->usr->user_balance;//����ö���Ʊ�����û����֮��
		if (debt > 0) {
			return debt;
		}
		else {
			return 0;
		}
	}

	//��ֵ
	void recharge(User* usr, double money) {
		usr->user_balance += money;
	}

	//����
	//return 0 ����ѯ����
	//       1 : ����ɹ�
	// ��λ  0 ������ӰԺ���η�Χ��
	//       1 ���ɹ���
	//       2 �����۳�
	//       3 ���������۳�����λ���һ����λ�����޷��۳�
	int process_pay(Order* order, int(*seat_map)[26], Order_hash_table* hashTable) {
		char* token = strtok(order->seats, "-");//����strtok����������зֶ�
		char charline[3];//���ڴ洢��λ��Ϣ
		int line[3];//���ڴ洢��λ��Ϣ
		int row[3];//���ڴ洢��λ��Ϣ
		for (int i = 0; i < order->seat_number; i++) {
			if (sscanf(token, "%c%d", &charline[i], &row[i]) != 2) {
				return 0;
			}
			token = strtok(NULL, "-");
		}
		for (int i = 0; i < order->seat_number; i++) {//��������������ĸ��תΪ������ʽ
			line[i] = charline[i];
			line[i] -= 64;
		}
		for (int i = 0; i < order->seat_number; i++) {
			seat_map[line[i] - 1][row[i] - 1] = 2;//seatsΪ�û��ӽ��£��������о���-1���ȸ�����Ϊ�ѹ���״̬���ٸ��ĺ�����λ
		}
		for (int i = 0; i < order->seat_number; i++) {
			if (row[i] == 1 && seat_map[line[i] - 1][row[i]] == 1) {//������������һ�У��������λ
				seat_map[line[i] - 1][row[i]] = 3;//�������λ�ض�ΪI1,�ʲ������Ҳ���λΪ��0������Ϊ���������ɣ�����λ�Ϸ��������Ҳ���λ��ֱ�Ӹĳɡ�3��״̬
				continue;
			}
			if (row[i] == 26 && seat_map[line[i] - 1][row[i] - 2] == 1) {//������������һ�У��Ҳ�����λ
				seat_map[line[i] - 1][row[i] - 2] = 3;//���Ҳ���λ�ض�ΪI26,�ʲ����������λΪ��0������Ϊ���������ɣ�����λ�Ϸ������������λ��ֱ�Ӹĳɡ�3��״̬
				continue;
			}
			else {//����ʣ���������������λ����λ
				if (seat_map[line[i] - 1][row[i]] == 1) {//����λ�Ҳ���ܳ��֡�0��״̬����λ���Ҳ����ܳ��֡�2��״̬��λ����ֻ�ж�Ϊ��1��״̬��
					seat_map[line[i] - 1][row[i]] = 3;
				}
				if (seat_map[line[i] - 1][row[i] - 2] == 1) {//����λ�����ܳ��֡�0��״̬����λ���Ҳ����ܳ��֡�2��״̬��λ����ֻ�ж�Ϊ��1��״̬��
					seat_map[line[i] - 1][row[i] - 2] = 3;
				}
				continue;
			}
		}
		order->usr->user_balance -= order->price;//�޸��û����
		order->movie->remaining_ticket = get_remaining_ticket(seat_map);//ˢ����Ʊ��
		order->status = 1;//���Ķ���״̬Ϊ�Ѹ���״̬
		return 1;
	}

	//ȡ������
	void order_cancel(Order* order) {
		order->status = 3;
	}

	//��Ʊ
	//return 0 ����ѯ����
	//       1 : �˿�ɹ�
	// ��λ  0 ������ӰԺ���η�Χ��
	//       1 ���ɹ���
	//       2 �����۳�
	//       3 ���������۳�����λ���һ����λ�����޷��۳�
	int ticket_refund(Order* order, int(*seat_map)[26], Order_hash_table* hashTable) {
		char* token = strtok(order->seats, "-");//����strtok����������зֶ�
		char charline[4];//���ڴ洢��λ��Ϣ
		int line[3];//���ڴ洢��λ��Ϣ
		int row[3];//���ڴ洢��λ��Ϣ
		for (int i = 0; i < order->seat_number; i++) {
			if (sscanf(token, "%c%d", &charline[i], &row[i]) != 2) {
				return 0;
			}
			token = strtok(NULL, "-");
		}
		for (int i = 0; i < order->seat_number; i++) {//��������������ĸ��תΪ������ʽ
			line[i] = charline[i];
			line[i] -= 64;
		}
		for (int i = 0; i < order->seat_number; i++) {//�ȸ�����Ʊ��λΪ3״̬���˴�3״̬���κ����壬ֻ�Ǵ�����״̬���ɣ���Ϊ�����ͬʱ��F12-F13��״̬��
			seat_map[line[i] - 1][row[i] - 1] = 3;
		}
		for (int line = 0; line < 9; line++) {//ˢ����λͼ������������ά����
			for (int row = 0; row < 26; row++) {
				if (seat_map[line][row] == 3) {//ֻ����λ״̬Ϊ3����λ��Ҫ���ģ���λ״̬Ϊ1�Ĳ�����Ϊ��Ʊ��������Ϊ״̬��
					if (row == 0 && seat_map[line][row + 1] != 2) {//�����һ���������λ����ô�����Ҳ಻���ѹ������λ����ɹ���
						seat_map[line][row] = 1;
					}
					if (row == 25 && seat_map[line][row - 1] != 2) {//���Ҳ�һ���Ҳ�����λ����ô������಻���ѹ������λ����ɹ���
						seat_map[line][row] = 1;
					}
					else {
						if (seat_map[line][row - 1] != 2 && seat_map[line][row + 1] != 2) {//������λ������������������ѹ����״̬
							seat_map[line][row] = 1;
						}
					}
				}
			}
		}
		order->usr->user_balance += order->price;//�����û����
		order->movie->remaining_ticket = get_remaining_ticket(seat_map);//ˢ��ʣ��Ʊ��
		order->status = 4;//���Ķ���״̬
		return 1;
	}

	//չʾ�û����ж������������Ѿ�ȡ���Ķ�����
	void order_show_mini(User* usr, Order_hash_table* hashTable) {
		if (usr == NULL) {//�������
			printf("�û�������");
			return;
		}
		if (usr->my_order == NULL) {//�ų���û����ʷ���������
			printf("��û����ʷ������\n");
		}
		printf("������ʷ�������£�\n");
		int history_order_count = 0;//�˴�Ϊ�����������������¼�ǵڼ�������
		Linked_string_list* order = usr->my_order;
		while (order != NULL) {
			Order* order_find = find_order_in_hash_table(hashTable, order->id);
			if (order_find == NULL) {
				printf("��ѯʧ��.\n");
				return;
			}
			if (order_find->status == 3) {//������Ѿ�ȡ���Ķ���
				order = order->next;
				continue;
			}
			history_order_count++;
			printf("%d.\n", history_order_count);//���������Ϣ
			printf("orderID:%s\n", order_find->orderID);//���������Ϣ
			printf("user_id:%s\n", order_find->user_id);//���������Ϣ
			printf("movie_id:%s\n", order_find->movie_id);//���������Ϣ
			printf("seats:%s\n", order_find->seats);//���������Ϣ
			printf("seat_number:%d\n", order_find->seat_number);//���������Ϣ
			switch (order_find->status) {//���������Ϣ
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
			printf("time:%s\n", order_find->time);//���������Ϣ
			printf("price:%f\n", order_find->price);//���������Ϣ
			order = order->next;
		}
	}

	//����Ӱ������
	double get_movie_income(User* usr, Movie* movie, Order_hash_table* hashTable) {
		User* head = usr;//չʾ�����ָ�������ͷ���
		double movie_income = 0;//��ʼ������ֵ
		while (head != NULL) {//����User����
			Order* order_find = find_order_in_hash_table(hashTable, head->my_order->id);
			while (order_find != NULL) {//����my_order����
				if (order_find->movie->movie_id == movie->movie_id && order_find->status == 1) {//ȷ������Ϊ�ѹ���״̬
					double order_price = order_find->price;
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
		char* great_seats = malloc(13 * sizeof(char));
		memset(great_seats, 0, 13 * sizeof(char));
		int count = 0;
		int line_better[3];//���ڴ洢��Ϊ��Ϣ
		int row_better[3];//���ڴ洢��Ϊ��Ϣ
		for (double i = 0.5; i < 18; i++) {//��λͼ��9��26�У���Ϊ�������м�Ϊ���λ�ã�����Ϊ��6�У���13.5�У�����doubleֵ������ֵΪ17.5����i < 18
			if (count >= 3) {//�ҵ���������ѭ��
				break;
			}
			for (int line = 0; line < 9; line++) {//������λͼ
				if (count >= 3) {
					break;
				}
				for (int row = 0; row < 26; row++) {
					double difference = 1.0 * abs(line - 6) + fabs(1.0 * row - 13.5);//����������������6-13.5����
					if (count >= 3) {
						break;
					}
					if (seat_map[line][row] == 1 && fabs(difference - i) < 1e-6) {//�õ��Ĳ�ֵ��differemce�Ƚ�
						line_better[count] = line;
						row_better[count] = row;
						count++;
					}
				}
			}
		}

		for (int i = 0; i < count; i++) {//ͨ��ѭ���ѵõ������������ӵ�������ַ���֮��
			char better[4];
			sprintf(better, "%c%d-", line_better[i] + 'A', row_better[i] + 1);//�轫���ص�����ת��Ϊ��ĸ����ʽ
			strcat(great_seats, better);
		}
		size_t len = strlen(great_seats);//ɾȥ��β�� -
		great_seats[len - 1] = '\0';
		return great_seats;
	}

	//�ͷ�Order�ṹ��
	void order_list_free(Order* head) {
		Order* temp = head;
		while (head != NULL) {
			temp = head;
			head = head->next;//�ͷ�orderID,user_id,movie_id,seats,time
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
			//�ͷ�Order�ṹ�屾��
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
		//���Ƶ�ǰ��Order��Ϣ���½ڵ�
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