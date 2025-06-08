#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX_LINES = 5;

int main() {
  char *lines[5];
  size_t n = 0;
  char *line = NULL;
  int count = 0;

  while (1) {
    printf("Enter Input: ");
    ssize_t len = getline(&line, &n, stdin);
    if (len == -1)
      break;

    if (line[len - 1] == '\n')
      line[len - 1] = '\0';

    if (count == MAX_LINES) {
      free(lines[0]);
      for (int i = 1; i < MAX_LINES; i++) {
        lines[i - 1] = lines[i];
      }
      count--;
    }

    lines[count++] = strdup(line);

    if (strcmp(line, "print") == 0) {
      for (int i = 0; i < count; i++) {
        printf("%s\n", lines[i]);
      }
    }
  }

  for (int i = 0; i < count; i++) {
    free(lines[i]);
  }
  free(line);
  return 0;
}
