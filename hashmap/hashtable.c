#include "hashtable.h"

#define SENTINEL 0xDEADBEEF

/* Declarations */
int getHashCode(char* key, unsigned int range);
int SimpleIntHash( int value, unsigned int range );

// Function for computing load factor and use factor
// Why? Computing properties in the middle of other functions is VERY distracting.
// Also, people will not want the info most of the time anyway
void ComputeProperties(HashTablePTR hashTable);

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
	treeNodePTR* treeHandle = hashTable->buckets + hashCode;

	if(*treeHandle==NULL){ // If size is 0
		*previousDataHandle = NULL;
		if( Insert(treeHandle, key, data) == -1 ){
			return -2; // Not enough memory
		} else{
			return 0;
		}
	}else{
		if(DeleteNode(treeHandle, key, previousDataHandle)==-1){
			Insert(treeHandle, key, data); // TODO: ADD IF STATEMENT AROUND THIS TO CHECK FOR MEMORY
			return 1; //Collision, different keys
		}else{
			Insert(treeHandle, key, data);
			previousDataHandle = NULL;
			return 2; // Collision with same keys, previousDataHandle now points to data
		}
	}
}

int DeleteEntry( HashTablePTR hashTable, char *key, void **dataHandle )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}
	int hashCode = getHashCode(key, hashTable->info.bucketCount);
	if(DeleteNode((hashTable->buckets + hashCode), key, dataHandle)==-1){
		return -2;
	}else{
		int numEntries = (int) ( hashTable->info.loadFactor * (float)hashTable->info.bucketCount ) - 1;
		hashTable->info.loadFactor = (float)( (float) numEntries/ (float) hashTable->info.bucketCount);
		return 0;
	}
	return 0;
}

int FindEntry( HashTablePTR hashTable, char *key, void **dataHandle )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}
	int hashCode = getHashCode(key, hashTable->info.bucketCount);
	treeNodePTR root = *(hashTable->buckets + hashCode);
	treeNodePTR node = FindItem(root, key);
	if(node==NULL){
		*dataHandle = NULL;
		return -2;
	}else{
		*dataHandle = node->value;
		return 0;
	}
	return 0;
}

int GetKeys( HashTablePTR hashTable, char ***keysArrayHandle, unsigned int *keyCount )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}

	unsigned int totalNumKeys = (unsigned int) ( hashTable->info.loadFactor * (float)hashTable->info.bucketCount );
	*keyCount = totalNumKeys;
	
	char **keysArray = malloc(sizeof(char*) * totalNumKeys);
	int i;
	int counter = 0; // number of keys processed so far
	for(i=0; i<(hashTable->info.bucketCount); i++){
		treeNodePTR tree = *(hashTable->buckets + i);
		char **treeKeys;
		int numKeys;
		if( RetrieveKeys(tree, &treeKeys, &numKeys) == -2 ){
			*keysArrayHandle = NULL;
			return -2;
		}else{
			int j;
			for(j=0; j<numKeys; j++){
				keysArray[counter] = treeKeys[j];
				counter++;;
			}
		}
		free(treeKeys);
	}
	*keysArrayHandle = keysArray;
	return 0;
}


int GetHashTableInfo(HashTablePTR hashTable, HashTableInfo *pHashTableInfo)
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}
	ComputeProperties(hashTable);
	pHashTableInfo->bucketCount = hashTable->info.bucketCount;
	pHashTableInfo->loadFactor = hashTable->info.loadFactor;
	pHashTableInfo->useFactor = hashTable->info.useFactor;
	pHashTableInfo->largestBucketSize = hashTable->info.largestBucketSize;
	pHashTableInfo->dynamicBehaviour = hashTable->info.dynamicBehaviour;
	pHashTableInfo->expandUseFactor = hashTable->info.expandUseFactor;
	pHashTableInfo->contractUseFactor = hashTable->info.contractUseFactor;

	return 0;
}

// Function for computing load factor and use factor
// Why? Computing properties in the middle of other functions is VERY distracting.
// Also, people will not want the info most of the time anyway
void ComputeProperties(HashTablePTR hashTable)
{
	int i;
	unsigned int largestBucketSize = 0; // minimum value is 0
	int numEntries = 0;
	int numNonEmptyBuckets = 0;
	unsigned int numBuckets = hashTable->info.bucketCount;
	for(i=0; i<numBuckets; i++)
	{
		treeNodePTR root = *(hashTable->buckets + i);
		if(root==NULL) continue; // if the size is not 0
		largestBucketSize = largestBucketSize > (root->size) ? largestBucketSize : (unsigned int)root->size;
		numEntries += root->size;
		numNonEmptyBuckets += 1;
	}
	hashTable->info.loadFactor = (float)numEntries / (float)numBuckets;
	hashTable->info.useFactor = (float)numNonEmptyBuckets / (float)numBuckets;
	hashTable->info.largestBucketSize = largestBucketSize;
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
