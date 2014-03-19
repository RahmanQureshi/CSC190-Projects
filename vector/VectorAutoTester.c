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

	fprintf(stderr, "Destroying Vector: [%d]\n", DestroyVector(&mVector));

	return 0;
}
