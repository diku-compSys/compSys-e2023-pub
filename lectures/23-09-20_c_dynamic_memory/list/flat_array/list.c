#include <stdlib.h>
#include "list.h"
#include <stdio.h>

struct list {
  void **data;
  int length;
};


struct list *list_create() {
  struct list *list = malloc(sizeof(struct list));

  list->length = 0;
  list->data = NULL;

  return list;
}


void list_free(struct list *list) {

  if (list == NULL)
    return;

  if (list->data != NULL) {
    free(list->data);
  }

  free(list);
}


int list_insert_first(struct list *list, void *data) {

  if (list == NULL)
    return 1;

  int old_length  = list->length;
  int new_length  = old_length + 1;

  void **old_data = list->data;
  void **new_data = malloc(new_length * sizeof(void*));

  new_data[0] = data;

  if (old_data != NULL) {
    for (int i = 0; i < old_length; i++) {
      new_data[i+1] = old_data[i];
    }

    free(old_data);
  }

  list->data   = new_data;
  list->length = new_length;
  return 0;
}


int list_remove_first(struct list *list, void **dest) {
  if (list == NULL || list->data == NULL)
    return 1;

  int old_length  = list->length;
  int new_length  = old_length - 1;

  void **old_data = list->data;
  void **new_data;

  *dest = old_data[0];


  if (new_length >= 1) {
    new_data = malloc(new_length * sizeof(void*));
    for (int i = 0; i < new_length; i++) {
      new_data[i] = old_data[i+1];
    }

  } else {
    new_data = NULL;
  }

  list->data   = new_data;
  list->length = new_length;

  free(old_data);

  return 0;
}


void list_map(struct list *list, map_fn f, void *aux) {

  if (list == NULL)
    return;

  void **data = list->data;

  for (int i = 0; i < list->length; i++) {
    data[i] = f(data[i], aux);
  }
}
