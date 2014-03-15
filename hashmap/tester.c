#include "hashtable.h"

#define OK 0
#define FATAL_ERROR -1
#define UNEXPECTED_ERROR -2
#define INITIAL_SIZE 100

void forceWalkTable(HashTablePTR, int);

int main()
{
	//Initialize
	HashTablePTR *mHashTableHandle;
	CreateHashTable(mHashTableHandle, INITIAL_SIZE);

	//Run tests
	forceWalkTable(*mHashTableHandle, 1);
}

void forceWalkTable(HashTablePTR table, int numBytes){
	int* data = (int*) table->data;
	int i;
	for(i=0; i<numBytes; i++){
		printf("%u\n", data[i]);
	}
}
