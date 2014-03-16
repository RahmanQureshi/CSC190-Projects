#include "vector.h"

int CreateVector(VectorPTR *vectorHandle, unsigned int initialSize)
{
	VectorPTR newVector = (VectorPTR) malloc(sizeof(Vector));
	if(newVector==NULL){
		return -1;
	}
	newVector->data = (void*) malloc(sizeof(void*) * initialSize);
	if(newVector->data == NULL){
		return -1;
	}
	newVector->size = initialSize;

	*vectorHandle = newVector;

	return 0;
}
