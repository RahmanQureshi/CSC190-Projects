#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"
#include "string.h"


typedef struct HashTableObjectTag HashTableObject;
typedef HashTableObject *HashTablePTR;

typedef struct HashTableInfoTag
{
    unsigned int bucketCount; // current number of buckets
    float loadFactor; // ( number of entries / number of buckets )
    float useFactor; // ( number of buckets with one or more entries / number of buckets )
    unsigned int largestBucketSize; // number of entries in the bucket containing the most entries
    int dynamicBehaviour; // whether or not the Hash Table will resize dynamically
    float expandUseFactor; // the value of useFactor that will trigger an expansion of the number of buckets
    float contractUseFactor; // the value of useFactor that will trigger a contraction in the number of buckets
} HashTableInfo;

int CreateHashTable( HashTablePTR *hashTableHandle, unsigned int initialSize );

int DestroyHashTable( HashTablePTR *hashTableHandle );

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle );

int DeleteEntry( HashTablePTR hashTable, char *key, void **dataHandle );

int FindEntry( HashTablePTR hashTable, char *key, void **dataHandle );

int GetKeys( HashTablePTR hashTable, char ***keysArrayHandle, unsigned int *keyCount );

int GetHashTableInfo( HashTablePTR hashTable, HashTableInfo *pHashTableInfo ); // Replaces GetLoadFactor

int SetResizeBehaviour( HashTablePTR hashTable, int dynamicBehaviour, float expandUseFactor, float contractUseFactor );

int PrintHashTable(HashTablePTR hashTable);

int Resize( HashTablePTR hashTable, unsigned int newSize); // Temporary for testing purposes

