#include "lib.h"

struct node;
struct leaf { int count_zero; int count_one; };
struct interior { struct node* zero; struct node* one; };
struct node {
  int bit_pos;
  union { struct leaf leaf; struct interior interior; };
};

struct node* tree = NULL;

#define MAX_BITS 30

void add_number(int number) {
  struct node** parent = &tree;
  for (int bit_pos = MAX_BITS; bit_pos >= 0; bit_pos--) {
    struct node* nptr = *parent;
    if (nptr == NULL) {
      nptr = allocate(sizeof(struct node));
      *parent = nptr;
      nptr->bit_pos = bit_pos;
      nptr->interior.zero = NULL;
      nptr->interior.one = NULL;
    }
    if (bit_pos) {
      if ((1<<bit_pos) & number)
        parent = & nptr->interior.one;
      else
        parent = & nptr->interior.zero;
    }
    else {
      if (number & 1)
        nptr->leaf.count_one++;
      else
        nptr->leaf.count_zero++;
    }
  }
}

void print_numbers_2(struct node* nptr, int higher_bits) {
  char buffer[20];
  if (nptr) {
    if (nptr->bit_pos == 0) {
      for (int n = 0; n < nptr->leaf.count_zero; ++n) {
        uns_to_str(buffer, higher_bits << 1);
        print_string(buffer);
        print_string(" ");
      }
      for (int n = 0; n < nptr->leaf.count_one; ++n) {
        uns_to_str(buffer, (higher_bits << 1) | 1);
        print_string(buffer);
        print_string(" ");
      }
    } else {
      print_numbers_2(nptr->interior.zero, higher_bits << 1);
      print_numbers_2(nptr->interior.one, (higher_bits << 1) | 1);
    }
  }
}

void print_numbers() {
  print_numbers_2(tree, 0);
}

void release_tree(struct node* tree) {
  if (tree) {
    if (tree->bit_pos) {
      release_tree(tree->interior.zero);
      release_tree(tree->interior.one);
    }
    release(tree);
  }
}

void main() {
  char buffer[128];
  print_string("Angiv række af tal større end 0, et per linie, afslut med 0\n");
  while (1) {
    read_string(buffer, 128);
    unsigned int arg = str_to_uns(buffer);
    if (arg == 0) break;
    add_number(arg);
  }
  print_string("Sorterer tallene\n");
  print_numbers();
  print_string("\n");
  release_tree(tree);
}

