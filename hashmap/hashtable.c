#include "hashtable.h"
#include "string.h"

#define SENTINEL 0xDEADBEEF
#define OFFSET 1 //One integer

int CreateHashTable( HashTablePTR *hashTableHandle, unsigned int initialSize )
{
	// Create the Hashtable
	HashTablePTR mHashTablePTR = (HashTablePTR) malloc(sizeof(HashTableObject));
	if(mHashTablePTR == NULL){
		return -1;
	}

	// Set sentinel
	mHashTablePTR->sentinel = (int) SENTINEL;

	// Create storage array
	mHashTablePTR->buckets = (LinkedListPTR*) malloc(sizeof(LinkedListPTR) * initialSize + sizeof(int));
	if(mHashTablePTR->buckets == NULL){
		return -1;
	}

	// Create linked list for each bucket
	int i;
	for(i=0; i<initialSize; i++){
		LinkedListPTR linkedList;
		CreateLinkedList(&linkedList);
		SetComparatorLinkedList(linkedList, StringComparatorHashTable); // Compare the keys of a KVP struct
		SetDataDeleterLinkedList(linkedList, DataDeleterHashTable); // Hashmap stores KVP structs. To delete data, need to set DataDeleter
		SetPrinterLinkedList(linkedList, LinkedListPrinterHashTable); //Pretty print the linked list
		SetBucketHashTable(mHashTablePTR, linkedList, i);
	}

	// Set size
	mHashTablePTR->numBuckets = initialSize;
	mHashTablePTR->numKeys = 0;

	// Set Handle
	*hashTableHandle = mHashTablePTR;

	return 0;
}

int DestroyHashTable( HashTablePTR *hashTableHandle )
{
	if(hashTableHandle == NULL || !isValidHashTable(*hashTableHandle)){
		return -1;
	}



	HashTablePTR mHashTablePTR = *hashTableHandle;
	LinkedListPTR *buckets = mHashTablePTR->buckets;

	unsigned int numBuckets = mHashTablePTR->numBuckets;

	// Free LinkedLists
	if(buckets!=NULL){
		int i;
		for(i=0; i<numBuckets; i++){
			LinkedListPTR linkedList;
			GetBucketHashTable(mHashTablePTR, &linkedList, i);
			DestroyNodesAndDataLinkedList(linkedList);
			DestroyLinkedList(&linkedList);
		}
	}

	// Free hashtable and buckets
	free(buckets);
	free(mHashTablePTR);

	return 0;
}

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}

	// Copy the key
	char* hashKey = (char*) malloc(sizeof(char) * strlen(key) + 1);
	strcpy(hashKey, key);

	// Get hashCode
	int hashCode = getHashCode(hashKey, hashTable->numBuckets);

	// Insert the key:data pair in the element
		// Get the linked list at hashCode
		// If the list is empty, insert and return 0
		// If the linkedlist contains the key already, overwrite its data and return 2
		// Otherwise append and return 1

	LinkedListPTR linkedList;
	GetBucketHashTable(hashTable, &linkedList, hashCode);
	NodePTR mNode; // Handle for previous data, if it exists
	KVP_PTR kvp = malloc(sizeof(KVP));
	kvp->key = (void*) hashKey;
	kvp->value = data;
	printf("Attempting to store: %s:%d\n", (char*)kvp->key, *((int*)kvp->value));
	printf("Current linkedlist at bucket:\n");
	PrintLinkedList(linkedList);

	if(linkedList->size==0){
		printf("List size 0, appending\n");
		hashTable->numKeys += 1;
		AppendLinkedList(linkedList, (void*) kvp);
		*previousDataHandle = NULL;
		return 0;
	}else if(! (FindNode(linkedList, &mNode, (void*) kvp ) == FOUND) ){ // If no node was found
		printf("Collision of buckets, appending\n");
		hashTable->numKeys += 1;
		AppendLinkedList(linkedList, (void*) kvp);
		*previousDataHandle = NULL;
		return 1;
	}else{
		printf("Node was found, setting previous data handle\n");
		*previousDataHandle = ((KVP_PTR)mNode->data)->value;
		((KVP_PTR)mNode->data)->value = data;
		free(hashKey); // Node was found, we do not need the hash key or new KVP anymore
		free(kvp);
		return 2;
	}
}

int DeleteEntry( HashTablePTR hashTable, char *key, void **dataHandle )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}

	int hashCode = getHashCode(key, hashTable->numBuckets);
	LinkedListPTR linkedList;
	GetBucketHashTable(hashTable, &linkedList, hashCode);

	KVP_PTR compare = malloc(sizeof(KVP));
	compare->key = key;

	KVP_PTR retrieve;
	if(DeleteNode(linkedList, compare, (void**)&retrieve) == FOUND ) {
		hashTable->numKeys -= 1;
		*dataHandle = retrieve->value;
		free(retrieve->key);
		free(retrieve);
		free(compare);
		return 0;
	}else{
		free(compare);
		return -2;
	}
}

int FindEntry( HashTablePTR hashTable, char *key, void **dataHandle )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}

	// Get the hash code
	int hashCode = getHashCode(key, hashTable->numBuckets);
	LinkedListPTR bucket;
	GetBucketHashTable(hashTable, &bucket, hashCode);

	NodePTR node; //
	KVP_PTR kvp = malloc(sizeof(KVP)); // Comparator takes kvp
	kvp->key = key;

	if(FindNode(bucket, &node, (void*)kvp)==FOUND){
		*dataHandle = ((KVP_PTR)node->data)->value;
		free(kvp);
		return 0;
	}else{
		free(kvp);
		return -2;
	}
}

int GetKeys( HashTablePTR hashTable, char ***keysArrayHandle, unsigned int *keyCount )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}

	int i;
	unsigned int numKeys = (unsigned int) hashTable->numKeys;
	int counter = 0; // Number of keys processed so far
	char **keysArray = (char**) malloc( sizeof(char*) * (unsigned long) numKeys );

	for(i=0; i<(hashTable->numBuckets); i++){ // Check every bucket
		LinkedListPTR linkedList;
		GetBucketHashTable(hashTable, &linkedList, i);
		if(!(linkedList->size==0)){
			printf("In getkeys:\n");
			PrintLinkedList(linkedList);
			int j;
			for(j=0; j<(linkedList->size); j++){
				void* temp;
				PeekIndex(linkedList, (void**) &temp, j);
				KVP_PTR kvp = (KVP_PTR) temp;
				char* key = (char*)(kvp->key);
				printf("Key found: %s\n", key);
				char* copy = (char*) malloc(sizeof(char) * strlen(key) + 1);
				strcpy(copy, kvp->key);
				*(keysArray + counter) = copy;
				counter += 1;
			}
		}
	}
	*keysArrayHandle = keysArray;
	*keyCount = numKeys;
	return 0;
}

int GetLoadFactor( HashTablePTR hashTable, float *loadFactor )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}
	
	float numItems = (float) hashTable->numKeys;
	float numBuckets = (float) hashTable->numBuckets;

	*loadFactor = numItems/numBuckets;

	return 0;
}

int getHashCode(char* key, unsigned int range)
{
	return 0;
}

int checkSentinel(HashTablePTR hashTable)
{
	int sentinel = hashTable->sentinel;
	if(sentinel == (int) SENTINEL) {
		return 1;
	}
	return 0;
}

int StringComparatorHashTable(void* dataOne, void* dataTwo)
{
	char* stringOne = (char*) ( ( (KVP_PTR)dataOne ) -> key);
	char* stringTwo = (char*) ( ( (KVP_PTR)dataTwo ) -> key);

	printf("Comparing %s to %s\n", stringOne, stringTwo);

	return strcmp(stringOne, stringTwo);
}

int GetBucketHashTable(HashTablePTR hashTable, LinkedListPTR* linkedList, int index)
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}
	LinkedListPTR* buckets = hashTable->buckets;
	*linkedList = *(buckets + index);
	return 0;
}

int SetBucketHashTable(HashTablePTR hashTable, LinkedListPTR linkedList, int index)
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}

	LinkedListPTR* buckets = hashTable->buckets;
	*(buckets + index) = linkedList;
	return 0;
}

int DataDeleterHashTable(void* data)
{
	KVP_PTR kvp = (KVP_PTR) data;
	free(kvp->key);
	free(kvp->value); //Commented out for CSC190 purposes
	return OK;
}

int isValidHashTable(HashTablePTR hashTable){
	if(!(hashTable==NULL) && checkSentinel(hashTable)){
		return 1;
	}
	return 0;
}

void LinkedListPrinterHashTable(void* data){
	// data is a KVP
	KVP_PTR kvp = (KVP_PTR) data;
	printf("%s:%d", (char*)(kvp->key), *((int*)kvp->value));
}