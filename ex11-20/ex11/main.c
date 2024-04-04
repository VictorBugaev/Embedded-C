#include "main.h"

#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
int main() {
  int rows, cols;
  int key;
  int current_position = 2;
  int wind_num = 0;
  int content = 0;
  time_t lastClickTime = 0;
  int k = 1;
  int f = 0;
  char dir_name[1000000] = "./";
  char wind1_dir_name[1000000] = "./";
  char wind2_dir_name[1000000] = "./";
  char current_name[10000] = "./";

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
  main = newwin(rows, cols, 0, 0);
  wbkgd(main, COLOR_PAIR(1));
  for (int i = 0; i < 2; i++) {
    wnd[i] = derwin(main, rows, cols / 2, 0, i * cols / 2);
    box(wnd[i], '|', '-');
    wrefresh(wnd[i]);
  }
  mousemask(BUTTON1_CLICKED, NULL);

  print_wind(main, wnd, 0, current_position, dir_name, &content, current_name,
             f);
  print_wind(main, wnd, 1, current_position, dir_name, &content, current_name,
             f);

  while ((key = getch()) != 'q') {
    switch (key) {
      case KEY_UP:
        if (current_position > 2) {
          current_position--;
          print_wind(main, wnd, wind_num, current_position, dir_name, &content,
                     current_name, f);
        }
        break;
      case KEY_DOWN:
        if (current_position < content) {
          current_position++;
          print_wind(main, wnd, wind_num, current_position, dir_name, &content,
                     current_name, f);
        }
        break;
      case '\n':
        f = 1;
        int ch = 0;
        print_wind(main, wnd, wind_num, current_position, current_name,
                   &content, current_name, f);
        if (dir_check(current_name)) {
          strcpy(dir_name, current_name);
        } else {
          strcpy(current_name, dir_name);
        }

        f = 0;
        print_wind(main, wnd, wind_num, current_position, dir_name, &content,
                   current_name, f);
        break;
      case 9:
        wind_num = k % 2;
        current_position = 2;
        if (wind_num == 1) {
          strcpy(wind1_dir_name, current_name);
          memset(current_name, 0, strlen(current_name));
          strcpy(current_name, wind2_dir_name);
        } else {
          strcpy(wind2_dir_name, current_name);
          memset(current_name, 0, strlen(current_name));
          strcpy(current_name, wind1_dir_name);
        }
        strcpy(dir_name, current_name);
        print_wind(main, wnd, wind_num, current_position, dir_name, &content,
                   current_name, f);
        k++;
        break;
      case KEY_MOUSE:
        MEVENT event;
        if (getmouse(&event) == OK) {
          time_t currentTime = time(NULL);
          if (lastClickTime != 0 &&
              difftime(currentTime, lastClickTime) < DOUBLE_CLICK) {
            f = 1;
            print_wind(main, wnd, wind_num, current_position, current_name,
                       &content, current_name, f);
            strcat(dir_name, current_name);
            f = 0;
          } else {
            print_wind(main, wnd, wind_num, event.y, current_name, &content,
                       current_name, f);
          }
          lastClickTime = currentTime;
        }
        break;
      default:
        break;
    }
    refresh();
  }
  refresh();
  endwin();
}
