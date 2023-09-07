
# hello: hello.c
# 	gcc -Wall -o hello hello.c



# CC = gcc
# CFLAGS = -Wall

# hello: hello.c
# 	$(CC) $(CFLAGS) -o hello hello.c



# CC = gcc
# CFLAGS = -Wall
# SRC = hello.c utils.c

# hello: $(SRC)
# 	$(CC) $(CFLAGS) -o hello $(SRC)



# executes clean cmd no matter what 
# .PHONY: clean

# CC = gcc
# CFLAGS = -Wall
# SRC = hello.c utils.c

# hello: $(SRC)
# 	$(CC) $(CFLAGS) -o hello $(SRC)


# clean:
# 	rm -f hello *.o



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