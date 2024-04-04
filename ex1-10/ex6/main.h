#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define N 100
#define MAX_VALUE 10

struct abonent_list;


void print_menu();
struct abonent_list initialization(int* count);
struct abonent_list add(int *count, struct abonent_list *abonent);
struct abonent_list *delete(int *count, struct abonent_list *abonent);
void number_update(int new_number, struct abonent_list *abonent);
void search();
void show_all();
struct abonent_list* stop(int *count, struct abonent_list *abonent);
void error_handler();