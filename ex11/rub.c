#include <stdio.h>
#include <ncurses.h>

#include <sys/types.h>
#include <dirent.h>

#include <sys/stat.h>
#include <time.h>

#include <stdlib.h>

int main(){
    int key, rows, cols;
    int current_position = 0;
    int wind_num = 0;
    int content = 0;
    
    WINDOW *main;    
    WINDOW *wnd[2];
    //printf("dssd");
    initscr();
    cbreak();
    curs_set(0);
    //keypad(stdscr, TRUE);
    //nodelay(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); 
    refresh();
    getmaxyx(stdscr, rows, cols);
    main = newwin(10,10, 0, 0);
    //wbkgd(main, COLOR_PAIR(1)); 
    box(main, '|', '-');
    
    
    wclear(main);
    wrefresh(main);
    wprintw(main, " sdasd");

    wrefresh(main); // Добавлено обновление окна
    refresh();

    getch();
    endwin();
}
