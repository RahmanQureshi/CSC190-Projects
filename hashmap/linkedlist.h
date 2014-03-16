#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Object Object;

struct Object {
	void* data;
	Object *next;
	Object *previous;
};

typedef struct {
	Object *head;
	unsigned int size;
} LinkedList;

typedef LinkedList *LinkedListPTR;

int CreateLinkedList(LinkedListPTR *linkedListHandle);

int DestroyLinkedList(LinkedListPTR *linkedListHandle);

int insertEntryLinkedList(LinkedListPTR linkedList, void *data);

// Stores the front of the linked list in data without removing it
int peekHead(LinkedListPTR linkedList, void **data);
