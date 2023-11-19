#include "lib.h"

asm("  .globl _start");
asm("_start:");
asm("  li a0, 0x1000000");  // set start of stack (which grows in opposite direction)
asm("  mv sp, a0");
asm("  li a0, 0x2000000");  // set start of heap area
asm("  call init_heap");
asm("  li a0, 0x1000000");  // arg area is right after stack (filled by simulator)
asm("  call args_to_main");
asm("  call terminate");

extern int main(int argc, const char* argv);

int args_to_main(int* args_ptr) {
  int argc = *args_ptr;
  const char* argv = (const char*)args_ptr + sizeof(int);
  return main(argc, argv);
}

char inp() {
  char c;
  asm volatile("  li a7,1" : : : "a7");
  asm volatile("  ecall" : : : "a0");
  asm volatile("  mv %0,a0" : "=r" (c));
  return c;
}

void outp(char c) {
  asm volatile("  mv a0,%0" : : "r" (c) : "a0");
  asm volatile("  li a7,2" : : : "a7");
  asm volatile("  ecall");
}

void terminate(int status) {
  asm volatile("  mv a0,%0" : : "r" (status));
  asm volatile("  li a7,3");
  asm volatile("  ecall");
  // never returns (stops machine)
}

void print_string(const char* p) {
  while (*p) { outp(*p++); };
}

void read_string(char* buffer, int max_chars) {
  int c = inp();
  while (c != '\n' && c != '\r' && max_chars > 1) {
    *buffer++ = c;
    --max_chars;
    c = inp();
  }
  // zero terminate:
  *buffer = 0;
}



unsigned int str_to_uns(const char* str) {
  unsigned int val = *str++ - '0';
  while (*str) {
    val = val * 10 + *str++ - '0';
  }
  return val;
}

int uns_to_str(char* buffer, unsigned int val) {
  if (val == 0) {
    buffer[0] = '0';
    buffer[1] = 0;
    return 1;
  }
  // produce digits in reverse order
  char* ptr = buffer;
  while (val) {
    *ptr++ = (val % 10) + '0';
    val = val / 10;
  }
  *ptr-- = 0;
  int retval = ptr - buffer;
  // reverse
  while (ptr > buffer) {
    char tmp = *ptr;
    *ptr = *buffer;
    *buffer = tmp;
    --ptr;
    ++buffer;
  }
  return retval;
}

// An allocator for small blocks.
#define SMALL_BLOCK_LIMIT 4096
#define MIN_ALLOCATION 100
// must be power of two:
#define BLOCK_SIZE_STEP 8
#define NUM_SIZES (SMALL_BLOCK_LIMIT / BLOCK_SIZE_STEP)
typedef void* vp;
vp small_block_headers[NUM_SIZES];
vp free_space;
int initialized;

void init_heap(void* heap_start) {
  initialized = 0;
  free_space = heap_start;
}

void* allocate(int size) {
  if (!initialized) {
    initialized = 0;
    for (int j = 0; j < NUM_SIZES; j++) small_block_headers[j] = NULL;
  }
  if (size < 1) return NULL;
  // make room for size in front of every allocation
  // storing the size allows us to get it back on release
  size += sizeof(int);
  // align size
  int offset = size & (BLOCK_SIZE_STEP - 1);
  if (offset) {
    size = (size & ~offset) + BLOCK_SIZE_STEP;
  }
  int num_size = size / BLOCK_SIZE_STEP;
  if (num_size >= NUM_SIZES) {
    // large blocks requires a more complex machinery (dividing/joining blocks)
    // this is left as an exercise :-)
    return NULL;
  }
  vp* header = small_block_headers + num_size;
  if (*header == NULL) {
    // allocate a chunk
    int allocation = size * 10;
    if (allocation < MIN_ALLOCATION) {
      int num_chunks = MIN_ALLOCATION / size;
      allocation = num_chunks * size;
    }
    char* chunk = (char*) free_space;
    char* end_chunk = chunk + allocation;
    free_space = end_chunk;
    // split the chunk into blocks and place a linked list inside them
    end_chunk -= size;
    while (end_chunk >= chunk) {
      *(vp*)end_chunk = *header;
      *header = end_chunk;
      end_chunk -= size;
    }
  }
  // unlink
  vp* block = *header;
  *header = *block;
  // save size (including the size field itself)
  *block = (void*)size;
  return block + 1;
}

void release(void* memory) {
  char* chunk = (char*) memory;
  chunk = chunk - 4;
  int size = *(int*)chunk;
  int num_size = size / BLOCK_SIZE_STEP;
  vp* header = small_block_headers + num_size;
  *(vp*)chunk = *header;
  *header = chunk;
}
