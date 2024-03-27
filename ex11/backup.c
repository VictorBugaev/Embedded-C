/*#include <stdio.h>
#include <ncurses.h>

#include <termios.h> 
#include <sys/ioctl.h> 
#include <signal.h> 
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>

int main(int argc, char ** argv) {
    WINDOW * wnd1; 
    WINDOW * sub1; 
        
    WINDOW * wnd2;
    WINDOW * sub2; 

    WINDOW * main;
        
    initscr();
    cbreak();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    refresh();
    int rows, cols;
        
    getmaxyx(stdscr, rows, cols);
        
    main = newwin(rows, cols, 0, 0);
    wbkgd(main, COLOR_PAIR(1)); 
        
    wnd1 = derwin(main, rows-1, cols/2, 0, 0);
    sub1 = derwin(wnd1, rows-2, (cols/2)-1, 1, 1);
    wprintw(sub1, "Hello, brave new curses world!\n"); 
    box(wnd1, '|', '-');
        
    wnd2= derwin(main, rows-1, cols/2, 0, cols/2);
    sub2 = derwin(wnd2, rows-2, (cols/2)-1, 1, 1);
    wprintw(sub2, "Hello, brave new curses world!\n"); 
    box(wnd2, '|', '-');
        

    wrefresh(sub1);
    wrefresh(wnd1);
    wrefresh(main);
        
    delwin(sub1);
    delwin(wnd1);
    delwin(main);
        
    refresh();
    getch();
    endwin();
    exit(EXIT_SUCCESS);
}
*/
#include <termios.h>
#include <sys/ioctl.h> 
#include <signal.h> 
#include <stdlib.h> 
#include <curses.h>
void sig_winch(int signo) {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size); 
    resizeterm(size.ws_row, size.ws_col); 
    nodelay(stdscr, 1);
    while (wgetch(stdscr) != ERR);
    nodelay(stdscr, 0);
}
int main(int argc, char ** argv) {
    initscr();
    signal(SIGWINCH, sig_winch);
    keypad(stdscr, 1);
    mousemask(BUTTON1_CLICKED, NULL);
    move(2,2);
    printw("Press the left mouse button to test mouse\n"); printw("Press any key to quit...\n");
    refresh();
    while (wgetch(stdscr) == KEY_MOUSE) {
        MEVENT event;
        getmouse(&event);
        move(0, 0);
        printw("Mouse button pressed at %i, %i\n", event.x, event.y); 
        refresh();
        move(event.y, event.x); 
    }
    endwin();
    exit(EXIT_SUCCESS);     
}
