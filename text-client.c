#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  struct sockaddr_un address;
  int reading, num_bytes = 0, i = 1;
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  char tmp[2048];
  address.sun_family = AF_UNIX;
  strncpy(address.sun_path, argv[1], sizeof(address.sun_path) - 1);
  int rv = connect(sockfd, (struct sockaddr *)&address, sizeof address);

  if (strlen(argv[3]) < 1) {
    argv[3] = "\030";
  }

  write(sockfd, argv[2], 512); // sends path
  write(sockfd, argv[3], 512); // sends text

  while (reading = read(sockfd, tmp, sizeof(tmp))) {
    fprintf(stderr, "SERVER CONNECCTION ACCEPTED\n");
    if (strlen(tmp) > 0 && strlen(argv[3]) > 0) {
      num_bytes += strlen(tmp);
      fprintf(stdout, "%d\t%s", i, tmp);
      memset(tmp, '\0', sizeof(tmp));
      i++;
    }
  }
  fprintf(stderr, "\nBYTES RECEIVED: %d\n", num_bytes);
  close(sockfd);
  exit(0);
}
