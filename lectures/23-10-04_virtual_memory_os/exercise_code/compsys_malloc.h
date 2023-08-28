#ifndef COMPSYS_MALLOC_H
#define COMPSYS_MALLOC_H

void compsys_heap_init();
void *compsys_calloc(size_t nmemb, size_t size);
void *compsys_malloc(size_t size);
void compsys_free(void *ptr);
void *compsys_realloc(void *ptr, size_t size);

#endif
