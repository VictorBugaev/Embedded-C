#include "main.h"
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#define NAME_SIZE 50

void menu();
void number_choose(int *a, int *b);
void lib_choose();
void * inicialization(char *name);

int main(){
    int f = 1, lib_f = 1, num_a, num_b, choose, result, lib_count = 0;
    int (*dif)() = 0, (*div)() = 0, (*mult)() = 0, (*sum)() = 0;
    while (lib_f)
    {
        lib_choose();
        scanf("%d", &choose);
        switch (choose){
        case 1:
            sum = inicialization("libsummary.so");
            printf("Библиотека сложения успешно загружена!\n");          
            lib_count++;
            break;
        case 2: 
            dif = inicialization("libdifference.so");
            printf("Библиотека вычитания успешно загружена!\n");
            lib_count++;
            break;
        case 3:
            mult = inicialization("libmultiplication.so");
            printf("Библиотека умножения успешно загружена!\n");
            lib_count++;
            break;
        case 4:
            div = inicialization("libdivision.so");
            printf("Библиотека деления успешно загружена!\n");
            lib_count++;
            break;
        case 5:
            lib_f = 0;
            break;    
        default:
            printf("Неверный символ\n");
        }
    }
    if (lib_count == 0){
        printf("Ни одна библиотека не загружена !\n");
    }
    while (f && lib_count)
    {
        menu();
        scanf("%d", &choose);
        if (choose != 5) number_choose(&num_a, &num_b);
        switch (choose)
        {
        case 1:
            if(sum){
                result = sum(num_a, num_b);
                printf("Результат - %d\n", result);            
            }else{
                printf("Библиотека не загружена!\n");
            }
            break;
        case 2:
            if(dif){
                result = dif(num_a, num_b);
                printf("Результат - %d\n", result);
            }else{
                printf("Библиотека не загружена!\n");
            }
            break;
        case 3:
            if(mult){
            result = mult(num_a, num_b);
            printf("Результат - %d\n", result);
            }else{
                printf("Библиотека не загружена!\n");
            }
            break;
        case 4:
            if(div){
                result = div(num_a, num_b);
                printf("Результат - %d\n", result);
            }else{
                printf("Библиотека не загружена!\n");
            } 
            break;
        case 5:
            f = 0;
            break;    
        default:
            printf("Неверный символ\n");
        }
    }
    
    
}
void lib_choose(){
    printf("Выберите библиотеку для загрузки:\n  1)Сложение\n  2)Вычитание\n  3)Умножение\n  4)Деление\n  5)Далее\n");
}

void menu(){
    printf("Выберите действие в соответсвии с загруженными библиотеками:\n  1)Сложение\n  2)Вычитание\n  3)Умножение\n  4)Деление\n  5)Выход\n");
}

void number_choose(int *a, int *b){
    printf("Введите a\n");
    scanf("%d", a);
    printf("Введите b\n");
    scanf("%d", b);
}

void * inicialization(char *name){
    char dir[] = "./libs/";
    char name_with_dir[NAME_SIZE + strlen(dir)];
    char function_name[NAME_SIZE];
    for(int i = 0; i < NAME_SIZE; i++){
        name_with_dir[i] = name[i];     
    } 
    memmove(name_with_dir + strlen(dir), name_with_dir, strlen(name_with_dir) + 1);
    memcpy(name_with_dir, dir, strlen(dir));
    void *ptr_lib = dlopen(name_with_dir, RTLD_LAZY);
    if(!ptr_lib){
        printf("%s\n",dlerror());
        exit(0);
    }
    int j = 2;
    for(int i = 0; i < strlen(name); i++){
        j++;
        if(i < 4){
            function_name[i] = name[j];    
        }else if (i > strlen(name) - 7){
            function_name[i] = '\0';
        }else{
            function_name[i] = name[j];    
        }
    } 
    int(*ptr_func)() = dlsym(ptr_lib, function_name);
    return  ptr_func; 
}
