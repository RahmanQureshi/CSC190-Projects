#include "linkedlist.h"

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

	int* head;

	fprintf(stderr, "Peeking the head: [%d]\n", PeekHead(mLinkedList, (void**)&head));

	fprintf(stderr, "Saw: [%d]\n", *head);

	fprintf(stderr, "Printing: ");
	PrintLinkedList(mLinkedList);

	NodePTR mNode;
	fprintf(stderr, "Finding node with number %d: [%d]\n", *one, FindNode(mLinkedList, &mNode, (void*)one));
	fprintf(stderr, "Checking node data; has %d\n", *((int*)(mNode->data)));

	fprintf(stderr, "Deleting node with number %d: [%d]\n", *one, DeleteNode(mLinkedList, (void*)zero));

	fprintf(stderr, "Printing: ");
	PrintLinkedList(mLinkedList);

	void *data;
	fprintf(stderr, "Popping head: [%d]\n", pop(mLinkedList, &data));
	fprintf(stderr, "Received: %d\n", *((int*)data));
	free(data);

	fprintf(stderr, "Printing: ");
	PrintLinkedList(mLinkedList);

	fprintf(stderr, "Destroying nodes and data: [%d]\n", DestroyNodesAndDataLinkedList(mLinkedList));

	fprintf(stderr, "Destroy linked list: [%d]\n", DestroyLinkedList(&mLinkedList));

	return 0;
}

