#include "linkedlist.h"

int main()
{
	LinkedListPTR mLinkedList;

	fprintf(stderr, "Creating LinkedList: [%d]\n", CreateLinkedList(&mLinkedList));

	int* zero = (int*) malloc(sizeof(int)); *zero = 100;
	//int* one = (int*) malloc(sizeof(int)); *one = 200;
	//int* two = (int*) malloc(sizeof(int)); *two = 150;

	fprintf(stderr, "Inserting into list: [%d]\n", InsertSortedLinkedList(mLinkedList, (void*)zero));

	fprintf(stderr, "Destroying nodes and data: [%d]\n", DestroyNodesAndDataLinkedList(mLinkedList));

	fprintf(stderr, "Destroy linked list: [%d]\n", DestroyLinkedList(&mLinkedList));

	return 0;
}

