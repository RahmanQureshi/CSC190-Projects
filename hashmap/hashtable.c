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

int Resize( HashTablePTR hashTable, unsigned int newSize);
int MaintainProperties(HashTablePTR); // Originally took a handle, but due to API constraints by project, not possible

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
	
	if(newHashTable==NULL){
		return -1; // insufficient memory
	}

	// Set the sentinel
	newHashTable->sentinel = (int) SENTINEL;

	// Initialize memory (buckets)
	newHashTable->buckets = (treeNodePTR*) malloc(sizeof(treeNodePTR) * initialSize);
	if(newHashTable->buckets==NULL){
		return -1;
	}
	int i;
	for(i=0; i<initialSize; i++){
		*(newHashTable->buckets + i) = NULL;
	}

	// Assign initial properties
	newHashTable->info.bucketCount = initialSize;
	newHashTable->info.loadFactor = 0;
	newHashTable->info.useFactor = 0;
	newHashTable->info.largestBucketSize = 0;
	newHashTable->info.dynamicBehaviour = 1;
	newHashTable->info.expandUseFactor = (float)0.7;
	newHashTable->info.contractUseFactor = (float)0.2;

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
			//free(data); // Assuming it is an integer; NOTE: COMMENT OUT FOR ASSIGNMENT
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
			if(!(hashTable->info.dynamicBehaviour==0)){ // if dynamic behaviour is on
				MaintainProperties(hashTable); // Inserted into a new bucket, make sure that !(useFactor > expandFactor)
			}
			return 0;
		}
	}else{
		if( DeleteNode(treeHandle, key, previousDataHandle) == -1 ){
			if( Insert(treeHandle, key, data) == -1 ){
				return -2;
			}else{
				return 1; //Collision, different keys
			}
		}else{
			if( Insert(treeHandle, key, data) == -1 ){
				return -2;
			}
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
		if(!(hashTable->info.dynamicBehaviour==0)){ // if dynamic behaviour is on
			MaintainProperties(hashTable); // Successful deletion, make sure everything is OK
		}
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

	ComputeProperties(hashTable); // Needed to get the number of keys
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

int MaintainProperties(HashTablePTR hashTable) // TODO: ERROR CODES
{
	ComputeProperties(hashTable);
	unsigned int numEntries = (unsigned int) (hashTable->info.loadFactor * (float)hashTable->info.bucketCount );

	if( hashTable->info.useFactor > hashTable->info.expandUseFactor )
	{
		unsigned int newSize = 2 * (unsigned int) ( (float) numEntries / hashTable->info.expandUseFactor );
		if(newSize == 0){
			newSize = 1;
		}
		if(Resize(hashTable, newSize) == -2){
			printf("There was insufficient memory to resize\n");
			return -1;
		};
	}else if(hashTable->info.useFactor < hashTable->info.contractUseFactor) // Assume perfect hash distribution
	{
		unsigned int newSize =  (unsigned int) ( ( (float) numEntries / hashTable->info.contractUseFactor ) / 2.0 );
		if(newSize == 0){
			newSize = 1;
		}
		if(Resize(hashTable, newSize) == -2){
			printf("There was insufficient memory to resize\n");
			return -1;
		};
	}
	return 0;
}

int SetResizeBehaviour( HashTablePTR hashTable, int dynamicBehaviour, float expandUseFactor, float contractUseFactor )
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}
	if(contractUseFactor>=expandUseFactor) return 1;
	hashTable->info.contractUseFactor = contractUseFactor;
	hashTable->info.expandUseFactor = expandUseFactor;
	hashTable->info.dynamicBehaviour = dynamicBehaviour;
	return 0;
}

int Resize( HashTablePTR hashTable, unsigned int newSize)
{
	if(!isValidHashTable(hashTable)){
		return -1;
	}
	// Create new hashmap and then swap the bucket arrays

	// Initialize memory (buckets)
	HashTablePTR newHashTable;
	CreateHashTable(&newHashTable, newSize);

	// Temporarily disable re-sizing
	SetResizeBehaviour(hashTable, 0, hashTable->info.expandUseFactor, hashTable->info.contractUseFactor);
	SetResizeBehaviour(newHashTable, 0, 2, -1);

	// Rehash
	char **keys;
	unsigned int numKeys;
	if(GetKeys( hashTable, &keys, &numKeys) == -2){
		return -2;
	}
	int i;
	for(i=0; i<numKeys; i++){
		void* data;
		DeleteEntry( hashTable, *(keys+i), &data);
		void* dummy;
		if( InsertEntry( newHashTable, *(keys+i), data, &dummy) == -2){
			return -2; // Not enough memory
		}
		free(*(keys+i));
	}
	free(keys);

	// Hacky solution - swap buckets
	treeNodePTR* temp = hashTable->buckets;
	unsigned int oldSize = hashTable->info.bucketCount;

	hashTable->buckets = newHashTable->buckets;
	hashTable->info.bucketCount = newSize;

	newHashTable->buckets = temp;
	newHashTable->info.bucketCount = oldSize; 
	DestroyHashTable(&newHashTable);

	// Re-enable
	SetResizeBehaviour(hashTable, 1, hashTable->info.expandUseFactor, hashTable->info.contractUseFactor);

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
