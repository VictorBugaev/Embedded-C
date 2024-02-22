#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define N 100
#define MAX_VALUE 10

struct abonent {
    char name[MAX_VALUE];
    char second_name[MAX_VALUE];
    char tel[MAX_VALUE];
};

void print_menu();
int add(int count, struct abonent *mass);
void delete(struct abonent *mass);
void search(int count, struct abonent *mass);
void show_all(int count, struct abonent *mass);
int stop();
void error_handler();

int main(){
    int flag = 1;
    char num[2];
    int count = 0;
    int count_ab = 0;
    struct abonent mass[N];
    print_menu();

    while (flag)
    {
        fgets(num, 2, stdin);
        if(num[0] == '\n'){
            continue;
        }
        switch (num[0])
        {
        case '1':
            count = add(count, mass);
            break;
        case '2':
            delete(mass);
            break;
        case '3':
            search(count, mass);
            break;
        case '4':
            show_all(count, mass);
            break;
        case '5':
            flag = stop();
            break;
        default:
            error_handler();
            break; 
        }
        if(flag){
            print_menu();
        }
    }
    
}

void print_menu(){
    printf("1) Добавить абонента \n2) Удалить абонента \n3) Поиск абонентов по имени \n4) Вывод всех записей \n5) Выход\n\n");
}

int add(int count, struct abonent *mass){
    if (count < N){
        char rubbish = fgetc(stdin);
        printf("----------------\n");
        printf("Введите имя\n");   
        fgets(mass[count].name, MAX_VALUE, stdin);
        printf("----------------\n");
        printf("Введите фамилию\n");
        fgets(mass[count].second_name, MAX_VALUE, stdin);
        printf("----------------\n");
        printf("Введите телефон\n");
        fgets(mass[count].tel, MAX_VALUE, stdin);
        printf("----------------\n\n");
        count ++;
    }else{
        printf("----------------\n");
        printf("Список переполнен\n");
        printf("----------------\n\n");
    }
    return count;        
}
void delete(struct abonent *mass){
    int a;
    printf("----------------\n");
    printf("Введите номер абонента\n");
    scanf("%d", &a);
    if (a > 100){
        perror("Invalid value");
    }
    printf("----------------\n");

    strcpy(mass[a-1].name, "0");
    strcpy(mass[a-1].second_name, "0");
    strcpy(mass[a-1].tel, "0");
}
void search(int count, struct abonent *mass){
    char rubbish = fgetc(stdin);
    char str[MAX_VALUE];
    int f = 0;
    printf("----------------\n");
    printf("Введите имя\n");
    fgets(str, sizeof(str), stdin);
    for(int i = 0; i < count; i++){
        if (strcmp(str, mass[i].name) == 0) {
            f = 1;
        }
        if(f){
            printf("----------------\n");
            printf("Найден абонент\n");
            printf("%s\n", mass[i].name);
            printf("%s\n", mass[i].second_name);
            printf("%s\n", mass[i].tel);
            printf("----------------\n");
            }else{
                printf("Абонент не найдет\n");
                printf("----------------\n");
            }
    f = 0;
    }
}
void show_all(int count, struct abonent *mass){
    for(int i = 0; i < count; i++){
        printf("----------------\n");
        printf("Абонент номер %d\n", i+1);
        printf("%s\n", mass[i].name);
        printf("%s\n", mass[i].second_name);
        printf("%s\n", mass[i].tel);
        printf("----------------\n");
    }
}
int stop(){
    return 0;
}

void error_handler(){
    printf("----------------\n");
    printf("Введен неверный символ\n");
    printf("----------------\n");
}
