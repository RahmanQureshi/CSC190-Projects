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

	SetComparatorLinkedList(mLinkedList, DefaultComparator);

	*linkedListHandle = mLinkedList;

	return 0;
}

int DestroyLinkedList(LinkedListPTR *linkedListHandle)
{
	if(linkedListHandle==NULL || *linkedListHandle==NULL) return -1;

	LinkedListPTR linkedList = *linkedListHandle;

	free(linkedList);

	linkedList = NULL;

	return 0;
}

int DestroyNodesLinkedList(LinkedListPTR linkedList)
{
	if(linkedList==NULL) return -1;

	unsigned int size = linkedList->size;
	int i;
	NodePTR next = linkedList->head;

	for(i=0; i<size; i++){
		NodePTR temp = next->next;
		free(next);
		next = NULL;
		next = temp;
	}

	linkedList->size = 0;

	return 0;
}


int DestroyNodesAndDataLinkedList(LinkedListPTR linkedList)
{
	if(linkedList==NULL) return -1;

	unsigned int size = linkedList->size;
	int i;
	NodePTR next = linkedList->head;

	for(i=0; i<size; i++){
		NodePTR temp = next->next;
		free(next->data);
		next->data = NULL;
		free(next);
		next= NULL;
		next = temp;
	}

	linkedList->size = 0;

	return 0;
}

int AppendLinkedList(LinkedListPTR linkedList, void *data)
{
	NodePTR curHead = linkedList->head;

	// Initialize new object. It will become the next head
	NodePTR newNode;
	CreateNode(&newNode, data, curHead);

	linkedList->head = newNode;



	linkedList->size = linkedList->size + 1;

	return 0;
}

int InsertSortedLinkedList(LinkedListPTR linkedList, void* data)
{

	linkedList->size = linkedList->size + 1;

	// List order: greatest to least
	if(linkedList->comparator == NULL){
		return -1;
	}

	// Create the new node
	NodePTR newNode;
	CreateNode(&newNode, data, NULL);
	Comparator comparator = linkedList->comparator;

	// Get the current head
	NodePTR curNode = linkedList->head;

	if(curNode==NULL){ // If the list is empty
		linkedList->head = newNode;
		return 0;
	}

	if(comparator(newNode, curNode)){
		newNode->next = curNode;
		linkedList->head = newNode;
		return 0;
	}

	// While the new node is less than the current node and less than the next node
		// Keep walking down
	// If the while-loop breaks => the new node is less than the current node but greater than the next node, so it belongs after the current

	// We note that by induction, the current node MUST be less than the new node, so only check the next node

	while(!comparator(newNode, curNode->next)){
		curNode = curNode->next; // GOD DAMN... THIS IS RE-USING INFORMATION NAMELY THAT CURNODE IS ALREADY LESS. 
	}

	NodePTR temp = curNode->next;
	curNode->next = newNode;
	newNode->next = temp;

	return 0;
	
	if(!(linkedList->comparator)(newNode->data, curNode)){ // If the new node is greater than the head
		newNode->next = curNode;
	}
}


int SetComparatorLinkedList(LinkedListPTR linkedList, Comparator comparator)
{
	if(comparator==NULL) return -1;
	linkedList->comparator = comparator;
	return 0;
}

int CreateNode(NodePTR* nodeHandle, void* data, NodePTR next)
{
	NodePTR new = (NodePTR) malloc(sizeof(Node));
	if(new==NULL) return -1;
	new->data = data;
	new->next = next;
	*nodeHandle = new;
	return 0;
}

int DefaultComparator(void* dataOne, void* dataTwo)
{
	int* one = (int*) dataOne;
	int* two = (int*) dataTwo;

	if(two==NULL || *one>*two){
		return 1;
	}
	return 0;
}

int PeekHead(LinkedListPTR linkedList, void **data)
{
	Node* head = linkedList->head;
	*data = head->data;
	return 0;
}

void PrintLinkedList(LinkedListPTR linkedList)
{
	NodePTR next = linkedList->head;
	while(next!=NULL){
		int* data = (int*) (next->data);
		printf("%d ", *data);
		next = next->next;
	}
	printf("\n");
}
