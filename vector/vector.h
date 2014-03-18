#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef void* Element;

typedef struct {
	Element *data;
	unsigned int numElements;
	unsigned int size;
} Vector;

typedef Vector *VectorPTR;


int CreateVector(VectorPTR *vectorHandle, unsigned int initialSize);

int DestroyVector(VectorPTR * vectorHandle);

int InsertVector(VectorPTR vector, void* data);

int GetIndexVector(VectorPTR vector, unsigned int index, Element *handle);
