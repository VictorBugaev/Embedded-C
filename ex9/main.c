#include "main.h"
#include <dlfcn.h>
#include <string.h>

#define NAME_SIZE 50

void menu();
void number_choose(int *a, int *b);
void lib_choose();

int *inicialization(char *name){
    char dir[] = "./libs/";
    char name_with_dir[NAME_SIZE + strlen(dir)];
    char function_name[NAME_SIZE];
    name[strlen(name) - 1] = '\0';

    for(int i = 0; i < NAME_SIZE; i++){
        name_with_dir[i] = name[i];     
    } 


    memmove(name_with_dir + strlen(dir), name_with_dir, strlen(name_with_dir) + 1);
    memcpy(name_with_dir, dir, strlen(dir));

    void *ptr_lib = dlopen(name_with_dir, RTLD_LAZY);
    if(!ptr_lib){
        printf("%s\n",dlerror());
        return 0;
    }
    int j = 2;
    for(int i = 0; i < strlen(name); i++){
        j++;
        if(i < 4){
            function_name[i] = name[j];    
        }else if (i > strlen(name) - 4){
            function_name[i] = '\0';
        }else{
            function_name[i] = name[i];    
        }

    } 

    //printf("Введите имя \n");
    
    printf("func - %s\n", function_name);

    //int (*ptr_func)() = dlsym(ptr_lib, "summary");
    

}

int main(){
    int f = 1, lib_f = 1, num_a, num_b, choose, result, lib_count = 0;
    char name[NAME_SIZE];
    printf("Введите имя бибилотеки в формате libname.so\n");

    fgets(name, NAME_SIZE, stdin);
    printf("name -  %s\n", name);
    inicialization(name);
    void *ptr_sum = dlopen("./libs/libsummary.so" ,  RTLD_LAZY);
    void *ptr_dif = dlopen("./libs/libdifference.so",  RTLD_LAZY);
    void *ptr_mult = dlopen("./libs/libdivision.so",  RTLD_LAZY);
    void *ptr_div = dlopen("./libs/libmultiplication.so",  RTLD_LAZY);
    
    if(!ptr_sum){
        printf("%s\n",dlerror());
        return 0;
    }
    if(!ptr_dif){
        printf("%s\n",dlerror());
        return 0;
    }if(!ptr_mult){
        printf("%s\n",dlerror());
        return 0;
    }if(!ptr_div){
        printf("%s\n",dlerror());
        return 0;
    }
    int (*sum)() = dlsym(ptr_sum, "summary");
    int (*dif)() = dlsym(ptr_dif, "difference");
    int (*div)() = dlsym(ptr_mult, "division");
    int (*mult)() = dlsym(ptr_div, "multiplication");
    while (lib_f)
    {
        lib_choose();
        scanf("%d", &choose);
        switch (choose){
        case 1:
            printf("Библиотека сложения успешно загружена!\n");            
            lib_count++;
            break;
        case 2:
            printf("Библиотека вычитания успешно загружена!\n");
            lib_count++;
            break;
        case 3:
            printf("Библиотека умножения успешно загружена!\n");
            lib_count++;
            break;
        case 4:
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
            result = sum(num_a, num_b);
            printf("Результат - %d\n", result);            
            break;
        case 2:
            result = dif(num_a, num_b);
            printf("Результат - %d\n", result);
            break;
        case 3:
            result = mult(num_a, num_b);
            printf("Результат - %d\n", result);

            break;
        case 4:
            result = div(num_a, num_b);
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
void lib_choose(){
    printf("Выберите библиотеку для загрузки:\n  1)Сложение\n  2)Вычитание\n  3)Умножение\n  4)Деление\n  5)Выход\n");
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
