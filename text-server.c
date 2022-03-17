#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

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
    char buff[256], buff2[256], file[256], word[256], output[512];
    char path[2048], command[1024], lines_command[1024];
    client_sockfd =
        accept(server_sockfd, (struct sockaddr *)&client_addr, &(client_len));
    fprintf(stderr, "CLIENT CONNECTED\n");

    int rv1 = read(client_sockfd, buff, sizeof buff);
    buff[rv1] = '\0';
    strcpy(file, buff);
    fprintf(stderr, "PATH: \"%s\"\n", file);
    write(client_sockfd, "", 1);
    int rv = read(client_sockfd, buff2, sizeof buff2);
    buff2[rv] = '\0';
    strcpy(word, buff2);
    fprintf(stderr, "SEEKING: \"%s\"\n", word);
    fflush(stdout);


    if (strlen(buff2) == 0) {
      char length[32], invalid[32] = "";
      memset(&path[1], 0, sizeof(path));
      write(client_sockfd, path, sizeof(path));
      sprintf(length, "%ld", sizeof(invalid));
      write(client_sockfd, length, 32);
      write(client_sockfd, invalid, 32);
      fprintf(stderr, "BYTES SENT: %ld\n", strlen(invalid));

    } /*else {*/
/*    FILE *fp, *f;
    int num_bytes = 0;
    sprintf(command, "grep \"%s\" %s ", word, file);
    sprintf(lines_command, "grep \"%s\" %s | wc -l", word, file);
    //if (f = fopen(file, "r")) {
      int total;
      int num_lines;
      char length[32];
      fp = popen(lines_command, "r");
      while (fgets(path, sizeof(path) - 1, fp) != NULL) {
        write(client_sockfd, path, sizeof(path));
      }
      pclose(fp);
      fp = popen(command, "r");
      while (fgets(path, sizeof(path) - 1, fp) != NULL) {
        sprintf(length, "%ld", strlen(path));
        write(client_sockfd, length, 32);
        write(client_sockfd, path, atoi(length));
        num_bytes += strlen(path);
      }
      fclose(f);
      pclose(fp);
      fprintf(stderr, "BYTES SENT: %d\n", num_bytes);
    /*} else {
      char length[32], invalid[32] = "INVALID FILE\n";
      memset(&path[1], 0, sizeof(path));
      path[0] = '1';
      write(client_sockfd, path, sizeof(path));
      sprintf(length, "%ld", sizeof(invalid));
      write(client_sockfd, length, 32);
      write(client_sockfd, invalid, 32);
      fprintf(stderr, "BYTES SENT: %ld\n", strlen(invalid));
    }*/

   // }
    close(client_sockfd);
  }
  return 0;
}
