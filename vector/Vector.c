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
	newVector->numElements = 0;

	*vectorHandle = newVector;

	return 0;
}

int DestroyVector(VectorPTR *vectorHandle)
{
	// Free internal data
		// Free the induvidual elements of data
	// Free the vector

	VectorPTR vector = *vectorHandle;
	Element *data = vector->data;
	int i;
	for(i=0; i<(vector->numElements); i++){
		void* dataPiece = *(data + i);
		free(dataPiece);
	}
	free(data);
	free(vector);
	return 0;
}

int InsertVector(VectorPTR vector, Element element)
{
	if( vector->numElements == (vector->size) ){ // If full

		// Double vector size
		Element *newData = (void*) malloc(sizeof(void*) * (vector->size)*2);
		if(newData == NULL){
			return -1;
		}

		// Copy the data over
		memcpy(newData, vector->data, sizeof(void*) * (vector->numElements) );

		// Append element
		*( (vector->data) + (vector->numElements) ) = element;

		vector->numElements = vector->numElements + 1;
		vector->size = vector->size * 2;

		// Re-assign and free
		free(vector->data);
		vector->data = newData;

	}else{ // Simply append the element

		*( (vector->data) + (vector->numElements) ) = element;

		vector->numElements = vector->numElements + 1;
	}

	return 0;
}

int GetIndexVector(VectorPTR vector, unsigned int index, Element *handle)
{
	Element *data = vector->data;

	*handle = *(data + index);

	return 1;
}
