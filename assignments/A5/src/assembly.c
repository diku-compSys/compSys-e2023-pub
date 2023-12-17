#include "assembly.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct entry
{
  int valid;
  int addr;
  const char *text;
};

struct assembly
{
  int table_size;
  struct entry *lookup_table;
};

#define NOT_FOUND -1

// Hashing with linear probing...

int assembly_find_entry(struct assembly *as, int addr)
{
  int idx = addr % as->table_size;
  for (int offset = 0; offset < 4; offset++)
  {
    struct entry *e = &(as->lookup_table[idx]);
    if (e->valid && e->addr == addr)
      return idx;
    ++idx;
    if (idx == as->table_size)
      idx = 0;
  }
  return NOT_FOUND;
}

int assembly_find_empty(struct assembly *as, int addr)
{
  int idx = addr % as->table_size;
  for (int offset = 0; offset < 4; offset++)
  {
    struct entry *e = &(as->lookup_table[idx]);
    if (!e->valid)
      return idx;
    ++idx;
    if (idx == as->table_size)
      idx = 0;
  }
  return NOT_FOUND;
}

void assembly_grow_and_rehash(struct assembly *as)
{
  int old_size = as->table_size;
  struct entry *old_table = as->lookup_table;
  int new_size = 1 + 2 * old_size;
  int done;
  do
  {
    done = 1;
    as->lookup_table = calloc(sizeof(struct entry), new_size);
    // printf("Growing assembly size to %d with table at %p\n", new_size, as->lookup_table);
    as->table_size = new_size;
    for (int i = 0; i < old_size; ++i)
    {
      if (old_table[i].valid)
      {
        int new_idx = assembly_find_empty(as, old_table[i].addr);
        if (new_idx == NOT_FOUND)
        {
          // printf(" ** Collision, need a bigger table **\n");
          free(as->lookup_table);
          done = 0;
          new_size = 1 + new_size * 2;
          break;
        }
        // printf("    %d -> %d\n", i, new_idx);
        as->lookup_table[new_idx] = old_table[i];
      }
    }
  } while (!done);
  // printf("Done rehashing\n");
  free(old_table);
}

void assembly_set(struct assembly *as, int addr, const char *text)
{
  int idx = assembly_find_entry(as, addr);
  if (idx == NOT_FOUND)
  {
    idx = assembly_find_empty(as, addr);
    while (idx == NOT_FOUND)
    {
      // printf("No free entry for %d\n", addr);
      assembly_grow_and_rehash(as);
      idx = assembly_find_empty(as, addr);
    }
  }
  // printf("Setting entry at %d for addr %d\n", idx, addr);
  struct entry *e = &(as->lookup_table[idx]);
  e->text = strdup(text);
  e->addr = addr;
  e->valid = 1;
}

const char *assembly_get(struct assembly *as, int addr)
{
  int idx = assembly_find_entry(as, addr);
  if (idx == NOT_FOUND)
    return "";
  return as->lookup_table[idx].text;
}

struct assembly *assembly_create()
{
  struct assembly *as = (struct assembly *)malloc(sizeof(struct assembly));
  int size = 4;
  as->table_size = size;
  struct entry *table = calloc(sizeof(struct entry), size);
  as->lookup_table = table;
  return as;
}

void assembly_delete(struct assembly *as)
{
  for (int k = 0; k < as->table_size; ++k)
  {
    struct entry *e = as->lookup_table + k;
    if (e->valid)
    {
      free((void *)e->text);
      e->valid = 0;
    }
  }
  free(as->lookup_table);
  free(as);
}
