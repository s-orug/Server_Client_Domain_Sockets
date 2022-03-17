#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>

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
  char word[] = " ", file[] = "dat/dante.txt";
  char *data = text_parse(word, file);
  printf("%s", data);
  
}
