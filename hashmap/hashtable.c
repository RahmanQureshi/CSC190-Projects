#include "hashtable.h"
#include "string.h"

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

	CreateVector(&(mHashTablePTR->keys), initialSize);
	SetComparatorVector(mHashTablePTR->keys, StringComparatorHashTable);

	// Set sentinel
	mHashTablePTR->sentinel = (int) SENTINEL;
	memcpy(mHashTablePTR->buckets, &(mHashTablePTR->sentinel), sizeof(int)); //Set Sentinal

	fprintf(stderr, "Initializing buckets\n");

	// Initialize storage array
	int i;
	for(i=0; i<initialSize; i++){
		LinkedListPTR linkedList;
		CreateLinkedList(&linkedList);

		// TODO: PRETIFY (NOT 'BEST' WAY RIGHT NOW)
		*(((LinkedListPTR*)(((int*)(mHashTablePTR->buckets)) + OFFSET)) + i) = linkedList;
	}

	fprintf(stderr, "Setting size\n");

	// Set size
	mHashTablePTR->numBuckets = initialSize;


	// Set Handle
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
	VectorPTR keys = mHashTablePTR->keys;

	unsigned int numBuckets = mHashTablePTR->numBuckets;

	// Free LinkedLists
	if(buckets!=NULL){
		int i;
		for(i=0; i<numBuckets; i++){
			LinkedListPTR linkedList = *(((LinkedListPTR*)((((int*)(buckets)) + OFFSET))) + i);
			DestroyNodesAndDataLinkedList(linkedList);
			DestroyLinkedList(&linkedList);
		}
	}

	// Free keys
	DestroyVector(&keys);

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
	VectorPTR keys = hashTable -> keys;

	fprintf(stderr, "Copying keys\n");
	// Copy key
	char* hashKey = (char*) malloc(sizeof(char) * strlen(key) + 1); // + 1 for terminator
	strcpy(hashKey, key);

	// Retrieve hash code
	int hashCode = getHashCode(hashKey, hashTable->numBuckets);

	fprintf(stderr, "Retrieving linkedlist at hashCode\n");
	
	// Retrieve the list at hashCode
	LinkedListPTR linkedList = *((LinkedListPTR*)((int*)(buckets) + OFFSET) + hashCode);
	unsigned int listSize = linkedList->size;

	fprintf(stderr, "Checking key\n");
	// Add the key
	if(!ContainsVector(keys, (void*) hashKey)){
		printf("Key not found, inserting now");
		AppendVector(keys, (void*)hashKey);
	}

	fprintf(stderr, "Checking previous data\n");
	// If the linkedList contains nothing, there is no previous data, otherwise set the previous data
	if(listSize==0){
		fprintf(stderr, "No previous data\n");
		*previousDataHandle = NULL;
	}else{
		fprintf(stderr, "Setting previous data\n");
		PeekHead(linkedList, previousDataHandle);
		flag = 2;
	}

	fprintf(stderr, "Storing\n");
	// Store in the data in the linkedlist
	AppendLinkedList(linkedList, data);

	return flag;
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

int StringComparatorHashTable(void* dataOne, void* dataTwo)
{
	char* stringOne = (char*) dataOne;
	char* stringTwo = (char*) dataTwo;

	return strcmp(stringOne, stringTwo);
}