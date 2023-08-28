# Exercises

## Memory mapping

Given an input file `input.txt`, with the contents `"CompSys\n"`,
write a C program that uses `mmap` to change the contents to
`"DumbSys\n"`.

## Heap management

Consider an allocator that uses an implicit free list.  The payload is
preceded by header and a footer, each taking up a single 32-bit word,
and containing the size (in bytes) of the block.  The header and
footer words for a block are always identical.

The size of each memory block must be a multiple of 8 bytes.  This
means that the least significant three bits of the size is unused for
the size, and therefore these are used to encode more information:

* Bit 0 (the least significant bit) indicates the use of the current
  block: 1 for allocated, 0 for free.

* Bit 1 indicates the use of the *previous* adjacent block: 1 for
  allocated, 0 for free.

* Bit 2 is unused and is always set to 0.

* The remaining bits contain the size of the block.  We pretend that
  the least significant 3 bits are zero when interpreting the
  header/footer as a size.


Given the following initial heap contents, show the new contents of
the heap after a call to `free(0x100f010)`.  Your answers should be
given as hex values.  Note that the addresses grow from bottom up.
Assume that the allocator uses immediate coalescing, that is, adjacent
free blocks are merged immediately each time a block is freed.

| Address | Word |
| --- | --- |
| 0x100f028 | 0x00000013 |
| 0x100f024 | 0x100f611c |
| 0x100f020 | 0x100f512c |
| 0x100f01c | 0x00000013 |
| 0x100f018 | 0x00000011 |
| 0x100f014 | 0x100f511c |
| 0x100f010 | 0x100f601c |
| 0x100f00c | 0x00000011 |
| 0x100f008 | 0x0000001a |
| 0x100f004 | 0x100f601c |
| 0x100f000 | 0x100f511c |
| 0x100affc | 0x100f511c |
| 0x100afe8 | 0x0000001a |
| 0x100afe4 | 0x0000001a |

As a starting point, here's part of the solution:

| Address | Word |
| --- | --- |
| 0x100f028 | |
| 0x100f024 | 0x100f611c |
| 0x100f020 | 0x100f512c |
| 0x100f01c |  |
| 0x100f018 |  |
| 0x100f014 | 0x100f511c |
| 0x100f010 | 0x100f601c |
| 0x100f00c |  |
| 0x100f008 |  |
| 0x100f004 | 0x100f601c |
| 0x100f000 | 0x100f511c |
| 0x100affc | 0x100f511c |
| 0x100afe8 |  |
| 0x100afe4 |  |

<details>
<summary>Open this to see the answer</summary>

| Address | Word |
| --- | --- |
| 0x100f028 | 0x00000011 |
| 0x100f024 | 0x100f611c |
| 0x100f020 | 0x100f512c |
| 0x100f01c | 0x00000011 |
| 0x100f018 | 0x0000002a |
| 0x100f014 | 0x100f511c |
| 0x100f010 | 0x100f601c |
| 0x100f00c | 0x00000011 |
| 0x100f008 | 0x0000001a |
| 0x100f004 | 0x100f601c |
| 0x100f000 | 0x100f511c |
| 0x100affc | 0x100f511c |
| 0x100afe8 | 0x0000001a |
| 0x100afe4 | 0x0000002a |

</details>

## Improving compsys_malloc.c (The Fun One)

The provided `compsys_malloc.c` allocates out of a fixed-size heap
(256 bytes by default).  Rewrite it to use `mmap()` to instead request
memory from the kernel as necessary.
