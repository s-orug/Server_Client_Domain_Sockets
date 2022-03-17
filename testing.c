//#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>


// char *text_parse(char *word, char *file);
char* text(char *word, char *file){
  char path[2048], command[1024], lines_command[1024];
  sprintf(command, "grep \"%s\" %s ", word, file);
  char *line=NULL, *store;
  FILE *fp;
  size_t one = 0;
  fp = popen(command, "r");
  while (getline(&line, &one, fp) > 1) {
  
  asprintf(&store, "%s%s", (char *const)store,(char *const)line);

  }
  return store; 
  // store[strlen(store)-1] = '\0';
}


int main(int argc, char *argv[]) {
  char word[] = " ",file[] = "dat/dante.txt";
  char* data = text(word, file);
  printf("%s", data);
  // store[strlen(store)-1] = '\0';
}
