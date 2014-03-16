#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedlist.h"
#include "vector.h"

#define offset sizeof(sentinel)

typedef struct
{
    int sentinel;
    unsigned int numBuckets;
    LinkedListPTR *buckets; //buckets
    VectorPTR keys;

} HashTableObject;

typedef HashTableObject *HashTablePTR;

int CreateHashTable( HashTablePTR *hashTableHandle, unsigned int initialSize );

int DestroyHashTable( HashTablePTR *hashTableHandle );

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle );

int DeleteEntry( HashTablePTR hashTable, char *key, void **dataHandle );

int FindEntry( HashTablePTR hashTable, char *key, void **dataHandle );

int GetKeys( HashTablePTR hashTable, char * (*keysArrayHandle)[], unsigned int *keyCount );

int GetLoadFactor( HashTablePTR hashTable, float *loadFactor );

int getHashCode(char* key, unsigned int range);

int containsKey(char* key, VectorPTR keys);

int checkSentinel(HashTablePTR hashTable, int sentinel);

