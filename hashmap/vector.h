#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef void* Element;

typedef struct {
	Element *data;
	unsigned int size;
} Vector;


typedef Vector *VectorPTR;

int CreateVector(VectorPTR *vectorHandle, unsigned int initialSize);
