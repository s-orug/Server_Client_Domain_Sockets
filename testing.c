#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>

int main(int argc, char *argv[]) {
  char path[2048], command[1024], lines_command[1024], word[] = " ",
                                                       file[] = "dat/dante.txt";
  sprintf(command, "grep \"%s\" %s ", word, file);
  char *line = NULL, store = (char*)malloc (6000 * sizeof (char));;
  FILE *fp;
  size_t one = 0;
  fp = popen(command, "r");
  while (getline(&line, &one, fp) >= 1) {
    strcat(store, line);
  }
  // store[strlen(store)-1] = '\0';
  printf("%s", store);
}
