#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define OK 0
#define ERROR 1
#define FATAL_ERROR -1


typedef void* Element;

typedef void (*Printer)(void* data);

typedef int (*Comparator)(void* dataOne, void* dataTwo);

typedef struct {
	Element *data;
	unsigned int numElements;
	unsigned int size;
	Printer printer;
	Comparator comparator;
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

// Returns 1 if dataOne is greater than dataTwo or dataTwo is null
// Returns 0 if dataOne is equal to dataTwo
// Returns -1 if dataOne is less than dataTwo
int SetComparatorVector(VectorPTR vector, Comparator comparator);

// For CSC190 purposes, the default comparator assumes data members are integers
int DefaultComparator(void* dataOne, void* dataTwo);

// Checks if data is inside vector (uses comparator)
// Returns 1 if vector does contain data, and 0 if it does not
int ContainsVector(VectorPTR vector, void* data);

