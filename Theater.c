/*
娴嬭瘯浠ｇ爜
Cinema* t = cinema_add("Cinema A", "Location A", 1);
Cinema *cinema_list= cinema_create_list(t);;
cinema_direct_add_to_list(&cinema_list, "Cinema C", "Location C", 3);
Theater *theater_temp= theater_add("theater1",20,cinema_list,"3D");
Theater *theater_list=theater_create_list(theater_temp);
theater_add_to_list(&theater_list,theater_temp); //鍙湁浣跨敤杩欎釜鍑芥暟娣诲姞瀵硅薄鍒伴摼琛ㄦ墠浼氭洿鏂癈inema->Theater鐨勬寚閽�
cinema_show(theater_temp->cinema);
theater_show(cinema_list->theater);

 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Theater.h"
#include "Cinema.h"
// 鍒涘缓骞跺垵濮嬪寲涓�涓柊鐨� Theater 缁撴瀯浣�
Theater* theater_create(const char* name, int capacity, Cinema* cinema_, const char* type) {
    // 鍔ㄦ�佸垎閰嶅唴瀛樼粰 Theater 缁撴瀯浣�
    Theater* theater = (Theater*)malloc(sizeof(Theater));
    if (theater == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // 鍔ㄦ�佸垎閰嶅唴瀛樺苟澶嶅埗鍙傛暟鍐呭鍒扮粨鏋勪綋瀛楁
    theater->theater_name = strdup(name);
    theater->theater_capacity = capacity;
    theater->cinema = cinema_;
    theater->theater_type = strdup(type);
    theater->movie = NULL;  // 闇�瑕佸彟澶栬祴鍊�
    theater->next = NULL;
    theater->cinema=cinema_;
    return theater;
}

// 鏄剧ず鍗曚釜鍓ч櫌淇℃伅
void theater_show(const Theater* theater) {
    if (theater == NULL) {
        printf("Theater data is NULL.\n");
        return;
    }

    printf("Theater Name: %s\n", theater->theater_name);
    printf("Capacity: %d\n", theater->theater_capacity);
    if (theater->cinema != NULL) {
        printf("Cinema Name: %s\n", theater->cinema->cinema_name);
    }
    printf("Theater Type: %s\n", theater->theater_type);
}

// 鍒涘缓鍓ч櫌閾捐〃澶磋妭鐐�
Theater* theater_create_list(Theater* new_theater) {
    return new_theater;
}

// 娣诲姞涓�涓厓绱犲埌鍓ч櫌閾捐〃锛堝ご鎻掓硶锛�
void theater_add_to_list(Theater** head, Theater* new_theater) {
    if (*head == NULL) {
        *head = new_theater;
        return;
    }

    new_theater->next = *head;
    *head = new_theater;
    (*head)->cinema->theater=(*head);
}

// 鐩存帴娣诲姞鍓ч櫌鍏冪礌鍒伴摼琛ㄤ腑
void theater_direct_add_to_list(Theater** head, const char* name, int capacity, Cinema* cinema, const char* type) {
    Theater* new_theater = theater_create(name, capacity, cinema, type);
    if (new_theater == NULL) {
        return;
    }

    new_theater->next = *head;
    *head = new_theater;
    (*head)->cinema->theater=(*head);
}

// 鏍规嵁鍓ч櫌鍚嶆煡鎵惧墽闄�
Theater* theater_find_by_name(Theater* head, const char* name) {
    Theater* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->theater_name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // 濡傛灉娌℃湁鎵惧埌鍖归厤鐨勫悕瀛楋紝杩斿洖NULL
}

// 鏄剧ず鎵�鏈夊墽闄俊鎭�
void theater_show_all(Theater* head) {
    Theater* temp = head;
    while (temp != NULL) {
        theater_show(temp);
        temp = temp->next;
    }
}
