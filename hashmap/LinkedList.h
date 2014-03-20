/*
* LinkedList
* Author: Abdur-Rahman Ayyaz Qureshi
* Implementation Notes:
* 1. This linkedlist takes control and responsibility for freeing the data and setting the pointers equal to null.
* 2. This linkedlist 'assumes' that the data is integers when printing and comparing nodes. Use SetComparatorLinkedList and SetPrinterLinkedList respectively to
* override this behaviour.
* 3. The linkedlist InsertSortedLinkedList method assumes the list is already sorted. It will order the nodes from greatest to lowest according to the comparator.
* 
* Notes on 1:
* The DeleteNode method's implementation will always attempt to delete the internal data as well. So if you are using the actual data to find the node, do not free it!
* When destroying the linked list, there is a method that will only delete the nodes, but only use it if you have a reference to the nodes, otherwise
* there will be information leaks. It was never really meant to be used. It is a relic of CSC190.
* Destroying the nodes (and data) and actual linked list is separated because you may want to clear the list without destroy the actual list.
* 
*/ 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Modified because these clashed with Vector (used in hashmap)
// Todo: this does not seem elegant at all...

#ifndef FATAL_ERROR
	#define FATAL_ERROR -1
#endif

#ifndef ERROR
	#define ERROR 1
#endif

#ifndef OK
	#define OK 0
#endif

#define NOT_FOUND 2
#define FOUND 3
#define EMPTY_LIST 4

typedef struct node Node;

typedef Node *NodePTR;

typedef int (*ComparatorLinkedList)(void* dataOne, void* dataTwo);

typedef void (*PrinterLinkedList)(void* data);

struct node {
	void* data;
	NodePTR next;
};

typedef struct {
	PrinterLinkedList printer;
	ComparatorLinkedList comparator;
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

// Removes the front of the linked list and assigns it to *dataHandle
int pop(LinkedListPTR linkedList, void **dataHandle);

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
int SetComparatorLinkedList(LinkedListPTR linkedList, ComparatorLinkedList comparator);

// Printer prints the data element passed to it anyway required
// Note that spacing between elements will be appended by PrintLinkedList, so printing spaces in the printer function just adds more padding
// If you want it on separate lines, just use \n in printer
int SetPrinterLinkedList(LinkedListPTR linkedList, PrinterLinkedList printer);

// For CSC190 purposes, the default comparator assumes data members are integers
int DefaultComparatorLinkedList(void* dataOne, void* dataTwo);

void DefaultPrinterLinkedList(void* data);
