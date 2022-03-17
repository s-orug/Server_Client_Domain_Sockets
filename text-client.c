#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

  struct sockaddr_un address;
  int num_lines, total_bytes = 0;
  char rand[32], buff[2048], text[2048], output[2048], *misc;
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

  address.sun_family = AF_UNIX;
  strncpy(address.sun_path, argv[1], sizeof(address.sun_path) - 1);
  int rv = connect(sockfd, (struct sockaddr *)&address, sizeof address);

  write(sockfd, argv[2], strlen(argv[2]));

  int n = read(sockfd, misc, 1);
  misc[n] = '\0';
  write(sockfd, argv[3], strlen(argv[3])+1);
  read(sockfd, buff, sizeof(buff));
  num_lines = atoi(buff);

  if (n > 0) {
    fprintf(stderr, "SERVER CONNECTION ACCEPTED\n");
    for (int i = 1; i <= num_lines; i++) {
      n = read(sockfd, rand, 32);
      rand[n] = '\0';

      n = read(sockfd, buff, atoi(rand));
      if (i == num_lines && num_lines != 1 && buff[atoi(rand) - 1] == '\n') {
        buff[n - 1] = '\0';
        total_bytes = total_bytes + 1;
      } else {
        buff[n] = '\0';
      }
      fprintf(stdout, "%d\t%s", i, buff);
      total_bytes = total_bytes + strlen(buff);
    }
    fflush(stdout);
    fprintf(stderr, "\nBYTES RECEIVED: %d\n", total_bytes);
  }
  close(sockfd);
  exit(0);
}
