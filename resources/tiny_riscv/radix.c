#include "lib.h"

struct node;
struct leaf { int count_zero; int count_one; };
struct interior { struct node* zero; struct node* one; };
struct node {
  int bit_pos;
  int number;
  union { struct leaf leaf; struct interior interior; };
};

struct node* tree = NULL;

#define MAX_BITS 1<<30

// Note: bit_pos is one-hot encoded bit positions
inline int lower_bits(int bit_pos) { return bit_pos - 1; }
inline int higher_bits(int bit_pos) { return 0 - bit_pos - bit_pos; }
inline int not_lower_bits(int bit_pos) { return ~lower_bits(bit_pos); }
inline int not_higher_bits(int bit_pos) { return ~higher_bits(bit_pos); }
// range including high pos, but excluding low pos
inline int bit_range(int bit_pos_high, int bit_pos_low) { return (higher_bits(bit_pos_low) & not_higher_bits(bit_pos_high)); }

void add_number(int number) {
  struct node** parent = &tree;
  for (int bit_pos = MAX_BITS; bit_pos >= 1; bit_pos >>= 1) {
    struct node* nptr = *parent;
    if (nptr == NULL) {
      // create a leaf
      nptr = allocate(sizeof(struct node));
      *parent = nptr;
      nptr->bit_pos = 1;
      nptr->number = number;
      nptr->leaf.count_zero = (number & 1) == 0;
      nptr->leaf.count_one = (number & 1) == 1;
      return;
    }
    if (bit_pos > nptr->bit_pos) {
      int mask = bit_range(bit_pos, nptr->bit_pos);
      int diff = mask & (number ^ nptr->number);
      if (diff) {
        // locate most significant differing bit (there must be one)
        while ((bit_pos & diff) == 0) { bit_pos >>= 1; };
        // inject an interior node for branching at bit_pos, above the earlier found subtree
        struct node* nptr2 = allocate(sizeof(struct node));
        *parent = nptr2;
        nptr2->bit_pos = bit_pos;
        nptr2->number = number;
        if ((number & bit_pos) == 0) {
          nptr2->interior.one = nptr;
          nptr2->interior.zero = NULL;
          parent = & nptr2->interior.zero;
        } else {
          nptr2->interior.zero = nptr;
          nptr2->interior.one = NULL;
          parent = & nptr2->interior.one;
        }
        continue;
      }
      // we may use the found node
      bit_pos = nptr->bit_pos;
    }
    if (bit_pos > 1) {
      if (bit_pos & number)
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

int* take_numbers_2(struct node** parent, int* buffer, int* end) {
  struct node* nptr = *parent;
  if (nptr) {
    if (nptr->bit_pos == 1) {
      while (buffer < end && nptr->leaf.count_zero) {
        *buffer++ = nptr->number & ~1;
        nptr->leaf.count_zero--;
      }
      while (buffer < end && nptr->leaf.count_one) {
        *buffer++ = nptr->number | 1;
        nptr->leaf.count_one--;
      }
      // remove "empty" node
      if (nptr->leaf.count_zero == 0 && nptr->leaf.count_one == 0) {
        release(nptr);
        *parent = NULL;
      }
    } else {
      buffer = take_numbers_2(& nptr->interior.zero, buffer, end);
      buffer = take_numbers_2(& nptr->interior.one, buffer, end);
      // remove node without subnodes
      if (nptr->interior.zero == NULL && nptr->interior.one == NULL) {
        release(nptr);
        *parent = NULL;
      }
    }
  }
  return buffer;
}

int take_numbers(int* buffer, int max_nums) {
  return take_numbers_2(& tree, buffer, buffer + max_nums) - buffer;
}

void release_tree(struct node* tree) {
  if (tree) {
    if (tree->bit_pos > 1) {
      release_tree(tree->interior.zero);
      release_tree(tree->interior.one);
    }
    release(tree);
  }
}

void main(int argc, char* argv[]) {

  if (argc != 3) {
    print_string("Use: radix input-file output-file\n");
    terminate(-1);
  }
  int in_file = open_file(argv[1], "r");
  if (in_file < 0) {
    print_string("Could not open input file\n");
  }
  int out_file = open_file(argv[2], "w");
  if (out_file < 0) {
    print_string("Could not open output file\n");
  }
  while (1) {
    int numbers[100];
    int out_numbers[100];
    int read = read_int_buffer(in_file, numbers, 100);
    if (read <= 0) break;
    for (int n = 0; n < read; ++n) {
      if (numbers[n] < 0) {
        int limit = -numbers[n];
        while (limit > 0) {
          int take_max = limit < 100 ? limit : 100;
          int taken = take_numbers(out_numbers, take_max);
          int to_write = taken;
          while (to_write > 0) {
            int written = write_int_buffer(out_file, out_numbers, to_write);
            to_write -= written;
          }
          limit -= taken;
          if (taken == 0) // empty tree
            break;
        }
      } else {
        add_number(numbers[n]);
      }
    }
  }
  close_file(in_file);
  close_file(out_file);
  release_tree(tree);
}

