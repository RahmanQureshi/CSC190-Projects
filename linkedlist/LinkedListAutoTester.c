#include "LinkedList.h"

int main()
{

	LinkedListPTR mLinkedList;

	fprintf(stderr, "Creating LinkedList: [%d]\n", CreateLinkedList(&mLinkedList));

	int* zero = (int*) malloc(sizeof(int)); *zero = 100;
	int* one = (int*) malloc(sizeof(int)); *one = 200;
	int* two = (int*) malloc(sizeof(int)); *two = 300;

	fprintf(stderr, "Inserting into list: [%d]\n", InsertSortedLinkedList(mLinkedList, (void*)zero));

	fprintf(stderr, "Inserting into list: [%d]\n", InsertSortedLinkedList(mLinkedList, (void*)one));

	fprintf(stderr, "Inserting into list: [%d]\n", InsertSortedLinkedList(mLinkedList, (void*)two));


	int i = 100;
	fprintf(stderr, "Deleting node with number %d: [%d]\n", i, DeleteNode(mLinkedList, (void*)&i));
	// ERROR WAS HERE: FIRST DELETED NODE, THEN TRIED TO READ AND DISPLAY! URGH. 

	fprintf(stderr, "Printing: ");
	PrintLinkedList(mLinkedList);

	fprintf(stderr, "Destroying nodes and data: [%d]\n", DestroyNodesAndDataLinkedList(mLinkedList));

	fprintf(stderr, "Destroy linked list: [%d]\n", DestroyLinkedList(&mLinkedList));

	return 0;
}

