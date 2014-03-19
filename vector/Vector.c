#include "Vector.h"

int CreateVector(VectorPTR *vectorHandle, unsigned int initialSize)
{
	VectorPTR newVector = (VectorPTR) malloc(sizeof(Vector));
	if(newVector==NULL){
		printf("Vector could not allocate initial memory\n");
		return FATAL_ERROR;
	}
	newVector->data = (void*) malloc(sizeof(void*) * initialSize);
	if(newVector->data == NULL){
		printf("Vector could not allocate initial memory\n");
		return FATAL_ERROR;
	}

	newVector->size = initialSize;
	newVector->numElements = 0;

	SetPrinterVector(newVector, DefaultPrinter);

	*vectorHandle = newVector;

	return 0;
}

int DestroyVector(VectorPTR *vectorHandle)
{
	// Free internal data
		// Free the induvidual elements of data
	// Free the vector
	if(vectorHandle==NULL || *vectorHandle==NULL){
		printf("Vector pointer is null\n");
		return ERROR;
	}

	VectorPTR vector = *vectorHandle;
	Element *data = vector->data;

	if(data==NULL){
		printf("Internal data array is null");
		return ERROR;
	}

	int i;
	for(i=0; i<(vector->numElements); i++){
		void* dataPiece = *(data + i);
		if(dataPiece==NULL){
			printf("Data pointer set to null, unable to free\n");
		}else{
			free(dataPiece);
		}
	}
	free(data);
	free(vector);
	return 0;
}

int AppendVector(VectorPTR vector, Element element)
{
	if(vector==NULL){
		printf("Vector pointer is null\n");
		return ERROR;
	}

	if( vector->numElements == (vector->size) ){ // If full

		// Double vector size
		Element *newData = (void*) malloc(sizeof(void*) * (vector->size)*2 + sizeof(void*)); // + 1 incase size is initially 0
		if(newData == NULL){
			printf("Vector could not allocate extra memory\n");
			return FATAL_ERROR;
		}

		// Copy the data over
		memcpy(newData, vector->data, sizeof(void*) * (vector->numElements) );

		// Re-assign and free
		free(vector->data);

		vector->data = newData;

		// Append element
		*( (vector->data) + (vector->numElements) ) = element;

		vector->size = vector->size * 2 + 1;

	}else{ // Simply append the element

		*( (vector->data) + (vector->numElements) ) = element;
	}

	vector->numElements = vector->numElements + 1;

	return 0;
}

int GetIndexVector(VectorPTR vector, unsigned int index, Element *handle)
{
	if(vector==NULL){
		printf("Vector pointer is null\n");
		return ERROR;
	}
	if( index > (vector->numElements)-1 ){
		printf("Index out of bounds\n");
		return ERROR;
	}

	Element *data = vector->data;

	*handle = *(data + index);

	return OK;
}

int DeleteIndexVector(VectorPTR vector, unsigned int index)
{
	if(vector==NULL){
		printf("Vector pointer is null\n");
		return ERROR;
	}
	if( index > (vector->numElements)-1 ){
		printf("Index out of bounds\n");
		return ERROR;
	}

	Element *data = vector->data;

	Element element = *(data + index);

	if(element==NULL){
		printf("DeleteIndexVector: Data pointer is set to null, deleting element\n");
	}else{
		free(element);
	}
	return OK;

}


int PrintVector(VectorPTR vector){

	if(vector==NULL){
		printf("Vector pointer is null\n");
		return ERROR;
	}

	Printer printer = vector->printer;

	if(printer==NULL){
		printf("Printer is not set");
		return ERROR;
	}

	printf("[ ");

	int i;
	for(i=0; i < (vector->numElements); i++){
		printer((vector->data)[i]);
		printf(" ");
	}

	printf("]\n");

	return OK;
}

void DefaultPrinter(void* data){
	if(data==NULL){
		printf("NULL");
	}else{
		printf("%d", *((int*)(data)));
	}
}

int SetPrinterVector(VectorPTR vector, Printer printer)
{
	if(vector==NULL){
		printf("Vector pointer is null\n");
		return ERROR;
	}else if(printer==NULL){
		printf("Printer function pointer is null\n");
		return ERROR;
	}
	vector->printer = printer;
	return OK;
}
