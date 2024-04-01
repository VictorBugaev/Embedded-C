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


void print_dir(WINDOW *name, WINDOW *size, WINDOW *time, char *dir_name){
    DIR * dir = opendir(dir_name);
    int cur_pos = 2;
    int string = 1;
    if(!dir){
        perror("diropen");
        exit(0);
    }

        wbkgd(name, COLOR_PAIR(2)); 
        wbkgd(size, COLOR_PAIR(2)); 
        wbkgd(time, COLOR_PAIR(2));


    init_pair(3, COLOR_BLACK, COLOR_RED);  
    struct dirent * str;
    struct stat file;

    wprintw(name, "  /.. \n");
    wprintw(size, "  UP-DIR\n");
    wprintw(time, "  ---\n");



    while((str = readdir(dir)) != NULL){
        if(cur_pos == string){
            wbkgd(name, COLOR_PAIR(3)); 
            wbkgd(size, COLOR_PAIR(3)); 
            wbkgd(time, COLOR_PAIR(3)); 
        }
        wprintw(name, " str-%d pos-%d", string, cur_pos);
        wprintw(name, "  %s \n", str -> d_name);
        wprintw(size, "  %d \n", str -> d_reclen);
        
        if(stat(dir_name, &file) < 0){
            perror("stat");
            exit(0);
        }
        wprintw(time, "  %s", ctime(&file.st_mtime));
        string++;
    }
}


int main(int argc, char ** argv) {
   // struct dirent * str;
   // struct stat file;
    int key; 
    int count = 6;
    
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
    curs_set(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  
    init_pair(2, COLOR_YELLOW,COLOR_BLUE);
    noecho();
    keypad(stdscr, TRUE);

    refresh();
    int rows, cols;
        
    getmaxyx(stdscr, rows, cols);
        
    main = newwin(rows, cols, 0, 0);
    wbkgd(main, COLOR_PAIR(1)); 
    
    wnd1 = derwin(main, rows, cols/2, 0, 0);
    
    sub1 = derwin(wnd1, rows, (cols/2), 0, 0);
    
    wattron(sub1, COLOR_PAIR(2)| A_BOLD);
    //wattron(sub1, COLOR_PAIR(2)); 

    name1 = derwin(sub1, rows, cols/6, 0, 0);
    size1 = derwin(sub1, rows, cols/11, 0, cols/6);
    time1 = derwin(sub1, rows, cols/4, 0, cols/4);
    
    wprintw(name1, "\n  Name\n");
    wprintw(size1, "\n  Size\n");
    wprintw(time1, "\n  Time\n");
    
    //wattroff(name1, COLOR_PAIR(1)| A_BOLD); 
    //wattroff(size1, COLOR_PAIR(1)| A_BOLD); 
    //wattroff(time1, COLOR_PAIR(1)| A_BOLD);

    print_dir(name1, size1, time1, "./");


    box(name1, '|', '-');
    box(size1, '|', '-');
    box(time1, '|', '-');
    box(wnd1, '|', '-');
    int f = 1;
    int cur_pos = 0;
    /*while (f){
        key = getch();
        switch (key)
        {
        case KEY_UP:
            f = 0;
            if(cur_pos>0)
            cur_pos --;
            move(0, cur_pos);
            break;
        case KEY_DOWN:
            f = 0;
            cur_pos ++;
            move(0, cur_pos);
            break;
        default:
            break;
        }
    }*/
    //print_dir(name1, size1, time1, "./");
    
        
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
    move(rows, cols);
        while ((key = getch()) != 'q') {
        switch (key) {
            case KEY_UP:
                wclear(name1);
                print_dir(name1, size1, time1, "./");
                //wprintw(name1, "\n  Name\n");
                wrefresh(name1);
                break;
            case KEY_DOWN:
                wclear(name1);
                //refresh();
                print_dir(name1, size1, time1, "./../");
                wrefresh(name1);

                break;
            default:
                break;
        }
        refresh();
    }
    delwin(sub1);
    delwin(wnd1);
    delwin(main);
    
    refresh();
    getch();
    endwin();
    exit(EXIT_SUCCESS);
}


