#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define OK 0
#define ERROR 1
#define FATAL_ERROR -1


typedef void* Element;

typedef void (*Printer)(void* data);

typedef struct {
	Element *data;
	unsigned int numElements;
	unsigned int size;
	Printer printer;
} Vector;

typedef Vector *VectorPTR;


int CreateVector(VectorPTR *vectorHandle, unsigned int initialSize);

int DestroyVector(VectorPTR * vectorHandle);

// Append to the end of the vector
int AppendVector(VectorPTR vector, void* data);

// Assign the pointer to data at 'index' to *handle without removing it from the list
int GetIndexVector(VectorPTR vector, unsigned int index, Element *handle);

// Delete the pointer to data at 'index'
int DeleteIndexVector(VectorPTR vector, unsigned int index);

int PrintVector(VectorPTR vector);

void DefaultPrinter(void* data);

int SetPrinterVector(VectorPTR vector, Printer printer);
