#include "main.h"


struct abonent_list {
    char name[MAX_VALUE];
    char second_name[MAX_VALUE];
    char tel[MAX_VALUE];
    int number;
    struct abonent_list *prew_abonent;
};

void print_menu(){
    printf("1) Добавить абонента \n2) Удалить абонента \n3) Поиск абонентов по имени \n4) Вывод всех записей \n5) Выход\n\n");
}

struct abonent_list initialization(int *count){
    
    struct abonent_list *abonent;
    abonent = (struct abonent_list *)malloc(sizeof(struct abonent_list));
    abonent->prew_abonent = NULL;
    abonent->number = *count;
    (*count) ++;
    return (*abonent);


}

struct abonent_list add(int *count, struct abonent_list *abonent){
    
    if (*count >= N){
        printf("Справошник переполнен!");
        return (*abonent);
    }


    struct abonent_list *tmp, *p;

    tmp = (struct abonent_list *)malloc(sizeof(struct abonent_list));
    
    p = abonent -> prew_abonent;    
    abonent -> prew_abonent = tmp;
    
    char rubbish = fgetc(stdin);
    printf("----------------\n");
    printf("Введите имя\n");   
    fgets(tmp -> name, MAX_VALUE, stdin);
    printf("----------------\n");
    printf("Введите фамилию\n");
    fgets(tmp -> second_name, MAX_VALUE, stdin);
    printf("----------------\n");
    printf("Введите телефон\n");
    fgets(tmp -> tel, MAX_VALUE, stdin);
    printf("----------------\n");

    tmp -> number = *count;
    (*count)++;
    
    tmp->prew_abonent = p;
    return (*abonent);
}
struct abonent_list* delete(int *count, struct abonent_list *abonent){
    
    int a;
    struct abonent_list *tmp, *prev = NULL;

    if(*count == 0){
        printf("Телефонная книга пуста\n");
        return (abonent);
    }

    printf("----------------\n");
    
    printf("Введите  номер абонента\n");
    scanf("%d", &a);
    if (a > *count){
        printf("Неверное значение\n");
        return (abonent);
    }
    
    tmp = abonent->prew_abonent;

    if (tmp == NULL) {
        printf("Abonent not found.\n");
        return abonent;
    }
    
    while (tmp != NULL && tmp->number != a) {
        prev = tmp;
        tmp = tmp->prew_abonent;
        if(*count > 1){
            number_update(tmp->number - 1, tmp);
        }
    }
    
  
    if (prev != NULL) {
        prev->prew_abonent = tmp->prew_abonent;
    } else {
        abonent = tmp->prew_abonent;
    }
    
    free(tmp);
    (*count)--; 
    return abonent;
}


void search(struct abonent_list *abonent){
    
    char name_to_phind[MAX_VALUE];
    char rubbish = fgetc(stdin);
    printf("----------------\n");
    printf("Введите имя\n");   
    fgets(name_to_phind, MAX_VALUE, stdin);
    printf("----------------\n");
       
    struct abonent_list *p;
    p = abonent;
    
    while (p != NULL)
    {
        if(!strcmp(p->name, name_to_phind)){
            printf("%s\n", p->name);
            printf("%s\n", p->second_name);
            printf("%s\n", p->tel);
            printf("----------------\n");        
        }
        p = p->prew_abonent;
    }
}
void show_all(struct abonent_list *abonent){
    struct abonent_list *tmp;
    tmp = abonent;
    while (tmp != NULL)
    {   
        if (tmp -> number != 0){
            printf("----------------\n");
            printf("%s\n", tmp->name);
            printf("%s\n", tmp->second_name);
            printf("%s\n", tmp->tel);
            printf("%d\n", tmp->number);
            printf("----------------\n");
        }
        tmp = tmp->prew_abonent;
        
    }
}
struct abonent_list* stop(int *count, struct abonent_list *abonent) {
    
    struct abonent_list *tmp, *prev;

    if(*count == 0){
        printf("Телефонная книга пуста\n");
        return (abonent);
    }

    tmp = abonent->prew_abonent;
    
    while (tmp != NULL ) {
        prev = tmp;
        tmp = prev->prew_abonent;
        free(prev);
    }
    return abonent;
}


void error_handler(){
    printf("----------------\n");
    printf("Введен неверный символ\n");
    printf("----------------\n");
}

void number_update(int new_number, struct abonent_list *abonent){
    struct abonent_list *tmp;
    tmp = abonent;
    while (tmp != NULL)
    {
        if(tmp -> number > new_number){
            tmp -> number --;
        }
        tmp = tmp -> prew_abonent;
    }
    
}