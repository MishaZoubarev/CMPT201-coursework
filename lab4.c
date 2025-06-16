#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define _DEFAULT_SOURCE
#define _ISOC99_SOURCE

#define BLOCK_SIZE 128
#define HEAP_SIZE 256
#define BUF_SIZE 64

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);

  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

void print_block(char *start) {
  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); ++i) {
    char *addr = start + sizeof(struct header) + i;
    uint64_t val = (uint64_t)*addr;
    print_out("%lu\n", &val, sizeof(val));
  }
}

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int fill_value) {
  block->size = size;
  block->next = next;
  memset(block + 1, fill_value, size - sizeof(struct header));
}

int main(void) {
  char *heap_start = sbrk(HEAP_SIZE);
  if (heap_start == (void *)-1)
    handle_error("sbrk");

  struct header *first = (struct header *)heap_start;
  struct header *second = (struct header *)(heap_start + BLOCK_SIZE);

  initialize_block(first, BLOCK_SIZE, NULL, 0);
  initialize_block(second, BLOCK_SIZE, first, 1);

  print_out("first block:       %p\n", first, sizeof(first));
  print_out("second block:      %p\n", second, sizeof(second));

  print_out("first block size:  %lu\n", &first->size, sizeof(first->size));
  print_out("first block next:  %p\n", &first->next, sizeof(first->next));
  print_out("second block size: %lu\n", &second->size, sizeof(second->size));
  print_out("second block next: %p\n", &second->next, sizeof(second->next));

  print_block((char *)first);
  print_block((char *)second);

  return 0;
}
