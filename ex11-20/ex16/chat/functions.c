#include "main.h"

void main_server_function(sem_t *sem_fd, char *serv_ptr, char *client_ptr) {
  int flag = 0;
  int f = 1;
  int client_numb = 0;
  char *connection_message = "You are connected to server";

  while (f) {
    sem_wait(sem_fd);
    if (strlen(serv_ptr) > 0) {
      printf("serv: %s", serv_ptr);
      strncpy(serv_ptr, connection_message, strlen(connection_message));
      client_numb += 1;
      flag = 1;
    }
    if (strcmp(client_ptr, "exit\n") == 0) {
      printf("Client leave the chat\n");
      client_numb -= 1;
    } else if (strlen(client_ptr) > 0) {
      printf("client: %s\n", client_ptr);
    }
    if (client_numb == 0 && flag) {
      printf("No one client on the server!\nDo you want to stop the server ?\n "
             "Y - yes N - no ");
      char choice = fgetc(stdin);
      if (choice == 'y' | choice == 'Y') {
        f = 0;
      } else {
        printf("%d", choice);
      }
    }
    memset(serv_ptr, 0, sizeof(serv_ptr));
    memset(client_ptr, 0, sizeof(client_ptr));
  }
}

void connection_to_server(char *serv_ptr, pid_t pid) {
  char connection_message[256];
  sprintf(connection_message, "Client %d connected to server\n", pid);
  strncpy(serv_ptr, connection_message, strlen(connection_message));
  printf("%s\n", connection_message);
}

void message_to_server(char *client_ptr, pid_t pid, sem_t *sem_fd) {
  int f = 1;
  while (f) {
    printf("Input the message: ");
    char prefix[256];
    char message[246];
    fgets(message, sizeof(message), stdin);
    strncpy(client_ptr, message, strlen(message));
    if (strcmp(message, "exit\n") == 0) {
      f = 0;
    } else {
      sprintf(prefix, "Client %d: %s", pid, message);
      strncpy(client_ptr, message, strlen(message));
    }
    sem_post(sem_fd);
  }
}