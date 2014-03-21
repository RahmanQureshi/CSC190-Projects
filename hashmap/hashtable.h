#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Vector.h"
#include "LinkedList.h"

typedef struct
{
    int sentinel;
    unsigned int numBuckets;
    LinkedListPTR *buckets;
    int numKeys;

} HashTableObject;

typedef struct 
{
	void* key;
	void* value;
} KVP;

typedef KVP *KVP_PTR;

typedef HashTableObject *HashTablePTR;

int CreateHashTable( HashTablePTR *hashTableHandle, unsigned int initialSize );

int DestroyHashTable( HashTablePTR *hashTableHandle );

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle );

int DeleteEntry( HashTablePTR hashTable, char *key, void **dataHandle );

int FindEntry( HashTablePTR hashTable, char *key, void **dataHandle );

int GetKeys( HashTablePTR hashTable, char ***keysArrayHandle, unsigned int *keyCount );

int GetLoadFactor( HashTablePTR hashTable, float *loadFactor );

int getHashCode(char* key, unsigned int range);

int GetLoadFactor( HashTablePTR hashTable, float *loadFactor );

int checkSentinel(HashTablePTR hashTable);

int GetBucketHashTable(HashTablePTR hashTable, LinkedListPTR* linkedList, int index);

int SetBucketHashTable(HashTablePTR hashTable, LinkedListPTR linkedList, int index);

int StringComparatorHashTable(void* dataOne, void* dataTwo);

int DataDeleterHashTable(void* data);
