#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
  printf("Hello World\n");
  char *line = NULL;
  size_t len = 0;

  printf("Enter text: \n");
  size_t read = getline(&line, &len, stdin);

  if (read == -1) {
    printf("Failure reading line\n");
    return 1;
  }

  printf("Tokens:\n");
  char *ret = NULL;
  char *saveptr = NULL;
  char *str = line;

  while ((ret = strtok_r(str, " \n", &str))) {
    printf(" %s\n", ret);
  }

  free(line);
  return 0;
}
