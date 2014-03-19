#include "Vector.h"

#define INITIAL_SIZE 0

int main()
{
	VectorPTR mVector;

	fprintf(stderr, "Creating Vector initial size of INITIAL_SIZE: [%d]\n", CreateVector(&mVector, INITIAL_SIZE));

	fprintf(stderr, "Printing:");
	PrintVector(mVector);

	fprintf(stderr, "Inserting numbers 0 to 99\n");
	int i;
	for(i=0; i<100; i++){
		int* j = malloc(sizeof(int));
		*j = i;
		AppendVector(mVector, (void*)j);
	}

	fprintf(stderr, "Printing:");
	PrintVector(mVector);

	int *get;
	fprintf(stderr, "Getting index 31: %d\n", GetIndexVector(mVector, 31, (void**)&get));
	fprintf(stderr, "Received: %d\n", *get);

	fprintf(stderr, "Removing index 0:\n");
	DeleteIndexVector(mVector, 0);

	fprintf(stderr, "Removing last index:\n");
	DeleteIndexVector(mVector, mVector->numElements-1);

	fprintf(stderr, "Removing index 47:\n");
	DeleteIndexVector(mVector, 47);

	int j = 77;
	fprintf(stderr, "Vector contains number 77? %d:\n", ContainsVector(mVector, (void*)&j));

	fprintf(stderr, "Printing:");
	PrintVector(mVector);

	fprintf(stderr, "Destroying Vector: [%d]\n", DestroyVector(&mVector));

	return 0;
}
