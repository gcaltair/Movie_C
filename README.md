所需函数

### 结构

user.h

```c
typedef struct User{
    char* userID;
    char* user_name;
    char* gender;
    char* telephone;
    char* password;
    char* email;
    double user_balance;
    struct User* next;
}User;
```

admin.h

```c
typedef struct Admin{
    char* admin_ID;
    char* admin_name;
    char* admin_telephone;
    char* admin_password;
    char* admin_email;
    Cinema* cinema;
    struct Admin* next;
}Admin;
```

movie.h

```c
    char* session_number;
	char* movie_name;
    char* affiliated_cinema; //归属影院
    Theater* play_theater; //在哪个影厅播放
    char* start_time;
    char* end_time;
    int remaining_ticket;
    double price;
	double discount; //优惠
    char* theater_type;
	struct Movie* next;
```

theater.h

```c
typedef struct {
    char* theater_name;
    int theater_capacity;
    Cinema* cinema;
    //缺座位图，座位号
    char* theater_type;
    struct Theater* next;
}theater;
```

order.h

```c
    int oderID;
    User* usr;
    Movie* movie;
    Theater* theater;
	Cinema* cinema;
    int seats; //可以是二维数组？
    int status; //订单状态
	int time;
	struct Order* next;
```

cinema.h

```c
	char* cinema_name;
	char* location;
	theater* the[100]
	int cinema_id;
	struct Cinema* next
```



### 函数

#### 1. `user.h`

函数

```c
User* add_user(char* email,char* name,……,)
//User* add_user("121212@dsadsa.com","sadsadsa")
```

```c
void delete_user(User* usr)
```

```c
User* find_user(char* name)
```

```c
void modify_user(User* usr)
```

```c
bool login(char* enter_usr,char* entered_password)
```

> 模拟付款单独做一个文件



#### 2.`admin.h`

增删查改用户直接调用

```c
bool login(char* enter_admin,char* entered_password)
```

```c
Admin* add_admin(char* email,char* name,……,)
```

```c
void delete_admin(Adimin* admin)
```

```c
void modify_admin(Admin* admin)
```

```c
Admin* find_admin(char* name)
```

----

#### 3. `theater.h`

```c
theater* add_theater(，……，)
```

```c
theater* find_theater(Cinema* cinema)
```

#### 4.`order.h` 处理

```c
Order* add_order(User* usr,Movie* movie)
```

```c
bool cancel_order(User* usr,Order* order)
```

```c
Order* find_order(User* usr)
```

#### 5.`cinema.h`

```c
	char* cinema_name;
	char* location;
	int cinema_id;
```



#### 6. `movie.h` 场次

```c
Movie* add_movie(,,,)
```

```c
Movie* find_movie(Cinema* cinema)
```

```c
…… //查找函数
```







`char*`

```c
char* a="asasa";
	char* input=(char*)malloc()
	scanf("%s",input);
	printf("%s",a);
```



