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

int insertEntryLinkedList(LinkedListPTR linkedList, void *data)
{
	Object* curHead = linkedList->head;

	// Initialize new object. It will become the next head
	Object* newObj = (Object*) malloc(sizeof(Object));
	newObj->data = data;
	newObj->previous = NULL;
	newObj->next = curHead;

	linkedList->head = newObj;

	linkedList->size = linkedList->size + 1;

	return 0;
}

int peekHead(LinkedListPTR linkedList, void **data)
{
	Object* head = linkedList->head;
	*data = head->data;
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

	free(linkedList);

	return 0;
}
