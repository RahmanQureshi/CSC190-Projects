CC = gcc
CFLAGS = -c -g -std=c99 -Wall -Werror -Wconversion -pedantic
LFLAGS = -g -std=c99 -Wall -Werror -Wconversion -pedantic
EXECUTABLE = hashTableTester
SRC = hashtable.c LinkedList.c HashTableAutoTester.c
OBJ = $(SRC:.c=.o)
HEADS = hashtable.h LinkedList.h

all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@

hashtable.o: hashtable.c
	$(CC) $(CFLAGS) $^ -o $@

LinkedList.o: LinkedList.c
	$(CC) $(CFLAGS) $^ -o $@

HashTableAutoTester.o: HashTableAutoTester.c
	$(CC) $(CFLAGS) $^ -o $@

LinkedList.c: LinkedList.h

hashtable.c: hashtable.h

HashTableAutoTester.c: HashTableAutoTester.o

clean:
	rm -rf *.o