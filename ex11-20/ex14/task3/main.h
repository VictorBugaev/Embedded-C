#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define DOUBLE_CLICK 3

void set_color(WINDOW *name, WINDOW *size, WINDOW *time, int num);
int print_wind(WINDOW *main, WINDOW *wnd[], int wind_num, int current_position,
               char *dir_name, int *count, char *current_name, int f);
int dir_check(char *name);
void *double_proc_create(char *proc1, char *proc2);