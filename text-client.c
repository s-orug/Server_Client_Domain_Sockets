#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
 
int main(int argc, char *argv[]) {

  struct sockaddr_un address;

  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

  address.sun_family = AF_UNIX;
  strncpy(address.sun_path, argv[1], sizeof(address.sun_path) - 1);
  int rv = connect(sockfd, (struct sockaddr *)&address, sizeof address);

  write(sockfd, argv[2], strlen(argv[2]));
  read(sockfd, "hello", 6);
  close(sockfd);
  exit(0);
}
