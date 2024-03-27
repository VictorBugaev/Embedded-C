#include <stdio.h>
#include <ncurses.h>

#include <termios.h> 
#include <sys/ioctl.h> 
#include <signal.h> 
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>

#include <sys/stat.h>
#include <time.h>

int main(int argc, char ** argv) {
    DIR * dir = opendir("./");
    if(!dir){
        perror("diropen");
        exit(0);
    }
    struct dirent * str;
    struct stat file;
    
    WINDOW * wnd1; 
    WINDOW * sub1; 
    WINDOW * name1; 
    WINDOW * size1; 
    WINDOW * time1; 
        
    WINDOW * wnd2;
    WINDOW * sub2; 
    WINDOW * name2; 
    WINDOW * size2; 
    WINDOW * time2;

    WINDOW * main;
        
    initscr();
    cbreak();
    curs_set(1);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  
    init_pair(2, COLOR_YELLOW,COLOR_BLUE);

    refresh();
    int rows, cols;
        
    getmaxyx(stdscr, rows, cols);
        
    main = newwin(rows, cols, 0, 0);
    wbkgd(main, COLOR_PAIR(1)); 
    
    wnd1 = derwin(main, rows, cols/2, 0, 0);
    
    sub1 = derwin(wnd1, rows, (cols/2), 0, 0);
    
    
    wattron(sub1, COLOR_PAIR(2)| A_BOLD); // Включаем цветовую пару с желтым цветом
    wattron(sub1, COLOR_PAIR(2)); // Включаем цветовую пару с желтым цветом


    name1 = derwin(sub1, rows, cols/6, 0, 0);
    size1 = derwin(sub1, rows, cols/11, 0, cols/6);
    time1 = derwin(sub1, rows, cols/4, 0, cols/4);
    
    wprintw(name1, "\n  Name\n\n");
    wprintw(size1, "\n  Size\n\n");
    wprintw(time1, "\n  Time\n\n");
    
    wattroff(name1, COLOR_PAIR(2)| A_BOLD); // Выключаем цветовую пару с желтым цветом
    wattroff(size1, COLOR_PAIR(2)| A_BOLD); // Выключаем цветовую пару с желтым цветом
    wattroff(time1, COLOR_PAIR(2)| A_BOLD); // Выключаем цветовую пару с желтым цветом
    
    while((str = readdir(dir)) != NULL){
        wprintw(name1, "  %s \n", str -> d_name);
        wprintw(size1, "  %d \n", str -> d_reclen);
        
        if(stat(str -> d_name, &file) < 0){
            perror("stat");
            exit(0);
        }
        wprintw(time1, "  %s", ctime(&file.st_mtime));
        
    }

    
    box(name1, '|', '-');
    box(size1, '|', '-');
    box(time1, '|', '-');
    box(wnd1, '|', '-');

    
    
    if(wgetch(wnd1) == 'q'){
        printw("asdasdasd");
    }
    
    
    
    //wprintw(sub1, "Hello, brave new curses world!\n"); 
    
        
    wnd2= derwin(main, rows-1, cols/2, 0, cols/2);
    sub2 = derwin(wnd2, rows-2, (cols/2)-1, 1, 1);
    wprintw(sub2, "Hello, brave new curses world!\n"); 
    box(wnd2, '|', '-');

    wrefresh(time1);
    wrefresh(size1);
    wrefresh(name1);

    wrefresh(sub1);
    wrefresh(wnd1);
    wrefresh(main);
        
    delwin(sub1);
    delwin(wnd1);
    delwin(main);
    
    refresh();
    //getch();
    endwin();
    exit(EXIT_SUCCESS);
}


