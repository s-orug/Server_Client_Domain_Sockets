#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

char *text_parse(char *word, char *file) {
  FILE *fp;
  size_t one = 0;
  char command[1024], *line = NULL, *store = "";
  sprintf(command, "grep \"%s\" %s ", word, file);
  fp = popen(command, "r");
  while (getline(&line, &one, fp) > 1) {
    asprintf(&store, "%s%s", (char *const)store, (char *const)line);
  }
  return store;
}

int main(int argc, char *argv[]) {
  int server_sockfd, client_sockfd, n;
  struct sockaddr_un server_addr;
  struct sockaddr_un client_addr;

  if (get_nprocs_conf() > 1) {
    n = get_nprocs_conf() - 1;
  } else {
    n = get_nprocs_conf();
  }

  unlink(argv[1]);
  server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, argv[1], sizeof(server_addr.sun_path) - 1);
  int success =
      bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof server_addr);

  listen(server_sockfd, n);
  fprintf(stderr, "SERVER STARTED\n\tMAX CLIENTS:%d\n", n);
  while (1) {
    int client_len = sizeof client_addr;
    char buff[256], tmp[512];
    client_sockfd =
        accept(server_sockfd, (struct sockaddr *)&client_addr, &(client_len));
    fprintf(stderr, "CLIENT CONNECTED\n");


    int k = read(client_sockfd, buff, sizeof(buff)); // receives path
    buff[k]= '\0';
    sprintf(tmp, "PATH: \"%s\"\n", buff);
    fprintf(stderr, "%s", tmp);

    k = read(client_sockfd, buff, sizeof(buff)); // receives text
    buff[k]= '\0';
    sprintf(tmp, "SEEKING: \"%s\"\n", buff);
    fprintf(stderr, "%s", tmp);

    close(client_sockfd);
  }
  return 0;
}
