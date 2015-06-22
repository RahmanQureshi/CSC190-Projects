CC = gcc
CFLAGS = -c -g -std=c99 -Wall -Werror -Wconversion -pedantic
LFLAGS = -g -std=c99 -Wall -Werror -Wconversion -pedantic
EXECUTABLE = hashTableTester
SRC = hashtable.c ../binarysearchtree/tree.c HashTableAutoTester.c
OBJ = $(SRC:.c=.o)
DEPS = hashtable.h ../binarysearchtree/tree.h

all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJ)
	$(CC) $(LFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf ../binarysearchtree/*.o
	rm -rf *.o
