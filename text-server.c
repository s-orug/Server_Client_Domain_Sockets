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

    close(client_sockfd);
  }
  return 0;
}
