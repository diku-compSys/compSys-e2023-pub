#include <stdlib.h>
#include "list.h"

struct list_node {
  void *data;
  struct list_node *next;
};

struct list {
  struct list_node *head;
};

struct list* list_create() {
  struct list *list = malloc(sizeof(struct list));
  list->head = NULL;
  return list;
}

void list_free(struct list* list) {
  struct list_node *node = list->head;
  while (node != NULL) {
    struct list_node *next = node->next;
    free(node);
    node = next;
  }
  free(list);
}

int list_insert_first(struct list* list, void* data) {
  struct list_node *new_head = malloc(sizeof(struct list_node));
  new_head->data = data;
  new_head->next = list->head;

  list->head = new_head;
  return 0;
}



int list_remove_first(struct list* list, void** dest) {
  struct list_node *old_head = list->head;
  if (old_head == NULL) {
    return 1;
  }
  *dest = old_head->data;
  list->head = old_head->next;
  free(old_head);
  return 0;
}

void list_map(struct list* list, map_fn f, void *aux) {
  struct list_node *node = list->head;
  while (node != NULL) {
    node->data = f(node->data, aux);
    node = node->next;
  }
}
