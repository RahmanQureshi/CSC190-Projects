#include "hashtable.h"

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

	int* mPrevData;
	int* mData = malloc(sizeof(int)); *mData = 25;
	char* mKey = "hello";

	fprintf(stderr, "Inserting data [%d]\n", *mData);
	InsertEntry(mHashTable, mKey, (void*)mData, (void**)&mPrevData);

	fprintf(stderr, "Destroying HashTable\n");
	DestroyHashTable(&mHashTable);

	return 0;
}
