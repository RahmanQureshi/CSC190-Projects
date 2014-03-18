#include "hashtable.h"
//#include "linkedlist.h"

#define OK 0
#define FATAL_ERROR -1
#define UNEXPECTED_ERROR -2
#define INITIAL_SIZE 1

//TODO: MAKE TWO TESTERS AND/OR USE COMMANDLINE ARGUMENTS WITH A .SH FILE TO SWITCH BETWEEN TESTERS

int main()
{
	// Hashmap Test

	HashTablePTR mHashTable = NULL;
	fprintf(stderr, "Creating HashTable\n");
	CreateHashTable(&mHashTable, INITIAL_SIZE);

	fprintf(stderr, "Checking sentinal\n");

	if(checkSentinel(mHashTable, (int)0xDEADBEEF)){
		fprintf(stderr, "Sentinel good\n");
	}else{
		fprintf(stderr, "Setinel bad\n");
	}

	fprintf(stderr, "Inserting data\n");
	char* key = "mKey"; 
	int* data = malloc(sizeof(int));
	*data = 5;
	void* prevData;
	InsertEntry(mHashTable, key, data, &prevData);

	fprintf(stderr, "Destroying HashTable\n");
	DestroyHashTable(&mHashTable);

	// LinkedList Test
	/*
	LinkedListPTR linkedList = NULL;
	
	fprintf(stderr, "Creating LinkedList\n");
	CreateLinkedList(&linkedList);

	fprintf(stderr, "Inserting 5 into LinkedList\n");
	int mNum = 5;
	insertEntryLinkedList(linkedList, &mNum);

	fprintf(stderr, "Retrieving head of LinkedList\n");
	
	void* p;
	peekHead(linkedList, &p);
	fprintf(stderr, "Received: %d\n", *((int*)(p)));

	fprintf(stderr, "Destroying LinkedList\n");
	DestroyLinkedList(&linkedList);
	*/

	return 0;
}
