//
// Created by Y on 2024/8/27.
//

#include "Movie.h"

bool login()
{
    return true;
}
Movie* Movie_add() {
    // ��̬�����ڴ����ڱ���һ�� Movie �ṹ��
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (newMovie == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // ��̬����ͳ�ʼ�������ֶ�
    newMovie->session_number = (char*)malloc(50 * sizeof(char));
    newMovie->movie_name = (char*)malloc(50 * sizeof(char));
    newMovie->affiliated_cinema = (char*)malloc(10 * sizeof(char));
    newMovie->telephone = (char*)malloc(20 * sizeof(char));
    newMovie->password = (char*)malloc(50 * sizeof(char));
    newMovie->email = (char*)malloc(50 * sizeof(char));

    if (!newUser->userID || !newUser->user_name || !newUser->gender ||
        !newUser->telephone || !newUser->password || !newUser->email) {
        printf("Memory allocation for fields failed!\n");
        free(newUser); // �ͷŷ�����ڴ�
        return NULL;
    }

    // ��ȡ�û����벢����洢�ڽṹ����
    printf("Enter User ID: ");
    scanf("%49s", newUser->userID);

    printf("Enter User Name: ");
    scanf("%49s", newUser->user_name);

    printf("Enter Gender: ");
    scanf("%9s", newUser->gender);

    printf("Enter Telephone: ");
    scanf("%19s", newUser->telephone);

    printf("Enter Password: ");
    scanf("%49s", newUser->password);

    printf("Enter Email: ");
    scanf("%49s", newUser->email);

    printf("Enter User Balance: ");
    scanf("%lf", &newUser->user_balance);

    return newUser;
}
void modify_personalinfo(); //�޸��û���Ϣ