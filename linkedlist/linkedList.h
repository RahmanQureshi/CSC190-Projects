#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FATAL_ERROR -1
#define ERROR 1
#define OK 0
#define NOT_FOUND 2
#define FOUND 3
#define EMPTY_LIST 4

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


// Clean up the linked list struct (not its members) (frees and sets to null)
int DestroyLinkedList(LinkedListPTR *linkedListHandle);

int CreateNode(NodePTR* nodeHandle, void* data, NodePTR next);

// Appends to the front of the linked list
int AppendLinkedList(LinkedListPTR linkedList, void *data);

// Inserts the linked list in a sorted order according to the comparator. Inserts in order of greatest to least
// This function assumes that the nodes are already in order
int InsertSortedLinkedList(LinkedListPTR linkedList, void* data);

// Stores the front of the linked list in data without removing it
int PeekHead(LinkedListPTR linkedList, void **data);

// CSC190 Purposes
// Assigns node to the node in the linkedlist with data 'data' and NULL otherwise
int FindNode(LinkedListPTR linkedList, NodePTR* nodeHandle, void* data);

// CSC190 Purposes
// Assigns *nodeHandle the address of the node that is equal to 'data' and null otherwise
int DeleteNode(LinkedListPTR linkedList, void* data);

// Note: assumes that data is integers
// TODO: Generalize
int PrintLinkedList(LinkedListPTR linkedList);

// Returns 1 if dataOne is greater than dataTwo or dataTwo is null
// Returns 0 if dataOne is equal to dataTwo
// Returns -1 if dataOne is less than dataTwo
int SetComparatorLinkedList(LinkedListPTR linkedList, Comparator comparator);

// For CSC190 purposes, the default comparator assumes data members are integers
int DefaultComparator(void* dataOne, void* dataTwo);
