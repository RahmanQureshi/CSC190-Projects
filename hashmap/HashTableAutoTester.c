#include "hashtable.h"

#define OK 0
#define FATAL_ERROR -1
#define UNEXPECTED_ERROR -2

#define INITIAL_SIZE 1

//TODO: MAKE TWO TESTERS AND/OR USE COMMANDLINE ARGUMENTS WITH A .SH FILE TO SWITCH BETWEEN TESTERS

int main()
{
	// Hashmap Test

	HashTablePTR mHashTable = NULL;
	fprintf(stderr, "Creating HashTable\n");
	CreateHashTable(&mHashTable, INITIAL_SIZE);

	int* mPrevData;
	int* mData = malloc(sizeof(int)); *mData = 25;
	char* mKeyOne = "hello";

	fprintf(stderr, "Inserting data [%d] at [%s] : [%d]\n", *mData, mKeyOne, InsertEntry(mHashTable, mKeyOne, (void*)mData, (void**)&mPrevData));

	if(mPrevData==NULL){
		printf("No previous data\n");
	}else{
		printf("Previous data: %d", *mPrevData);
	}
	mPrevData = NULL;

	char* mKeyTwo = "hello";
	int* mDataTwo = malloc(sizeof(int)); *mDataTwo = 35;
	
	fprintf(stderr, "Inserting data [%d] at [%s] : [%d]\n", *mDataTwo, mKeyTwo, InsertEntry(mHashTable, mKeyTwo, (void*)mDataTwo, (void**)&mPrevData));

	if(mPrevData==NULL){
		printf("No previous data\n");
	}else{
		printf("Previous data: %d; freeing now\n", *mPrevData);
		free(mPrevData);
	}
	mPrevData = NULL;

	fprintf(stderr, "Retrieving entry at %s: [%d]\n", mKeyTwo, FindEntry( mHashTable, mKeyTwo, (void**)&mPrevData) );
	fprintf(stderr, "Retrieved: %d\n", *mPrevData);
	mPrevData = NULL;

	int* mDataThree = malloc(sizeof(int)); *mDataThree = 50;
	char* mKeyThree = "hello";
	fprintf(stderr, "Inserting data [%d] at [%s] : [%d]\n", *mDataThree, mKeyThree, InsertEntry(mHashTable, mKeyThree, (void*)mDataThree, (void**)&mPrevData));

	if(mPrevData==NULL){
		printf("No previous data\n");
	}else{
		printf("Previous data: %d; freeing now\n", *mPrevData);
		free(mPrevData);
	}
	mPrevData = NULL;

	char **keysArray;
	unsigned int numKeys;
	fprintf(stderr, "Getting keys: [%d]\n", GetKeys(mHashTable, &keysArray, &numKeys) );
	int z;
	for(z=0; z<numKeys; z++){
		printf("Key: %s\n", *(keysArray+z));
		free(*(keysArray+z));
	}
	free(keysArray);

	fprintf(stderr, "Deleting entry at %s: [%d]\n", mKeyThree, DeleteEntry(mHashTable, mKeyTwo, (void**)&mPrevData));
	fprintf(stderr, "Retrieved: %d\n", *mPrevData);
	if(mPrevData==NULL){
		printf("No previous data\n");
	}else{
		printf("Previous data: %d; freeing now\n", *mPrevData);
		free(mPrevData);
	}
	mPrevData = NULL;

	fprintf(stderr, "Destroying HashTable\n");
	DestroyHashTable(&mHashTable);

	return 0;
}
