# Exercises
## Compile a C-program

These exercises are intended to give you a first quick feeling of
C. Use the exercise classes to get help.  This is not part of the
mandatory assignments.  Even if you do not manage to solve the
exercises during the classes, they may still be worth working on in
your own time, as they are designed to prepare you for the mandatory
assignments and the exam.

For all of the below, you should use `make` to build your programs. To
parametrize `make` to build with all the necessary compiler flags, start by
writing down a `Makefile` containing the following:

```
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -pedantic -g
```

Then when you add a program `foo`, add a rule to `Makefile` as
follows:

```
foo: foo.c
	$(CC) -o foo foo.c $(CFLAGS)
```

**Beware**: the leading whitespace *must* be a single tab character.
Now, to compile `foo`, just run `make foo`. For example:

```
$ make mynameis
```

There are ways to automate parts of this, but we recommend being
explicit until you get a firm grasp on what `make` does.

## Run a C-program
To run the *compiled* program write: 
```
$ ./mynameis
```

# Write C-programs
In the following, we colloquially use "print" as slang for writing to
standard output.

## Printing in C

Write a C program `mynameis` that prints your name.

## Input arguments in C

Write a C program `repeatme` that given a string as argument, prints
the string twice on separate lines.

If the program gets a number of arguments that is different from 1 it
should print "`Wrong number of arguments`".

## Input argument validation

Write a C program `noAs` that given a string as argument, does either
of the following.

  * If the first character of the string is the `char` `A` it
    prints "`No beginning A's are allowed`",

  * otherwise it prints the given string.

Hint: strings are arrays in C.

Note: reuse your argument validation from before. You can just as well
learn it from the beginning. _Always sanitise your input._

## Multiple input formats

Modify the `roll` program developed at lecture to support `dN` as
alternative notation for `1dN`.  Hint: if one `sscanf()` fails, try
another.

* `dN` is diceNumber. d6 means a six-sided dice and d12 means a 12-sided dice. 
* `1dN` is 1 die with N-sides. 
## Guessing game

Write a C program that on startup generates a random number with
`rand()`, and then asks the user to guess it, answering either "too
low" or "too high" when the user guesses wrong.  Take care to handle
non-numeric user input in a sensible way.  _Always sanitise your
input._

## Integer representation

Play with integer representation. Try to get `0xA` correct on the different "levels".

http://topps.diku.dk/compsys/integers.html

Next, answer all of the following:

* http://topps.diku.dk/compsys/integers.html#NjdfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#NjFfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#MTAzX2ZhbHNlXzFfMl8x
* http://topps.diku.dk/compsys/integers.html#OTBfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#MjU1X2ZhbHNlXzFfMF8y
* http://topps.diku.dk/compsys/integers.html#MTUzX2ZhbHNlXzFfMF8y
* http://topps.diku.dk/compsys/integers.html#MjE5X2ZhbHNlXzFfMF8x
* http://topps.diku.dk/compsys/integers.html#OTBfZmFsc2VfMV8wXzE=
