#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedlist.h"

#define offset sizeof(sentinel)

typedef struct
{
    int sentinel;
    unsigned int size;
    Object *data; //buckets
    char *keys;

} HashTableObject;

typedef HashTableObject *HashTablePTR;

int CreateHashTable( HashTablePTR *hashTableHandle, unsigned int initialSize );

int DestroyHashTable( HashTablePTR *hashTableHandle );

int InsertEntry( HashTablePTR hashTable, char *key, void *data, void **previousDataHandle );

int DeleteEntry( HashTablePTR hashTable, char *key, void **dataHandle );

int FindEntry( HashTablePTR hashTable, char *key, void **dataHandle );

int GetKeys( HashTablePTR hashTable, char * (*keysArrayHandle)[], unsigned int *keyCount );

int GetLoadFactor( HashTablePTR hashTable, float *loadFactor );
