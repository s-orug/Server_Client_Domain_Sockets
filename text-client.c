#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  struct sockaddr_un address;
  int reading, num_bytes = 0, i = 0;
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
    if (i == 0) { // if it is the first itereation,
                  // then the server accepted so its written to stdout
      fprintf(stderr, "SERVER CONNECTION ACCEPTED\n");
      i++;
    }
    if (strlen(tmp) > 0 && strlen(argv[3]) > 0) {
      num_bytes += strlen(tmp);
      fprintf(stdout, "%d\t%s", i,
              tmp); // prints out each line in a formatted manner
      memset(tmp, '\0', sizeof(tmp));
      i++;
    }
  }

  fprintf(stderr, "\nBYTES RECEIVED: %d\n",
          num_bytes); // logging number of bytes received
  close(sockfd);      // closes the socket file descriptor
  exit(0);
}
