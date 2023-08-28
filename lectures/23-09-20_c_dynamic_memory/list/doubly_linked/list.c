#include <stdlib.h>
#include "list.h"
#include <stdio.h>

struct node {
  void *data;
  struct node *next;
  struct node *prev;
};

struct list {
  struct node *first;
  struct node *last;
};


struct list *list_create() {
  struct list *list = malloc(sizeof(struct list));

  list->first = NULL;
  list->last  = NULL;

  return list;
}


void list_free(struct list *list) {

  if (list == NULL)       // nothing to free
    return;

  struct node *node = list->first;

  while (node != NULL) {  // free nodes in list, if any
    struct node *next = node->next;
    free(node);
    node = next;
  }

  free(list);
}


int list_insert_first(struct list *list, void *data) {

  if (list == NULL) {        // if list un-initialized
    return 1;
    // list = list_create(); // could also create new list here instead of returning error
  }

  struct node *new_first = malloc(sizeof(struct node));

  new_first->data = data;
  new_first->next = list->first;

  if (list->first == NULL)
    list->last = new_first;         // if list previously empty, new node is also last
  else
    list->first->prev = new_first;

  list->first = new_first;
  return 0; }


int list_remove_first(struct list* list, void** dest) {

  if (list == NULL || list->first == NULL)  // if list un-initialized or empty
    return 1;

  struct node *old_first = list->first;
                                   
  *dest       = old_first->data;            // pop data
  list->first = old_first->next;

  if (list->first == NULL)                  // if list is now empty
    list->last = NULL;

  free(old_first);
  return 0;
}

void list_map(struct list* list, map_fn f, void *aux) {
  
  if (list == NULL)   // if list-uninitialized; nothing to map :)
    return;

  struct node *node = list->first;
  while (node != NULL) {
    node->data = f(node->data, aux);
    node = node->next;
  }
}
