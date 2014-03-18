#include "vector.h"

#define INITIAL_SIZE 100

int main()
{
	VectorPTR mVector;

	fprintf(stderr, "Creating Vector\n");
	CreateVector(&mVector, 100);

	fprintf(stderr, "Inserting into Vector\n");
	int* one = malloc(sizeof(int)); 
	*one = 5;
	InsertVector(mVector, (void*)one );

	int* two = malloc(sizeof(int));
	*two = 10;
	InsertVector(mVector, (void*)two );

	int* getZero;
	GetIndexVector(mVector, 0, (void**)&getZero);
	printf("Received: %d\n", *getZero);
	int* getOne;
	GetIndexVector(mVector, 1, (void**)&getOne);
	printf("Received: %d\n", *getOne);

	fprintf(stderr, "Destroying Vector\n");
	DestroyVector(&mVector);

	return 0;
}
