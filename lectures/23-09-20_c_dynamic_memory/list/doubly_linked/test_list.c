#include "list.h"
#include <stdio.h>
#include <assert.h>

void* print_elem(void *data, void *aux_data) {
  (void)aux_data;
  int *int_data = (int*)data;
  printf("elem: %d\n", *int_data);
  return data;
}

void print_list(struct list *l) {
  list_map(l, print_elem, NULL);
}

void* inc_elem(void *data, void *aux_data) {
  int *int_data = (int*)data;
  int *aux_int_data = (int*)aux_data;
  *int_data += *aux_int_data;
  return data;
}

void inc_list(struct list *l, int K) {
  list_map(l, inc_elem, &K);
}

int main() {
  int K = 42;

  int x = 1, y = 2, z = 3;
  void *d;

  struct list *l = list_create();
  assert(l != NULL);

  // test removing from initially empty list
  assert(list_remove_first(l, &d) == 1);

  // test inserting a couple of elements
  assert(list_insert_first(l, &x) == 0);
  assert(list_insert_first(l, &y) == 0);
  assert(list_insert_first(l, &z) == 0);


  // test removing elements
  assert(list_remove_first(l, &d) == 0);
  assert(d == &z);
  assert(list_remove_first(l, &d) == 0);
  assert(d == &y);
  assert(list_remove_first(l, &d) == 0);
  assert(d == &x);

  // test removing from newly empty list
  assert(list_remove_first(l, &d) == 1);


  assert(list_insert_first(l, &x) == 0);
  assert(list_insert_first(l, &y) == 0);
  assert(list_insert_first(l, &z) == 0);

  print_list(l);
  inc_list(l, K);
  print_list(l);

  // assert list properly mapped
  assert(list_remove_first(l, &d) == 0);
  assert(d == &z && z == 3+42);
  assert(list_remove_first(l, &d) == 0);
  assert(d == &y && y == 2+42);
  assert(list_remove_first(l, &d) == 0);
  assert(d == &x && x == 1+42);

  list_free(l);
}
