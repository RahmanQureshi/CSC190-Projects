#include "LinkedList.h"

int CreateLinkedList(LinkedListPTR *linkedListHandle)
{
	// Create the Linked List
	LinkedListPTR mLinkedList = (LinkedListPTR) malloc(sizeof(LinkedList));

	if(mLinkedList == NULL){
		printf("Memory for LinkedList could not be allocated\n");
		return FATAL_ERROR;
	}

	mLinkedList->head = NULL;
	mLinkedList->size = 0;

	SetComparatorLinkedList(mLinkedList, DefaultComparator);

	*linkedListHandle = mLinkedList;

	return OK;
}

int DestroyLinkedList(LinkedListPTR *linkedListHandle)
{
	if(linkedListHandle==NULL || *linkedListHandle==NULL){
		printf("LinkedList pointer is NULL\n");
		return ERROR;
	}

	LinkedListPTR linkedList = *linkedListHandle;

	free(linkedList);

	linkedList = NULL;

	return OK;
}

int DestroyNodesLinkedList(LinkedListPTR linkedList)
{
	if(linkedList==NULL){
		printf("LinkedList pointer is NULL\n");
		return ERROR;
	}

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

	return OK;
}


int DestroyNodesAndDataLinkedList(LinkedListPTR linkedList)
{
	if(linkedList==NULL){
		printf("LinkedList pointer is NULL\n");
		return ERROR;
	}

	unsigned int size = linkedList->size;
	int i;
	NodePTR next = linkedList->head;

	for(i=0; i<size; i++){
		NodePTR temp = next->next;
		if(next->data==NULL){
			printf("Node data set to null - modified outside of linked list\n");
		}else{
			free(next->data);
		}
		next->data = NULL;
		free(next);
		next= NULL;
		next = temp;
	}

	linkedList->size = 0;

	return OK;
}

int AppendLinkedList(LinkedListPTR linkedList, void *data)
{
	if(linkedList==NULL){
		printf("LinkedList pointer is NULL\n");
		return ERROR;
	}

	// Initialize new object. It will become the next head
	NodePTR newNode;
	NodePTR curHead = linkedList->head;
	CreateNode(&newNode, data, curHead);

	if(newNode==NULL){
		printf("Could not allocate memory for node\n");
		return FATAL_ERROR;
	}

	linkedList->head = newNode;

	linkedList->size = linkedList->size + 1; // Everything OK, increase

	return OK;
}

int InsertSortedLinkedList(LinkedListPTR linkedList, void* data)
{

	if(linkedList->comparator == NULL){
		printf("Comparator is not set\n");
		return ERROR;
	}

	// Create the new node
	NodePTR newNode;
	CreateNode(&newNode, data, NULL);
	if(newNode==NULL){
		printf("Could not allocate memory for new node\n");
		return FATAL_ERROR;
	}

	Comparator comparator = linkedList->comparator;

	// Get the current head
	NodePTR curNode = linkedList->head;

	linkedList->size = linkedList->size + 1;

	if(curNode==NULL){ // If the list is empty
		linkedList->head = newNode;
		return OK;
	}

	// While the new node is less than the current node and less than the next node
		// Keep walking down
	// If we consider the cornercase of head first (head being less than curNode):
	// We note that by induction, the current node MUST be less than the new node, so only check the next node
	// If the while-loop breaks => the new node is less than the current node but greater than the next node, so it belongs after the current


	if(comparator(newNode->data, curNode->data)==1){ // Corner case - first node
		newNode->next = curNode;
		linkedList->head = newNode;
		return OK;
	}

	// If there is no next node, just insert
	while(!(curNode->next==NULL) && comparator(newNode->data, (curNode->next)->data)==-1){
		curNode = curNode->next;
	}

	NodePTR temp = curNode->next;
	curNode->next = newNode;
	newNode->next = temp;

	return OK;
}

int PeekHead(LinkedListPTR linkedList, void **data)
{
	if(linkedList==NULL){
		printf("LinkedList pointer is NULL\n");
		return ERROR;
	}
	Node* head = linkedList->head;
	*data = head->data;
	return OK;
}

int FindNode(LinkedListPTR linkedList, NodePTR* nodeHandle, void* data)
{
	if(linkedList==NULL){
		printf("LinkedList pointer is NULL\n");
		return ERROR;	
	}

	Comparator comparator = linkedList->comparator;
	NodePTR next = linkedList->head;
	while(next!=NULL){
		if(comparator(data, next->data)==0){
			*nodeHandle = next;
			return FOUND; // Found and assigned
		}
		next = next->next;
	}
	*nodeHandle = NULL;
	return NOT_FOUND; // Not found
}

int DeleteNode(LinkedListPTR linkedList, void* data)
{
	if(linkedList==NULL){
		printf("LinkedList pointer is NULL\n");
		return ERROR;	
	}

	NodePTR curNode = linkedList->head;

	if(curNode==NULL){ // If the list is empty
		return NOT_FOUND; // Not found
	}

	Comparator comparator = linkedList->comparator;

	// If the next node is the one we are looking for, delete it and assign curNode to it's next
	
	if(comparator(data, curNode->data)==0){ // Check head
		linkedList->head = curNode->next;
		if(curNode->data==NULL){
			printf("Node data set to null - modified outside of linked list\n");
		}else{
			free(curNode->data);
		}
		free(curNode);
		linkedList->size = linkedList->size - 1;
		return FOUND;
	}

	while(!(curNode->next==NULL)){
		if(comparator(data, curNode->next->data)==0){
			NodePTR temp = curNode->next->next;
			if(curNode->next->data==NULL){
				printf("Node data set to null - modified outside of linked list\n");
			}else{
				free(curNode->next->data);
			}
			free(curNode->next);
			curNode->next = temp;
			linkedList->size = linkedList->size - 1;
			return FOUND;
		}
		curNode = curNode->next;
	}
	return NOT_FOUND; // Not found
}

int PrintLinkedList(LinkedListPTR linkedList)
{
	if(linkedList == NULL){
		printf("LinkedList pointer is NULL\n");
		return ERROR;
	}else if(linkedList->head == NULL){
		printf("List is Empty\n");
		return EMPTY_LIST;
	}

	NodePTR next = linkedList->head;
	while(next!=NULL){
		int* data = (int*) (next->data);
		printf("%d ", *data);
		next = next->next;
	}
	printf("\n");
	return OK;
}

int SetComparatorLinkedList(LinkedListPTR linkedList, Comparator comparator)
{
	if(comparator==NULL){
		printf("Function pointer to comparator is NULL");
		return ERROR;
	}
	linkedList->comparator = comparator;
	return OK;
}

int CreateNode(NodePTR* nodeHandle, void* data, NodePTR next)
{
	NodePTR new = (NodePTR) malloc(sizeof(Node));
	if(new==NULL) return FATAL_ERROR;
	new->data = data;
	new->next = next;
	*nodeHandle = new;
	return OK;
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
