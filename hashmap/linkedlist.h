#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node Node;

typedef Node *NodePTR;

typedef int (*Comparator)(void* dataOne, void* dataTwo);

struct node {
	void* data;
	NodePTR next;
};

typedef struct {
	Comparator comparator;
	NodePTR head;
	unsigned int size;
} LinkedList;

typedef LinkedList *LinkedListPTR;

int CreateLinkedList(LinkedListPTR *linkedListHandle);

// Clean the nodes and set size = 0
int DestroyNodesLinkedList(LinkedListPTR linkedList);

// Clean the nodes and data and set size = 0
int DestroyNodesAndDataLinkedList(LinkedListPTR linkedList);


// Clean up the linked list (frees and sets to null)
int DestroyLinkedList(LinkedListPTR *linkedListHandle);

int CreateNode(NodePTR* nodeHandle, void* data, NodePTR next);

// Comparator returns true while dataOne is greater than dataTwo. Note: the null case MUST be implemented by comparator as well.
// The linked list will store elements with the greatest at the head
int SetComparatorLinkedList(LinkedListPTR linkedList, Comparator comparator);

// For CSC190 purposes, the default comparator assumes data members are integers
// Return TRUE if dataOne is greater than dataTwo
int DefaultComparator(void* dataOne, void* dataTwo);

// Appends to the end of the linked list
int AppendLinkedList(LinkedListPTR linkedList, void *data);

// Inserts the linked list in a sorted order according to the comparator
int InsertSortedLinkedList(LinkedListPTR linkedList, void* data);

// Stores the front of the linked list in data without removing it
int PeekHead(LinkedListPTR linkedList, void **data);

void PrintLinkedList(LinkedListPTR linkedList);

