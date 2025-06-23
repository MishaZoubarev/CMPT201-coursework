#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  while (free_list_ptr->next != NULL) {
    if (free_list_ptr->size >= size)
      return free_list_ptr->id;
    free_list_ptr = free_list_ptr->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t best_fit_size = UINT64_MAX;
  while (free_list_ptr->next != NULL) {
    if (free_list_ptr->size >= size && free_list_ptr->size < best_fit_size) {
      best_fit_size = free_list_ptr->size;
      best_fit_id = free_list_ptr->id;
    }
    free_list_ptr = free_list_ptr->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  uint64_t worst_fit_size = 0;
  while (free_list_ptr->next != NULL) {
    if (free_list_ptr->size >= size && free_list_ptr->size > worst_fit_size) {
      worst_fit_size = free_list_ptr->size;
      worst_fit_id = free_list_ptr->id;
    }
    free_list_ptr = free_list_ptr->next;
  }
  return worst_fit_id;
}

int main(void) {
  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("The ID for first-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for best-fit algorithm is: %d\n", best_fit_id);
  printf("The ID for worst-fit algorithm is: %d\n", worst_fit_id);
  return 0;
}

/*
 * function coalesce(free_list_head, newly_freed_block) {
 *  prev = NULL;
 *  curr = free_list_head
 *
 *  while curr != NULL && curr < newly_freed_block{
 *    prev = curr
 *    curr = curr.next
 *  }
 *
 *  if prev != NULL && address(prev) + size(prev) == address(newly_freed_block)
 *{ prev.size = prev.size + newly_freed_block.size newly_freed_block = prev
 *  }
 *  else {
 *    newly_freed_block.next = curr
 *    if prev != NULL
 *      prev.next = newly_freed_block
 *    }
 *    else {
 *      free_list_head = newly_freed_block
 *    }
 *
 *  if curr != NULL && address(newly_freed_block) + size(newly_freed_block) ==
 *address(curr){ newly_freed_block.size = newly_freed_block.size + curr.size
 *    newly_freed_block.next = curr.next
 *  }
 *}
 */
