#include "hashtable.h"

#define SENTINEL 0xDEADBEEF

/* Declarations */
int getHashCode(char* key, unsigned int range);
int SimpleIntHash( int value, unsigned int range );

int GetLoadFactor( HashTablePTR hashTable, float *loadFactor );

int isValidHashTable(HashTablePTR hashTable);
int checkSentinel(HashTablePTR hashTable);

struct HashTableObjectTag
{
    int sentinel;
    HashTableInfo info;
    treeNodePTR* buckets;
};


/* Implementations */

int CreateHashTable( HashTablePTR *hashTableHandle, unsigned int initialSize )
{
	// Create hashtable
	HashTablePTR newHashTable = malloc(sizeof(struct HashTableObjectTag));
	
	// Set the sentinel
	newHashTable->sentinel = (int) SENTINEL;

	// Initialize memory (buckets)
	newHashTable->buckets = (treeNodePTR*) malloc(sizeof(treeNodePTR) * initialSize);
	int i;
	for(i=0; i<initialSize; i++){
		*(newHashTable->buckets + i) = NULL;
	}

	// Assign initial properties
	newHashTable->info.bucketCount = initialSize;
	newHashTable->info.loadFactor = 0;
	newHashTable->info.useFactor = 0;
	newHashTable->info.largestBucketSize = 0;
	newHashTable->info.dynamicBehaviour = 0;
	newHashTable->info.expandUseFactor = 0;
	newHashTable->info.contractUseFactor = 0;

	*hashTableHandle = newHashTable;
	return 0;
}

int DestroyHashTable( HashTablePTR *hashTableHandle )
{
	HashTablePTR hashTable = *hashTableHandle;
	
	if(!isValidHashTable(hashTable)){
		return -1;
	}

	// Destroy the nodes in the buckets
	unsigned int size = (hashTable->info).bucketCount;
	int i;
	for(i=0; i<size; i++){
		treeNodePTR head = *(hashTable->buckets + i);
		while(!(head==NULL)){
			void* data;
			DeleteNode(&head, head->key, &data);
			free(data); // Assuming it is an integer; NOTE: COMMENT OUT FOR ASSIGNMENT
		}
	}
	free(hashTable->buckets);
	free(*hashTableHandle);
	*hashTableHandle = NULL;
	return 0;
}

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}

	int hashCode = getHashCode(key, hashTable->info.bucketCount);
	treeNodePTR tree = *(hashTable->buckets + hashCode);
	if(tree==NULL){ // If size is 0
		if( Insert(hashTable->buckets + hashCode, key, previousDataHandle) == -1 ){
			return -2; // Not enough memory
		} else{
			return 0;
		}
	}else{
		if(DeleteNode(&tree, key, previousDataHandle)==-1){
			Insert(hashTable->buckets + hashCode, key, data);
			return 1; //Collision, different keys
		}else{
			Insert(hashTable->buckets + hashCode, key, previousDataHandle);
			return 2; // Collision with same keys, previousDataHandle now points to data
		}
	}
	return 0;
}

int DeleteEntry( HashTablePTR hashTable, char *key, void **dataHandle )
{
	return 0;
}

int FindEntry( HashTablePTR hashTable, char *key, void **dataHandle )
{
	return 0;
}

int GetKeys( HashTablePTR hashTable, char ***keysArrayHandle, unsigned int *keyCount )
{
	return 0;
}

int GetLoadFactor( HashTablePTR hashTable, float *loadFactor )
{
	return 0;
}

int getHashCode(char* key, unsigned int range)
{
	int total = 0;
	int length = (int) strlen(key);
	int i;
	for (i = 0; i < length; i++ )
	{
		total = total + (int) key[i];
	}
	return SimpleIntHash( total, range); 
}


int SimpleIntHash( int value, unsigned int range )
{
	int result;
	result = ( value % (int) range );
	if ( result < 0 )
	{
		result = -result;
	}

	return result;
}

int isValidHashTable(HashTablePTR hashTable){
	if(!(hashTable==NULL) && checkSentinel(hashTable)){
		return 1;
	}
	return 0;
}

int checkSentinel(HashTablePTR hashTable)
{
	int sentinel = ((int*) hashTable)[0];
	if(sentinel == (int) SENTINEL) {
		return 1;
	}
	return 0;
}


int PrintHashTable(HashTablePTR hashTable)
{
	return 0;
}
