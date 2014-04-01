CC = gcc
EXECUTABLE = treeTester
SRC = tree.c treeTester.c
OBJ = $(SRC:.c=.o)
DEPS = tree.h
CFLAGS = -std=c99 -g -c -Wall -Werror -Wconversion -pedantic
LFLAGS = -std=c99 -g -Wall -Werror -Wconversion -pedantic


all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJ)
	$(CC) $(LFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
