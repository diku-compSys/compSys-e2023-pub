# Theoretical Exercises

Author: Troels Henriksen <athas@sigkill.dk>

## Pointers

Consider the follow fragments of C programs.  For each program, fill
in the empty underlined spots such that the final value of the
variable `x` is 0.

### 1.

    int x;
    int *p;
    p = &_____;
    *p = _____;

### 2.

    int x;
    int *p;
    int **pp;
    pp = &_____;
    p = &_____;
    **pp = _____;

### 3.

    int x, y;
    int *p = &_____;
    p = _____;
    *p = 0;
    p = _____;
    *p = 1;

### 4.

    int x, y;
    int* arr[2];
    arr[0] = _____;
    arr[1] = arr[0];
    *(arr[1]) = _____;
    *(arr[0]) = *(arr[0]) - 1;

# Practical Exercises

Author: Troels Henriksen <athas@sigkill.dk>

These exercises are intended to give you more experience with C, in
particular with file I/O and simple use of pointers.

The [`solutions`](solutions/) directory contains our solutions.  It's best to look
at them only when you have tried yourself first, or are stuck.  When
you do look at them, make sure you understand why they work before
moving on.

For the practical programming tasks, you should use make to build your
programs. To parametrize make to build with all the necessary compiler
flags, start by writing down a Makefile containing the following:

```Makefile
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
```

Then when you add a program `foo`, add a rule to Makefile as follows:

```Makefile
foo: foo.c
	$(CC) -o foo foo.c $(CFLAGS)
```

Beware: the leading whitespace must be a single tab character. Now, to
compile foo, just run `make foo`. For example:

```
$ make hexabyte
```

There are ways to automate parts of this, but we recommend being
explicit until you get a firm grasp on what `make` does.

In the following, we colloquially use "print" as slang for writing to
standard output.

## A hex dumper

Write a C program `hexabyte` that prints in hexadecimal notation the
bytes contained in a file.  For example:

```
$ ./hexabyte ints.bin
01
00
00
00
01
00
00
00
02
00
00
00
03
...
```

### Hints

* Define the main function as

  ```C
  int main(int argc, char** argv) {
    ...
  }
  ```

  in order to access command-line parameters (in `argv`).

* Use `fopen(filename, "r")` to open a file for reading.

* Use the `fread()` function to actually perform the read from the
  `FILE*` object.  This function will return `0` when you have read
  the entire file.

* Use `%.2x` format specifier with `printf()` to print an integer as a
  two-digit hexadecimal number.

* Use the `assert` macro from `<assert.h>` to guard against potential
  errors.

## Converting binary integers to ASCII integers

Define a function with the following prototype:

```C
int read_int(FILE *f, int *out);
```

A call `read_int(f, &x)` must read the first four bytes from `f` and
place them in `x`.  If the read succeeds, the function must return 0,
and otherwise 1.

Then write a program `int2ascii.c` such that

```
$ ./int2ascii ints.bin
```

prints, separated by newlines, the numbers from [ints.bin](ints.bin).

### Hints

* Use the `fread()` function to actually perform the read from the
  `FILE*` object.  Remember that you need to read `sizeof(int)` bytes
  at a time (the `size` parameter accepted by `fread()`).

* The return value of `fread()` indicates how many elements were
  succesfully read (and you should read one element in `read_int()`).

## Converting ASCII integers to binary integers

Define a function with the following prototype:

```C
int read_ascii_int(FILE *f, int *out);
```

A call `read_ascii_int(f, &x)` reads an ASCII (text) integer from the
given file, and stores the final integer in `x`.  If the read
succeeds, the function must return 0, and otherwise 1.  Each integer
in the file must be followed by exactly one linebreak character
(`'\n'`), including the last one.  This is exactly the format produced
by `int2ascii`.

Then write a program `ascii2int.c` such that

```
$ ./ascii2int ints.txt ints.bin
```

prints, separated by newlines, the numbers from [ints.txt](ints.txt),
but *also* writes them as raw data to `ints.bin`, with four bytes per
integer.

#### Hints

* The `read_ascii_int()` function is a *parser*, because it translates
  unstructed text data to structured in-memory data.  Parsers are in
  general tricky to write well (and beyond the scope of our course),
  but the algorithm for reading a base-10 integer is fairly
  straightforward:

  1. We are constructing the result in the variable `x`, which is
     initially zero.

  2. Read a single character (byte) from the file.  If this fails,
     then parsing fails.

  3. If the character is a newline (`'\n'`), then parsing is done, and
     `x` is the result.

  4. If the character corresponds to a digit (see below), then convert
     it to the corresponding integer `d` in the range [0,9] and update
     `x`:

     ```
     x = x * 10 + d
     ```

     Then go to step 2.

  5. Else the character is invalid, and then parsing fails.

* To convert an ASCII character `c` corresponding to a digit, to the
  integer representing that digit, do `c - '0'`.  For example,

  ```C
  '7' - '0' == 7
  ```

* To open a file for writing, use `fopen(filename, "w")`.

* To write a raw binary integer `x` to an open file `f`, use
  `fwrite(&x, sizeof(int) 1, f)`.


# GDB exercises

Author: Michael Kirkedal Thomsen <kirkedal@acm.org>

The following exercises will to give you some experience with using GDB.

## Play with GDB

Take some of the programs from last weeks exercises or perhaps even
the assignment and play around with GDB. Recreate a bug that you had
in your program and try finding it with GDB. 

For a quick start guide to GDB, you can check out [Geeks for geeks guide on GBD](https://www.geeksforgeeks.org/gdb-step-by-step-introduction/). 

We recommend you test most of the
commands on the [GDB QUICK REFERENCE
sheet](https://sourceware.org/gdb/onlinedocs/refcard.pdf)
(which can also be found in today's exercise folder).

## Debug some programs

[Attached](exercise_code/) there is a list of programs containing some
different bugs. Some of them very obvious. Use GDB to identify and
profile the bugs. Record your approach in a GDB script.

We recommend to investigate in the following order:

* `hello.c`
* `table.c`
* `capitalize.c`
* `array.c`
