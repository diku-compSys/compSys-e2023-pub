// Futures are a programming abstraction where we can asynchronously
// create a value by providing a pointer to a function that creates
// it.  When we then later ask for the actual value, we either receive
// the value immediately, or block until it is available.  Futures are
// a pretty simple way to exploit parallelism.  The implementation in
// this header file is simplistic, in that it does not do any thread
// pooling.

#include <pthread.h>
#include <assert.h>

// We represent a future as the data and a thread handle.
struct future {
  void *data;
  pthread_t p;
};

// Create a new future whose value is computed by the given function,
// which returns the address of the value.
typedef void* (*future_fn)(void*);
struct future* future_create(future_fn, void*);

// Get the value from the future and destroy the future.  Blocks if
// necessary.
void* future_get(struct future*);

struct future* future_create(future_fn f, void *arg) {
  struct future *future = malloc(sizeof(struct future));
  int ret = pthread_create(&future->p, NULL, f, arg);
  assert(ret == 0);
  return future;
}

void* future_get(struct future* future) {
  void *vp;
  int ret = pthread_join(future->p, &vp);
  assert(ret == 0);
  free(future);
  return vp;
}
