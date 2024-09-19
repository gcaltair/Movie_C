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
	char* seats; //�����Ƕ�ά���飿
	int seat_number;
	int status; //����״̬
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
	int count;
} Order_hash_table;

// ��������ʼ��һ�� Order_hash_table
Order_hash_table* order_hash_table_create();

// ��ʼ����ϣ�������е�ָ������Ϊ NULL
void init_order_hash_table(Order_hash_table* ht);

// ʹ�ù�ϣ�������������
void insert_order_to_hash_table(Order_hash_table* ht, Order* order);

// �ڹ�ϣ���в��Ҷ�����ͨ�� orderID ����
Order* find_order_in_hash_table(Order_hash_table* ht, char* orderID);


//��������ʼ����λͼ
int(*seat_map_generation())[26];

//չʾ��λͼ
void seat_map_show(int(*seat_map)[26]);

//��ѯ����ʣ����λ��
int get_remaining_ticket(int(*seat_map)[26]);

//���ַ�����ʽ���ص�ǰ�����գ�2024-8-31��
char* get_current_day();

//��ȡ��ǰʱ��
char* get_current_time();

//����orderID
char* get_orderID(int number);

//ͨ��seats������λ��
//retunr 0 : ����ʧ��
//       >=1 ������ɹ�
int get_seat_number(char* seats);

//������λ����
//return NULL �����벻�Ϸ�
char* seats_input_check();

//��λ����ͻ�ж�
//return 0 : ��ȡλ����Ϣʧ��
//       1 ; �����ɹ� 
//       2 : ʣ����λ������򳬹����Ʊ�޶�
//       3 ������������ͬ����λ�š�
//       4 ������ӰԺ���η�Χ��
//       5 ����λ���۳�
//       6 �������۳�����λ���һ����λ
// ��λ  0 ������ӰԺ���η�Χ��
//       1 ���ɹ���
//       2 �����۳�
//       3 ���������۳�����λ���һ����λ�����޷��۳�
int seats_check(char* seats, int(*seat_map)[26]);

//�жϵ�ǰʱ���Ƿ�ʹ���ʱ����ͬһ��
int is_current_date(char* time);

//��ʷ����ʱ���ͻ�ж�
//return 0 :��ѯʧ��
//       1 :�޳�ͻ
//       7 :�ѹ�����ó��ε�Ʊ
//       8 :�����Ѿ�����������ε�Ʊ
//       9 :������ӰƬ����ʱ���ͻ
//       10 :�ѹ�����ó��ε�Ʊ�ҹ�����ӰƬ����ʱ���ͻ
int history_order_time_check(User* usr, Movie* movie, Order_hash_table* hashTable);

//�ж϶����ܷ�����
//return 0 :��ѯʧ��
//       1 ; �����ɹ� 
//       2 : ʣ����λ������򳬹����Ʊ�޶�
//       3 ������������ͬ����λ�š�
//       4 ������ӰԺ���η�Χ��
//       5 ����λ���۳�
//       6 �������۳�����λ���һ����λ
//       7 :�ѹ�����ó��ε�Ʊ
//       8 :�����Ѿ�����������ε�Ʊ
//       9 :������ӰƬ����ʱ���ͻ
//       10 :�ѹ�����ó��ε�Ʊ�ҹ�����ӰƬ����ʱ���ͻ
int order_generation(User* usr, char* seats, Movie* movie, int(*seat_map)[26], Order_hash_table* hashTable);

//�����۸����
//discount���û��� = 1 - 0.05 * history_seat_number
//return 0      :����ʧ��
//       >0 :����ɹ�
double get_order_price(Order* order, Order_hash_table* hashTable);

//�ж�����Ƿ����
//return 0 : ����
//       1 ��������
int balance_check(Order* order);

//Ƿ�����
//return 0  ����Ƿ��
//       >0 ��Ƿ����
double  get_debt(Order* order, Order_hash_table* hashTable);

//��ֵ
//return 0 ����ֵʧ��
//return 1 : ��ֵ�ɹ�
int recharge(User* usr, double money);

//����
//return 0 ����ѯ����
//       1 : ����ɹ�
// ��λ  0 ������ӰԺ���η�Χ��
//       1 ���ɹ���
//       2 �����۳�
//       3 ���������۳�����λ���һ����λ�����޷��۳�
int process_pay(Order* order, int(*seat_map)[26]);

//ȡ������
void order_cancel(Order* order);

//��Ʊ
//return 0 ���˿�ʧ��
//       1 : �˿�ɹ�
// ��λ  0 ������ӰԺ���η�Χ��
//       1 ���ɹ���
//       2 �����۳�
//       3 ���������۳�����λ���һ����λ�����޷��۳�
int ticket_refund(Order* order, int(*seat_map)[26], Order_hash_table* hashTable);

//չʾ�û����ж������������Ѿ�ȡ���Ķ�����
void order_show_mini(User* usr, Order_hash_table* hashTable);

//����Ӱ������
double get_movie_income(User* usr, Movie* movie, Order_hash_table* hashTable);

//�����Ƽ���λͼ
//���ؾ���F13��F14����Ŀɹ��������λ�ã����ظ�ʽ"F11-F12-F15",���뺯��ǰ���ж���Ʊ�����ڵ���3
char* get_great_seats(int(*seat_map)[26]);

//�ͷ�order_list
void order_list_free(Order* head);

//
Order* order_copy_info(Order* order);

//
Order* order_list_create_by_user(User* usr, Order_hash_table* order_hash_table);

#endif //MOVIE_C_ORDER_H
