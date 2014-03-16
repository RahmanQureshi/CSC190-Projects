#include "hashtable.h"

#define SENTINEL 0xDEADBEEF
#define OFFSET 1 //One integer

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
	mHashTablePTR->sentinel = (int) SENTINEL;
	memcpy(mHashTablePTR->buckets, &(mHashTablePTR->sentinel), sizeof(int)); //Set Sentinal

	fprintf(stderr, "Initializing buckets\n");

	// Initialize storage array
	int i;
	for(i=0; i<initialSize; i++){
		LinkedListPTR linkedList;
		fprintf(stderr, "Creating LinkedList\n");
		CreateLinkedList(&linkedList);
		fprintf(stderr, "Storing LinkedList\n");

		// TODO: PRETIFY (NOT 'BEST' WAY RIGHT NOW)
		*(((LinkedListPTR*)(((int*)(mHashTablePTR->buckets)) + OFFSET)) + i) = linkedList;
	}

	fprintf(stderr, "Setting size\n");

	// Set sizes
	mHashTablePTR->numBuckets = initialSize;
	mHashTablePTR->numKeys = 0;

	fprintf(stderr, "Setting handle\n");

	// Set handle
	// fprintf(stderr, "Address of Hashtable: %p\n", (void*) mHashTablePTR); DEBUG

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
			LinkedListPTR linkedList = *(((LinkedListPTR*)((((int*)(buckets)) + OFFSET))) + i);
			DestroyLinkedList(&linkedList);
		}
	}

	// Free keys
	unsigned int numKeys = mHashTablePTR->numKeys;
	int i;
	for(i=0; i<numKeys; i++){
		char* key = *(keys+i);
		free(key);
	}

	// Free hashtable and buckets
	free(buckets);
	free(mHashTablePTR);


	return 0;
}

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle )
{
	if(!checkSentinel(hashTable, (int) ( (int*)(hashTable->buckets) )[0])){ // If the sentinel is not the first four bytes of buckets array
		return -1;
	}

	int flag = 0; // 0 indicates success with no collisions

	LinkedListPTR *buckets = hashTable->buckets;
	char **keys = hashTable -> keys;

	fprintf(stderr, "Copying keys\n");
	// Copy key
	char* hashKey = (char*) malloc(sizeof(char) * strlen(key));
	strcpy(hashKey, key);

	// Retrieve hash code
	int hashCode = getHashCode(hashKey, hashTable->numBuckets);

	fprintf(stderr, "Retrieving linkedlist at hashCode\n");
	// Retrieve the list at hashCode
	LinkedListPTR linkedList = *((LinkedListPTR*)((int*)(buckets) + OFFSET) + hashCode);
	unsigned int listSize = linkedList->size;

	fprintf(stderr, "Checking key\n");
	// Add the key
	if(!containsKey(hashKey, keys, hashTable->numKeys))
	{
		fprintf(stderr, "Appending key\n"); //DEBUG
		*(keys + listSize) = hashKey;
		hashTable->numKeys = hashTable->numKeys + 1;
		flag = 1;
	}else{
		fprintf(stderr, "Key already set\n");
	}

	fprintf(stderr, "Checking previous data\n");
	// If the linkedList contains nothing, there is no previous data, otherwise set the previous data
	if(listSize==0){
		fprintf(stderr, "No previous data\n");
		*previousDataHandle = NULL;
	}else{
		fprintf(stderr, "Setting previous data\n");
		peekHead(linkedList, previousDataHandle);
		flag = 2;
	}

	fprintf(stderr, "Storing");
	// Store in the data in the linkedlist
	insertEntryLinkedList(linkedList, data);

	return flag;
}

int containsKey(char* key, char **keys, unsigned int size)
{
	int i;
	for(i=0; i<size; i++){
		if(!strcmp(key, keys[i])){
			return 1;
		}
	}
	return 0;
}

int getHashCode(char* key, unsigned int range)
{
	return 0;
}

int checkSentinel(HashTablePTR hashTable, int sentinel)
{
	if(sentinel == (int) SENTINEL) {
		return 1;
	}
	return 0;
}
