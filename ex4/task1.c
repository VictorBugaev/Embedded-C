#include <stdio.h>
#include <string.h>

#define N 100

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
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
    char num;
    int count = 0;
    int count_ab = 0;
    struct abonent mass[N];
    print_menu();
    while (flag)
    {
        scanf("%c", &num);
        if(num == '\n'){
            continue;
        }
        switch (num)
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
        printf("----------------\n");
        printf("Введите имя\n");
        scanf("%s", mass[count].name);
        printf("----------------\n");
        printf("Введите фамилию\n");
        scanf("%s", mass[count].second_name);
        printf("----------------\n");
        printf("Введите телефон\n");
        scanf("%s", mass[count].tel);
        printf("----------------\n\n");
        count ++;
            //count_ab ++;
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
    scanf("%d", &a);
    printf("Номер абонента\n");
    printf("----------------\n");

    strcpy(mass[a-1].name, "0");
    strcpy(mass[a-1].second_name, "0");
    strcpy(mass[a-1].tel, "0");
            //count_ab --;
}
void search(int count, struct abonent *mass){
    char str[256];
    int f = 0;
    printf("----------------\n");
    printf("Введите имя\n");
    scanf("%s", str);
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