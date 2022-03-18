#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

bool file_checker(char filename[]) {
  FILE *f;
  if (f = fopen(filename, "r")) {
    fclose(f);
    return true; // returns true if it can open
  }
  return false; // returns false if it can't open
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
    int client_len = sizeof client_addr, num_bytes = 0, total = 0; // size=0;
    char buff[512], buff2[256], tmp[2048], *misc, path[512], seeking[512];
    client_sockfd =
        accept(server_sockfd, (struct sockaddr *)&client_addr, &(client_len));
    fprintf(stderr, "CLIENT CONNECTED\n");

    int k = read(client_sockfd, buff, sizeof(buff)); // receives path
    buff[k] = '\0';
    sprintf(path, "%s", buff);
    fprintf(stderr, "PATH: \"%s\"\n", path);
    fflush(stdout);

    k = read(client_sockfd, buff2, sizeof(buff2)); // receives text
    buff2[k] = '\0';
    sprintf(seeking, "%s", buff2);
    fprintf(stderr, "SEEKING: \"%s\"\n", seeking);
    fflush(stdout);

    if (file_checker(path) < 1) {
      num_bytes = 0;
      strcpy(tmp, "INVALID FILE\n");
      write(client_sockfd, tmp, sizeof(tmp));
      num_bytes += strlen(tmp);
      close(client_sockfd);
    }

    if (strlen(seeking) != 0) {
      FILE *fp;
      char command[2048], line[2048], *store = "";
      sprintf(command, "grep \"%s\" %s ", seeking, path);
      if (file_checker(path) != 0) {
        fp = popen(command, "r");

        while (fgets(line, sizeof(line) - 1, fp) != NULL) {
          sprintf(tmp, "%s", line);
          write(client_sockfd, tmp, sizeof(tmp));
          num_bytes += strlen(tmp);
        }
        strcpy(tmp, "");
        write(client_sockfd, tmp, sizeof(tmp));
        pclose(fp);
      }

      fprintf(stderr, "BYTES SENT: %d\n", num_bytes);
      close(client_sockfd);
    } else {
      if (strlen(seeking) == 0) {
        num_bytes = 0;
      }
      fprintf(stderr, "BYTES SENT: %d\n", num_bytes);
    }
    close(client_sockfd);
  }
  return 0;
}
