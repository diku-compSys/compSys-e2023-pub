#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>

struct worker_payload {
  unsigned char *data;
  long *sum;
  size_t n; //The amount to count
};

void* thread(void* p) {
    struct worker_payload payload = *(struct worker_payload*)p;
    long local_sum = 0;
    for (size_t i = 0; i < payload.n; i++) {
        local_sum += payload.data[i];
    }
  return (void *) local_sum;
}

int main(int argc, char** argv) {
  assert(argc == 2);
  char *filename = argv[1];

  // Open the given file and determine its size.
  FILE *file = fopen(filename, "r");
  assert(file != NULL);
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  // mmap file as an array of 'size' bytes.
  unsigned char *data = mmap(NULL,
                             size,
                             PROT_READ,
                             MAP_PRIVATE,
                             fileno(file), 0);
  assert(data != MAP_FAILED);
  fclose(file);

  long sum = 0;

  pthread_t p1;
  pthread_t p2;

  struct worker_payload payload1;
  payload1.data = data;
  payload1.sum = &sum;
  payload1.n = size/2;

  struct worker_payload payload2;
  payload2.data = &data[size/2]; //Because we index and then need address of that, could we just add
  payload2.sum = &sum;
  payload2.n = size-size/2; //The other half

  pthread_create(&p1, NULL, thread, (void *) &payload1);
  pthread_create(&p2, NULL, thread, (void *) &payload2);

  long retval1; 
  pthread_join(p1, (void**)&retval1); //Null as we have passed in arg to update so dont need retval
  long retval2; 
  pthread_join(p2, (void**)&retval2);

  sum += retval1;
  sum += retval2;
  
  printf("Sum: %ld\n", sum);
}
