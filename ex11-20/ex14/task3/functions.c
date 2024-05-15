#include "main.h"

int choice_flag = 1;
char * proc1[256];

void set_color(WINDOW *name, WINDOW *size, WINDOW *time, int num) {
  wbkgd(name, COLOR_PAIR(num));
  wbkgd(time, COLOR_PAIR(num));
  wbkgd(size, COLOR_PAIR(num));
}
int print_wind(WINDOW *main, WINDOW *wnd[], int wind_num, int current_position,
               char *dir_name, int *count, char *current_name, int f) {
  DIR *dir = opendir(dir_name);
  pid_t pid;
  int status;
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  struct dirent *str;
  struct stat file;
  for (int i = 0; i < 2; i++) {
    wnd[i] = derwin(main, rows, cols / 2, 0, i * cols / 2);
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
  wind_box = derwin(wnd[wind_num], rows, cols / 11, 0, cols / 6);
  for (int i = 1; i < rows - 1; i++) {
    string[i] = derwin(wnd[wind_num], 1, cols / 2, i, 0);
    name[i] = derwin(string[i], 1, cols / 6, 0, 1);
    size[i] = derwin(string[i], 1, cols / 11, 0, cols / 6);
    time[i] = derwin(string[i], 1, cols / 4 - 1, 0, cols / 4);
  }
  for (int i = 1; i < rows - 1; i++) {
    if (i == 1) {
      set_color(name[i], size[i], time[i], 2);
      wprintw(name[i], " Name");
      wprintw(size[i], " Size");
      wprintw(time[i], "   Time");
      i++;
    }
    if ((str = readdir(dir)) != NULL) {
      if (i == current_position) {
        set_color(name[i], size[i], time[i], 3);
      }
      if (i == current_position && f) {
        strcat(current_name, str->d_name);
        if (!dir_check(current_name)) {  
          int choice;
          if(choice_flag){
            printw("Do you want to use '|' (1) - yes (2) - no?");
            refresh();
            
            choice = fgetc(stdin);
          }
          if(choice = 1){
            int proc_count = 0;
            strncpy(proc1, current_name, strlen(current_name));
            proc_count += 1;
          }
          if(!choice_flag){
            double_proc_create(proc1, current_name);
            memset(proc1, 0, sizeof(proc1));
            choice_flag = 1;
          }
          choice_flag = 0;
          /*int fd[2];
          pipe(fd);
          pid = fork();
          if (pid == 0) {
            if (a == 0){
              a = 1;             
              dup2(fd[1], STDOUT_FILENO);
              execv(current_name, NULL);
            } else {
              dup2(fd[0], 0);
              execv(current_name, NULL);

              a = 0;  
            }
            execv(current_name, NULL);
            exit(1);
          } else {
            wait(&status);

          }*/
          strcpy(current_name, dir_name);
        } else {
          strcat(current_name, "/");
        }
      }
      wprintw(name[i], " %s \n", str->d_name);
      wprintw(size[i], " %d \n", str->d_reclen);
      if (stat(dir_name, &file) < 0) {
        break;
      }
      wprintw(time[i], "   %s", ctime(&file.st_mtime));
      *count = i;
    } else {
      wclear(name[i]);
      wclear(size[i]);
      wclear(time[i]);
    }
    
    wrefresh(string[i]);
  }
  box(wind_box, '|', '-');
  wrefresh(wind_box);
  wrefresh(main);
}

int dir_check(char *name) {
  int res;
  DIR *dir = opendir(name);
  if (!dir) {
    res = 0;
  } else {
    if (readdir(dir) != NULL)
      res = 1;
    else
      res = 0;
  }
  return res;
}

int double_proc_create(char * proc1, char * proc2){
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid < 0) {
        printf("Ошибка при создании процесса\n");
        return 1;
    } else if (pid == 0) {
        // Дочерний процесс

        // Закрываем дескриптор для записи
        close(fd[1]);
        
        // Перенаправляем стандартный ввод на дескриптор для чтения из канала
        dup2(fd[0], 0);
        close(fd[0]);

        // Выполняем команду 'grep a'
        execv(proc2, NULL);
    } else {
        // Родительский процесс

        // Закрываем дескриптор для чтения
        close(fd[0]);
        
        // Перенаправляем стандартный вывод на дескриптор для записи в канал
        dup2(fd[1], 1);
        close(fd[1]);

        // Выполняем команду 'ls -la'
        execv(proc1, NULL);
    }

    return 0;
}
