#include "linkedlist.h"

int CreateLinkedList(LinkedListPTR *linkedListHandle)
{
	// Create the Linked List
	LinkedListPTR mLinkedList = (LinkedListPTR) malloc(sizeof(LinkedList));

	if(mLinkedList == NULL){
		return -1;
	}

	mLinkedList->head = NULL;
	mLinkedList->size = 0;

	*linkedListHandle = mLinkedList;

	return 0;
}

int insertLinkedList(LinkedListPTR linkedList, void *data)
{
	return 0;
}

int DestroyLinkedList(LinkedListPTR *linkedListHandle)
{
	LinkedListPTR linkedList = *linkedListHandle;
	unsigned int size = linkedList->size;

	int i;
	Object *next = linkedList->head;
	for(i=0; i<size; i++){
		Object* temp = next->next;
		free(next);
		next = temp;
	}

	return 0;
}
