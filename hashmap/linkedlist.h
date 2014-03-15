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

int insertLinkedList(LinkedListPTR linkedList, void *data);
