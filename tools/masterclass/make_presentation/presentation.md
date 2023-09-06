# Make
Make makes it easy to run commands with keywords.
ie. ```make hello```, is far easier to remember and write quickly, compared to ``` gcc -Wall -o hello hello.c```.

Make will be able to register changes in source files, and recompile if needed. (you still have to execute ```make hello```)

```rm hello``` to remove the executable file.


## Basic
<span style="color:red;">EXECISE:</span>
Make a simple cmd.

<span style="color:red;">REALLY IMPORTANT THAT YOU INDENT, OTHERWISE YOU GET ERROR: ```Makefile:2: *** missing separator.  Stop.```</span>


```
hello: hello.c
    gcc -Wall -o hello hello.c
```
## Variables
<span style="color:red;">EXECISE:</span>
Abstract variables such as compiler, and flags.

```
CC = gcc
CFLAGS = -Wall

hello: hello.c
    $(CC) $(CFLAGS) -o hello hello.c
```
## Dependencies

<span style="color:red;">EXECISE:</span>
Add some library dependency, that you want to compile with your hello.c.

```
CC = gcc
CFLAGS = -Wall
SRC = hello.c utils.c

hello: $(SRC)
	$(CC) $(CFLAGS) -o hello $(SRC)
```
## Cleanup/recompiling


<span style="color:red;">EXECISE:</span> 
Make a clean cmd, that removes files. ie. if some files are corrupted, or make cannot register changes in source files.


```
# executes clean cmd no matter what 
.PHONY: clean

CC = gcc
CFLAGS = -Wall
SRC = hello.c utils.c

hello: $(SRC)
	$(CC) $(CFLAGS) -o hello $(SRC)


clean:
	rm -f hello *.o
```
## Make valgrind for hello

<span style="color:red;">EXECISE:</span> make valgrind for this cmd ```valgrind --tool=memcheck --leak-check=yes ./hello``. Furthermore, make it easy to change valgrind flags and executable name (currently hello).

leaks (macos) memory 
valgrind 

```
# executes clean cmd no matter what 
.PHONY: clean

CC = gcc
CFLAGS = -Wall
SRC = hello.c utils.c
EXEC = hello
VFLAGS = --tool=memcheck --leak-check=yes 


hello: $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

valgrind: $(SRC)
	valgrind $(VFLAGS) ./$(EXEC)

clean:
	rm -f $(EXEC) *.o

```


## Some (but not all) possible Warning flags:
- -std=c11: Specify C language standard. ()
- -g3: Generate debugging information.
- -Wall: Enable most warning messages.
- -Wextra: Enable additional warning messages.
- -Werror: Treat warnings as errors. (your program will not compile until you fix all warnings)
- -pedantic: Catches more possible errors (by warning you about them).

<span style="color:red;">EXECISE:</span> Add some of these and try to make the compiler trigger them. (unused variables?)

# vscode extensions
- Go to extensions on the left (Ctrl+Shift+X)
- Get the C -extensions by microsoft is a good starting point
- PDF viewer
- Markdown previewer (Ctrl+Shift+V)

# godbolt
Example: 
<https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AB9U8lJL6yAngGVG6AMKpaAVxYMQkrlwAcpBwAZPAZMADl3ACNMYhAAdlIAB1QFQlsGZzcPLx9/ZNSbAWDQiJZo2ITLTGt0oQImYgJM909vPwtMK0KGOoaCYvComPiLesbm7Lb/BTH%2BkMGy4biASgtUV2Jkdg4AegAqAGoAFQBPRMwDk/XiA7QsA4QYzFIDkgPaVCZ0A8MDzFVWIl6AA6A57HYAUg0AEEIQAmADMIWQbnuEIRjhm%2BFQwIQ6OwUNhMMJIQIBwUAEdXA1MBBSQcGO5lgcIXEAEKEg5cg47Hb0xksOEshEAEQOcPRHJh3NuCAahxmN3RYvhcIA7hrNVrtTrdXr9QbDUbjSbTWbzRbLVbrTbbXb7Q7HU7nS7XW73R7PV7vT7fX7/QHA0HgyHQ2HwxHI1HozHY3H4wnE0nkynU2n0xnM1nsznc3n8wXC0XiyXS2XyxXK1XqzXa3X6w3tarJZzuYliKSqBBm3CAKwKVWjYjLFvS7nETAEDYMBnuMGzlij2FxEWEjirWicXu8TwcLSkVCcRzk65bFmInikAiaderADWIARCOBT9fb/fADZ9JxJDubwfOF4BQQA0K8b1WOBYCQNAWESOgYnISgYLg%2BhYmIAA3BE4QAWmQYBkGQLg4S4UCsHQvAtgANTwTA1QAeXOXdLxoWgCBiYCIEif9IhCBoTk4S8eOYYgTjoyJtGqa9uF4GC2EEOiGFofi914LBIlcYBHDEWhgOk0gsBYQxgHEFT9LwCcanQzBdP3f5qlcNiBN4UlOn/Wg8EiYg%2BOcLB/wIDsWCc1YqAMYAFGo2iGMYJyZEEEQxHYKRYvkJQ1H/XQuH0IyQFMYxzHcyJgMgVZUESbpdOwrFlUIrgDmwgB1bS6vq/5/KYOrznQQwbGQOrgAROqqAYVBsNQFhCGwqgvLYbDkhc4heFQKziA7LAiogVYqhqOwIAcCZPC4ABOAIGHQAZSnKEBDrhJIUjSAR9okY78nuhhzqGWJro6LpalmR6ju%2ByTfr6d7Fk%2Bm6Zj6f7jshxpQcu67NtPRKNy3P9TMPDgDgAJQASSERxsMog4ICw7CeIIBRmXw3qiOBLhgQ0EncEIN54QRLhll4KStGWe9HziF932Fp9vw4X9SF3fdMaAkCwJUiCYEQEB1gIRIHMQiBkPg4gwlYbZVF8D9sI/SQDhpg4uGfOFeEwfAiFWvR%2BDi0RxCS52UpUdRTIy0g1S8xIgrF7dJf/TG6Ic9WyVQKgcfxwnidJnCKap82CMtuF6cZknnFgnXzw5rn5d5/m4UOoWRbfPsxYlqXFsAiw5Z528xZt0OMYb5u%2BdIZbUjsSQgA%3D>

# Risc-V
To compile to exec risc-v, with the library provided.
~~~
riscv32-unknown-elf-gcc -march=rv32im -mabi=ilp32 -O1 hello.c lib.c -static -nostartfiles -nostdlib -o test.riscv
~~~

Readable risc-v code.
~~~
riscv32-unknown-elf-objdump -s -w test.riscv > test.dis
riscv32-unknown-elf-objdump -S test.riscv >> test.dis
~~~

https://github.com/TheThirdOne/rars/releases/tag/continuous
