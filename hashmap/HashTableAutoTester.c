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

	char* keyArray[11] = {"a","b","c","d","e","f","g","h","i","j","a"};
	int dataArray[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	int i;
	for(i=0; i<11; i++){
		char* key = keyArray[i];
		int data = dataArray[i];
		void* previousData;
		fprintf(stderr, "Inserting entry: [%d]\n", InsertEntry(mHashTable, key, (void**)&data, &previousData) );
		if(!(previousData==NULL)){
			fprintf(stderr, "Previous data: %d\n", *((int*)previousData));
			previousData = NULL;
		}
	}

	char **hashKeysArray;
	unsigned int keyCount;
	fprintf(stderr, "Retrieving keys: [%d]\n", GetKeys(mHashTable, &hashKeysArray, &keyCount));
	fprintf(stderr, "Number of keys: %d\n", keyCount);
	fprintf(stderr, "Keys: ");
	for(i=0; i<keyCount; i++){
		fprintf(stderr, "%s", *(hashKeysArray+i));
		free(*(hashKeysArray+i));
	}
	free(hashKeysArray);

	fprintf(stderr, "Destroying HashTable\n");
	DestroyHashTable(&mHashTable);

	return 0;
}
