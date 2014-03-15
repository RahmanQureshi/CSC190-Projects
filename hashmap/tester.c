#include "hashtable.h"

#define OK 0
#define FATAL_ERROR -1
#define UNEXPECTED_ERROR -2
#define INITIAL_SIZE 100

void checkSentinel(HashTablePTR);

int main()
{
	//Initialize
	HashTablePTR *mHashTableHandle;
	CreateHashTable(mHashTableHandle, INITIAL_SIZE);

	//Run tests
	checkSentinel(*mHashTableHandle);
}

void checkSentinel(HashTablePTR table){
	int* buckets = (int*) table->buckets;
	printf("%u\n", buckets[0]);
}
