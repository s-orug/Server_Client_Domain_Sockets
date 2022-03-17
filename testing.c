#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>

char *text_parse(char *word, char *file)
{
  FILE *fp;
  size_t one = 0;
  char command[1024], *line = NULL, *store = "";
  sprintf(command, "grep \"%s\" %s ", word, file);
  fp = popen(command, "r");
  while (getline(&line, &one, fp) > 1)
  {
    asprintf(&store, "%s%s", (char *const)store, (char *const)line);
  }
  return store;
}
char *append(char *str1, char *str2)
{
  char *ret_append = calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));
  for (int i = 0; i < strlen(str1); i++)
  {
    ret_append[i] = str1[i];
  }
  for (int j = 0; j < strlen(str2); j++)
  {
    ret_append[j + strlen(str1)] = str2[j];
  }
  free(ret_append);
}
char *text_parse2(char *word, char *file)
{
  FILE *fp;
  size_t one, retSize = 1;
  char command[1024], *line = NULL, *store = " ";
  char *ret = calloc(retSize, sizeof(char));
  sprintf(command, "grep \"%s\" %s ", word, file);
  fp = popen(command, "r");
  while (getline(&line, &one, fp) > 1)
  {
    retSize = strlen(line) + strlen(ret);
    ret = realloc(ret, retSize * sizeof(char));
    ret = append(ret, line);
  }
  ret[retSize - 1] = '\0';
  printf("%ld", strlen(ret));
  free(ret);
  return store;
}

int main(int argc, char *argv[])
{
  char word[] = "onle", file[] = "dat/dante.txt";
  // char *data = text_parse2(word, file); // 228056
  // printf("%s\n bytes: %ld\n", data, strlen(data));
  size_t retSize = 1;
  char *ret = calloc(retSize, sizeof(char));
}
