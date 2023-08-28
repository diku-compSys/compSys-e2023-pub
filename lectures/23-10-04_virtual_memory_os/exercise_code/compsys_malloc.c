/* Uses explicit free lists. */

#include <stdint.h>
#include <stdlib.h>
#include "compsys_malloc.h"

#define HEAP_SIZE 256 /* 256 byte heap - puny! */

typedef struct free_block {
  size_t size;
  struct free_block *next;
} free_block_t;

static const size_t MIN_ALLOC_SIZE = sizeof(free_block_t);

typedef unsigned char byte;

byte heap[HEAP_SIZE];

free_block_t *free_list;

/* Initialise the heap - compsys_malloc() et al won't work unless this
   is called first. */
void compsys_heap_init()
{
  free_list = (free_block_t*) heap;
  free_list->size = HEAP_SIZE;
  free_list->next = NULL;
}

/* Return a block of at least size bytes, or NULL if no such block
   can be found.  */
void *compsys_malloc(size_t size) {
  free_block_t *block;
  free_block_t **prev_p; /* Previous link so we can remove an element */
  if (size == 0) {
    return NULL;
  }

  /* Ensure block is big enough for bookkeeping. */
  size=size < MIN_ALLOC_SIZE ? MIN_ALLOC_SIZE : size;
  /* Word-align */
  if (size % 4 != 0) {
    size &= ~3;
    size += 4;
  }

  /* Iterate through list of compsys_free blocks, using the first that is
     big enough for the request. */
  for (block = free_list, prev_p = &free_list;
       block;
       prev_p = &(block->next), block = block->next) {
    if ( (int)( block->size - size - sizeof(size_t) ) >=
         (int)( MIN_ALLOC_SIZE+sizeof(size_t) ) ) {
      /* Block is too big, but can be split. */
      block->size -= size+sizeof(size_t);
      free_block_t *new_block =
        (free_block_t*)(((byte*)block)+block->size);
      new_block->size = size+sizeof(size_t);
      return ((byte*)new_block)+sizeof(size_t);
    } else if (block->size >= size + sizeof(size_t)) {
      /* Block is big enough, but not so big that we can split
         it, so just return it */
      *prev_p = block->next;
      return ((byte*)block)+sizeof(size_t);
    }
    /* Else, check the next block. */
  }

  /* No heap space left. */
  return NULL;
}

/* Return the block pointed to by ptr to the compsys_free pool. */
void compsys_free(void *ptr)
{
  if (ptr != NULL) { /* Freeing NULL is a no-op */
    free_block_t *block = (free_block_t*)((byte*)ptr-sizeof(size_t));
    free_block_t *cur_block;
    free_block_t *prev_block;

    /* Iterate through the free list, which is sorted by
       increasing address, and insert the newly compsys_freed block at the
       proper position. */
    for (cur_block = free_list, prev_block = NULL;
         ;
         prev_block = cur_block, cur_block = cur_block->next) {
      if (cur_block > block || cur_block == NULL) {
        /* Insert block here. */
        if (prev_block == NULL) {
          free_list = block;
        } else {
          prev_block->next = block;
        }
        block->next = cur_block;

        if (prev_block != NULL &&
            (size_t)((byte*)block - (byte*)prev_block) == prev_block->size) {
          /* Merge with previous. */
          prev_block->size += block->size;
          prev_block->next = cur_block;
          block = prev_block;
        }

        if (cur_block != NULL &&
            (size_t)((byte*)cur_block - (byte*)block) == block->size) {
          /* Merge with next. */
          block->size += cur_block->size;
          block->next = cur_block->next;
        }
        return;
      }
    }
  }
}

void *calloc(size_t nmemb, size_t size)
{
  size_t i;
  byte *ptr = compsys_malloc(nmemb*size);
  if (ptr != NULL) {
    for (i = 0; i < nmemb*size; i++) {
      ptr[i] = 0;
    }
  }
  return ptr;
}

void *realloc(void *ptr, size_t size)
{
  byte *new_ptr;
  size_t i;
  if (ptr == NULL) {
    return compsys_malloc(size);
  }

  if (ptr != NULL && size == 0) {
    compsys_free(ptr);
    return NULL;
  }

  /* Simple implementation: allocate new space and copy the contents
     over.  Exercise: Improve this by searching through the compsys_free
     list and seeing whether an actual enlargement is possible. */
  new_ptr = compsys_malloc(size);
  if (new_ptr != NULL) {
    for (i = 0; i < size; i++) {
      new_ptr[i] = ((byte*)ptr)[i];
    }
    compsys_free(ptr);
  }
  return new_ptr;
}
