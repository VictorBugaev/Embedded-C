    #include <stdio.h>
    #include <ncurses.h>

    #include <termios.h> 
    #include <sys/ioctl.h> 
    #include <signal.h> 
    #include <stdlib.h>

    int main(int argc, char ** argv) {
        WINDOW * wnd; 
        WINDOW * wnd2;
        WINDOW * sub1;
        WINDOW * sub2;
        
        initscr();
        cbreak();
        curs_set(0);
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        refresh();
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        wnd = newwin(cols/2, cols/2, 0, 0);
        wbkgd(wnd, COLOR_PAIR(1));
        
        sub1 = derwin(wnd, cols/2, cols/2, 1, 1);
        box(wnd, '|', '-');
        wprintw(sub1, "Hello, brave new curses world!\n"); 
        wrefresh(sub1);

        wnd2 = newwin(cols/2, cols/2, 0, cols/2 );
        wbkgd(wnd2, COLOR_PAIR(1));
        box(wnd2, '|', '-');
        sub2 = derwin(wnd2, cols/2, cols/2, 1, 1);
        wprintw(sub2, "Hello, brave new curses world!\n"); 
        wrefresh(sub2);



        wrefresh(wnd);
        wrefresh(wnd2);
        
        delwin(wnd);
        delwin(wnd2);
        refresh();
        getch();
        endwin();
        exit(EXIT_SUCCESS);
    }

