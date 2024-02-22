
#include "main.h"

struct abonent_list {
    char name[MAX_VALUE];
    char second_name[MAX_VALUE];
    char tel[MAX_VALUE];
    int number;
    struct abonent_list *prew_abonent;
};

int main(){
    int flag = 1;
    char num[2];
    int count = 0;
    int count_ab = 0;
    print_menu();
    struct abonent_list element[N]; 
    element[0] = initialization(&count);
    while (flag)
    {
        fgets(num, 2, stdin);
        if(num[0] == '\n'){
            continue;
        }
        switch (num[0])
        {
        case '1':
            add(&count, element);
            break;
        case '2':
            delete(&count, element);
            break;
        case '3':
            search(element);
            break;
        case '4':
            show_all(element);
            break;
        case '5':
            stop(&count, element);
            //flag = 1;
            return 0;
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


