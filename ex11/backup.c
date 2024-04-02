#include <stdio.h>
#include <ncurses.h>

#include <sys/types.h>
#include <dirent.h>


#include <sys/stat.h>
#include <time.h>

#include <stdlib.h>
#include <string.h>
//#include <malloc.h>

#define DOUBLE_CLICK 2

void transition(){

}


void set_color(WINDOW *name, WINDOW *size, WINDOW *time, int num){
    wbkgd(name, COLOR_PAIR(num));
    wbkgd(time, COLOR_PAIR(num)); 
    wbkgd(size, COLOR_PAIR(num));         
}

int print_wind(WINDOW *main, WINDOW *wnd[], int wind_num, int current_position, char *dir_name, int * count, char *current_name, int f){
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    DIR * dir = opendir(dir_name);
    if(!dir){
        return 0;
    }
    struct dirent * str;
    struct stat file;
    for(int i = 0; i < 2; i++){
        wnd[i] = derwin(main, rows, cols/2, 0, i*cols/2);
        box(wnd[i], '|', '-');
        wrefresh(wnd[i]);
    }
    WINDOW *string[rows];
    WINDOW *name[rows];
    WINDOW *size[rows];
    WINDOW *time[rows];
    WINDOW *wind_box;
    init_pair(2, COLOR_YELLOW, COLOR_BLUE);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    wind_box = derwin(wnd[wind_num], rows, cols/11, 0, cols/6);
    for(int i = 1; i < rows-1; i++){
        string[i] = derwin(wnd[wind_num], 1, cols/2, i, 0);
        name[i] = derwin(string[i], 1, cols/6, 0, 1);
        size[i] = derwin(string[i], 1, cols/11, 0, cols/6);
        time[i] = derwin(string[i], 1, cols/4-1, 0, cols/4);
        wrefresh(string[i]);
        wclear(name[i]);
        wclear(size[i]);
        wclear(time[i]);
    }
    
    for (int i = 1; ((str = readdir(dir)) != NULL); i++){ 
        if (i == 1){
            set_color(name[i], size[i], time[i], 2);
            wprintw(name[i], " Name");
            wprintw(size[i], " Size");
            wprintw(time[i], "   Time");
            i++;
        }
       if(i == current_position){
            set_color(name[i], size[i], time[i], 3);
        }
        if(i == current_position && f){
            strcat(current_name, str -> d_name);
            strcat(current_name, "/");
        }
        wprintw(name[i], " %s \n", str -> d_name);
        wprintw(size[i], " %d \n", str -> d_reclen);
        if(stat(dir_name, &file) < 0){
            break;
        }
        wprintw(time[i], "   %s", ctime(&file.st_mtime));
        *count = i;
        wrefresh(name[i]);
        wrefresh(size[i]);
        wrefresh(time[i]);
    }
    box(wind_box, '|', '-');
    wrefresh(wind_box);
    wrefresh(main);
    refresh();
}

int main(){
    int rows, cols;
    int key;
    int current_position = 2;
    int wind_num = 0;
    int content = 0;
    
    time_t lastClickTime = 0;
    
    char current_name[10000]="./";
    
    WINDOW *main;    
    WINDOW *wnd[2];

    initscr();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE); 

    refresh();
    
    getmaxyx(stdscr, rows, cols);
    main =  newwin(rows, cols, 0, 0);
    wbkgd(main, COLOR_PAIR(1)); 

    for(int i = 0; i < 2; i++){
        wnd[i] = derwin(main, rows, cols/2, 0, i*cols/2);
        box(wnd[i], '|', '-');
        wrefresh(wnd[i]);
    }
    mousemask(BUTTON1_CLICKED, NULL);
    mousemask(BUTTON1_CLICKED, NULL);
    int k = 1;
    int f = 0;

    
    char dir_name[1000000] = "./"; 
    char wind1_dir_name[1000000] = "./"; 
    char wind2_dir_name[1000000] = "./"; 

    print_wind(main, wnd, wind_num, current_position, dir_name, &content, current_name, f);
    print_wind(main, wnd, k, current_position, dir_name, &content, current_name, f);
    
    wrefresh(main);
    refresh();
    while ((key = getch()) != 'q') {
        switch (key) {
        case KEY_UP:
            if(current_position > 2) current_position --;
            print_wind(main, wnd, wind_num, current_position, dir_name, &content, current_name, f);
            break;
        case KEY_DOWN:
            if(current_position < content) current_position ++;
            print_wind(main, wnd, wind_num, current_position, dir_name, &content, current_name, f);
            break;
        case '\n':
            f = 1;
            print_wind(main, wnd, wind_num, current_position, current_name, &content, current_name, f);
            strcpy(dir_name, current_name);
            f = 0;
            break;
        case 9:
            wind_num = k % 2;
            current_position = 2;
            if(k == 1){

             //
                strcpy(wind1_dir_name, dir_name);
                memset(dir_name, 0, strlen(dir_name));
                strcpy(dir_name, wind2_dir_name);
            }else{
                strcpy(wind2_dir_name, dir_name);
                memset(dir_name, 0, strlen(dir_name));
                strcpy(dir_name, wind1_dir_name);     
            }
            print_wind(main, wnd, wind_num, current_position, dir_name, &content, current_name, f);
                wprintw(wnd[wind_num], "%s\n", dir_name);

            k++;
            break;
        case KEY_MOUSE:
            MEVENT event;
            if (getmouse(&event) == OK) {
                time_t currentTime = time(NULL);
                if (lastClickTime != 0 && difftime(currentTime, lastClickTime) < 3) {
                    f = 1;
                    print_wind(main, wnd, wind_num, current_position, current_name, &content, current_name, f);
                    strcpy(dir_name, current_name);
                    f = 0;
                } else{
                    print_wind(main, wnd, wind_num, event.y, current_name, &content, current_name, f);
                }
                lastClickTime = currentTime;
            }
            break;
        /*case BUTTON1_DOUBLE_CLICKED:
            f = 1;
            print_wind(main, wnd, wind_num, current_position, current_name, &content, current_name, f);
            strcpy(dir_name, current_name);
            f = 0;
            break;//закоментить*/
        default:
            break;
        }
        refresh();  
    }

    refresh();
    endwin();
}

