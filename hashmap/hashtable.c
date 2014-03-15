#include "hashtable.h"

#define SENTINAL 0xDEADBEEF
#define OFFSET sizeof(SENTINAL)

int CreateHashTable( HashTablePTR *hashTableHandle, unsigned int initialSize )
{
	// Assume initialSize > 0

	// Create the Hashtable
	HashTablePTR mHashTablePTR = (HashTablePTR) malloc(sizeof(HashTableObject));
	if(mHashTablePTR == NULL){
		return -1;
	}

	// Create storage array
	mHashTablePTR->buckets = (LinkedListPTR*) malloc(sizeof(LinkedListPTR) * initialSize + sizeof(int));
	if(mHashTablePTR->buckets == NULL){
		return -1;
	}

	// Set sentinel
	mHashTablePTR->sentinel = (int) SENTINAL;
	memcpy(mHashTablePTR->buckets, &(mHashTablePTR->sentinel), sizeof(int)); //Set Sentinal

	// Initialize storage array
	int i;
	for(i=0; i<initialSize; i++){
		LinkedListPTR linkedList;
		CreateLinkedList(&linkedList);
		*((mHashTablePTR->buckets) + i + OFFSET) = linkedList; 
	}

	// Set size
	mHashTablePTR->numBuckets = initialSize;

	// Set handle
	*hashTableHandle = mHashTablePTR;

	return 0;
}

int DestroyHashTable( HashTablePTR *hashTableHandle )
{
	if(hashTableHandle == NULL || *hashTableHandle == NULL){
		return -1;
	}

	HashTablePTR mHashTablePTR = *hashTableHandle;
	LinkedListPTR *buckets = mHashTablePTR->buckets;
	char **keys = mHashTablePTR->keys;
	unsigned int numBuckets = mHashTablePTR->numBuckets;
	
	// Free data values
	if(buckets!=NULL){
		int i;
		for(i=0; i<numBuckets; i++){
			LinkedListPTR linkedList = *(buckets + OFFSET + i);
			DestroyLinkedList(&linkedList);
		}
	}

	// Free keys
	unsigned int numKeys = mHashTablePTR->numKeys;
	if(numKeys!=NULL){
		int i;
		for(i=0; i<numKeys; i++){
			char* key = *(keys+i);
			free(key);
		}
	}

	// Free hashtable
	free(mHashTablePTR);

	return 0;
}

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle )
{
	// Copy key
	char* hashKey = (char*) malloc(sizeof(char) * strlen(key));
	strcpy(hashKey, key);

	//Retrieve hash code

	//Store in linkedlist

	// Check if key existed

	return 0;
}
