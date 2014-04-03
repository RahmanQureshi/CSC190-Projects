#include "hashtable.h"

#define OK 0
#define FATAL_ERROR -1
#define UNEXPECTED_ERROR -2

int main()
{
	char* input = malloc(sizeof(char) * 100);
	HashTablePTR mHashTable;

	while(1){
		printf("Command: ");
		scanf("%s", input);
		if( strcmp(input, "create") == 0 ){
			printf("Size: ");
			unsigned int size;
			scanf("%u", &size);
			CreateHashTable(&mHashTable, size);
		}else if( strcmp(input, "quit") == 0 ){
			break;
		}else if( strcmp(input, "destroy") == 0 ){
			DestroyHashTable( &mHashTable );
		}
	}

	free(input);

	return 0;
}
