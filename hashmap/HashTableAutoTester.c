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

	fprintf(stderr, "Destroying HashTable\n");
	DestroyHashTable(&mHashTable);

	return 0;
}
