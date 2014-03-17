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

	if(linkedList->comparator == NULL){
		return -1;
	}

	// Create the new node
	NodePTR newNode;
	CreateNode(&newNode, data, NULL);
	if(newNode==NULL){
		return -1;
	}

	Comparator comparator = linkedList->comparator;

	// Get the current head
	NodePTR curNode = linkedList->head;


	if(curNode==NULL){ // If the list is empty
		linkedList->head = newNode;
		return 0;
	}

	// While the new node is less than the current node and less than the next node
		// Keep walking down
	// If the while-loop breaks => the new node is less than the current node but greater than the next node, so it belongs after the current

	// If we consider the cornercase of head first (head being less than curNode):
	// We note that by induction, the current node MUST be less than the new node, so only check the next node

	if(comparator(newNode->data, curNode->data)){ // Corner case
		newNode->next = curNode;
		linkedList->head = newNode;
		return 0;
	}

	// If there is no next node, just insert
	while(!(curNode->next==NULL) && !comparator(newNode->data, (curNode->next)->data)){
		curNode = curNode->next;
	}

	NodePTR temp = curNode->next;
	curNode->next = newNode;
	newNode->next = temp;

	return 0;
	
	if(!(linkedList->comparator)(newNode->data, curNode)){ // If the new node is greater than the head
		newNode->next = curNode;
	}
}

int PeekHead(LinkedListPTR linkedList, void **data)
{
	Node* head = linkedList->head;
	*data = head->data;
	return 0;
}

int FindNode(LinkedListPTR linkedList, NodePTR* nodeHandle, void* data)
{
	Comparator comparator = linkedList->comparator;
	NodePTR next = linkedList->head;
	while(next!=NULL){
		if(comparator(data, next->data)==0){
			*nodeHandle = next;
			return 0; // Found and assigned
		}
		next = next->next;
	}
	*nodeHandle = NULL;
	return 1; // Not found
}

int DeleteNode(LinkedListPTR linkedList, void* data)
{
	NodePTR curNode = linkedList->head;

	if(curNode==NULL){
		return 1; // Not found
	}

	Comparator comparator = linkedList->comparator;

	// If the next node is the one we are looking for, delete it and assign curNode to it's next
	
	if(comparator(data, curNode->data)==0){ // Check head
		linkedList->head = curNode->next;
		free(curNode->data); // Commented out for CSC190 purposes
		free(curNode);
		linkedList->size = linkedList->size - 1;
		return 0;
	}

	while(!(curNode->next==NULL)){
		if(comparator(data, curNode->next->data)==0){
			NodePTR temp = curNode->next->next;
			free(curNode->next->data); // Commented out for CSC190 Purposes
			free(curNode->next);
			curNode->next = temp;
			linkedList->size = linkedList->size - 1;
			return 0;
		}
		curNode = curNode->next;
	}
	return 1; // Not found
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

	if(*one==*two){
		return 0;
	}

	return -1;
}
