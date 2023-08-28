#ifndef LIST_H
#define LIST_H

struct list;

// Create new list.  Initially empty.  NULL on error.
struct list* list_create();

// Deallocates list.
void list_free(struct list*);

// Insert element at head of list.  Returns 0 on success.
int list_insert_first(struct list*, void*);

int list_remove_first(struct list*, void**);

typedef void* (*map_fn)(void*, void*);

void list_map(struct list*, map_fn, void*);

#endif
