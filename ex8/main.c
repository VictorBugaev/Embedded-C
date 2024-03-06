#include "main.h"

void menu();
void number_choose(int *a, int *b);


int main(){
    int f = 1, num_a, num_b, choose, result;
    while (f)
    {
        menu();
        scanf("%d", &choose);
        if (choose != 5) number_choose(&num_a, &num_b);
        switch (choose)
        {
        case 1:
            result = summary(num_a, num_b);
            printf("Результат - %d\n", result);            
            break;
        case 2:
            result = difference(num_a, num_b);
            printf("Результат - %d\n", result);
            break;
        case 3:
            result = multiplication(num_a, num_b);
            printf("Результат - %d\n", result);

            break;
        case 4:
            result = division(num_a, num_b);
            printf("Результат - %d\n", result);
            break;
        case 5:
            f = 0;
            break;    
        default:
            printf("Неверный символ\n");
        }
    }
    
    
}

void menu(){
    printf("Выберите действие:\n  1)Сложение\n  2)Вычитание\n  3)Умножение\n  4)Деление\n  5)Выход\n");
}

void number_choose(int *a, int *b){
    printf("Введите a\n");
    scanf("%d", a);
    printf("Введите b\n");
    scanf("%d", b);
}