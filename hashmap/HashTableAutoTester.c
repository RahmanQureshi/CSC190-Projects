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

	void* previousData;
	char* keyArray[7] = {"a","b","c","d","e","f","a"};
	int dataArray[11] = {1, 2, 3, 4, 5, 6, 7};

	int i;
	for(i=0; i<7; i++){
		char* key = keyArray[i];
		int* data = malloc(sizeof(int));
		*data = dataArray[i];
		fprintf(stderr, "Inserting entry: [%d]\n", InsertEntry(mHashTable, key, (void*)data, &previousData) );
		if(!(previousData==NULL)){
			fprintf(stderr, "Previous data: %d\n", *((int*)previousData));
			free(previousData);
			previousData = NULL;
		}
	}

	char **hashKeysArray;
	unsigned int keyCount;
	fprintf(stderr, "Retrieving keys: [%d]\n", GetKeys(mHashTable, &hashKeysArray, &keyCount));
	fprintf(stderr, "Number of keys: %d\n", keyCount);
	fprintf(stderr, "Keys: ");
	for(i=0; i<keyCount; i++){
		fprintf(stderr, "%s ", *(hashKeysArray+i));
		free(*(hashKeysArray+i));
	}
	fprintf(stderr, "\n");
	free(hashKeysArray);

	char* deleteKey = "q";
	fprintf(stderr, "Deleting key %s : [%d]\n", deleteKey, DeleteEntry( mHashTable, deleteKey, &previousData));
	if(!(previousData==NULL)){
		fprintf(stderr, "Previous data: %d\n", *((int*)previousData));
		free(previousData);
		previousData = NULL;
	}

	char* findEntry = "q";
	fprintf(stderr, "Finding value with key %s: [%d]\n", findEntry, FindEntry( mHashTable, findEntry, &previousData ) );
	if(!(previousData==NULL)){
		fprintf(stderr, "Data: %d\n", *((int*)previousData)); // Don't delete, the hashmap still owns it
		previousData = NULL;
	}else{
		fprintf(stderr, "No data found\n");
	}

	fprintf(stderr, "Destroying HashTable\n");
	DestroyHashTable(&mHashTable);

	return 0;
}
