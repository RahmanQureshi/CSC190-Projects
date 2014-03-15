#include "hashtable.h"

#define SENTINAL 0xDEADBEEF

int CreateHashTable( HashTablePTR *hashTableHandle, unsigned int initialSize )
{
	// Assume initialSize > 0

	// Create the Hashtable
	HashTablePTR mHashTablePTR = (HashTablePTR) malloc(sizeof(HashTableObject));
	if(mHashTablePTR == NULL){
		return -1;
	}

	// Create storage array
	mHashTablePTR->data = (Object*) malloc(sizeof(Object) * initialSize + sizeof(int));
	if(mHashTablePTR->data == NULL){
		return -1;
	}

	// TODO: Initialize storage array

	//Set sentinel
	mHashTablePTR->sentinel = (int) SENTINAL;

	memcpy(mHashTablePTR->data, &(mHashTablePTR->sentinel), sizeof(int)); //Set Sentinal

	*hashTableHandle = mHashTablePTR;

	return 0;
}

int DestroyHashTable( HashTablePTR *hashTableHandle )
{
	if(hashTableHandle == NULL || *hashTableHandle == NULL){
		return -1;
	}

	HashTablePTR mHashTablePTR = *hashTableHandle;
	Object* data = mHashTablePTR->data;
	
	// TODO: Free data
	if(data!=NULL){
		free(data);
	}

	// TODO: Free keys

	// Free hashtable
	free(mHashTablePTR);

	return 0;
}

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle )
{
	// Copy key
	char* hashKey = malloc(sizeof(char) * strlen(key););
	strcpy(hashKey, key);

	//Retrieve hash code

	//Store in linkedlist

	// Check if key existed
}