#include "hashtable.h"

#define OK 0
#define FATAL_ERROR -1
#define UNEXPECTED_ERROR -2

#define KEY_SIZE 100

int main()
{
	char* input = malloc(sizeof(char) * 100);
	HashTablePTR mHashTable = NULL;

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
		}else if( strcmp(input, "insert") == 0 ){
			char key[KEY_SIZE];
			int* value = malloc(sizeof(int));
			printf("Key: ");
			scanf("%s", key);
			printf("Value: ");
			scanf("%d", value);
			void* prevData;
			printf("Return Code: [%d]\n", InsertEntry(mHashTable, key, (void*) value, &prevData));
			if(!(prevData==NULL)){
				printf("Key collision, previous data value: [%d]\n", *((int*)prevData));
				free(prevData);
				prevData = NULL;
			}
		}else if( strcmp(input, "find") == 0 ){
			char key[KEY_SIZE];
			printf("Key: ");
			scanf("%s", key);
			void* data;
			printf("Return Code: [%d]\n", FindEntry(mHashTable, key, &data));
			if(data==NULL){
				printf("Key not found\n");
			}else{
				printf("Key found. Data: %d\n", *((int*)data));
			}
		}else if( strcmp(input, "delete") == 0 ){
			char key[KEY_SIZE];
			printf("Key: ");
			scanf("%s", key);
			void* prevData;
			printf("Return Code: [%d]\n", DeleteEntry(mHashTable, key, &prevData));
			if(!(prevData==NULL)){
				printf("Node deleted. Data: %d\n", *((int*)prevData));
				free(prevData);
				prevData = NULL;
			}
		}else if( strcmp(input, "getkeys") == 0 ){
			unsigned int numKeys;
			char **keys;
			printf("Return Code: [%d]\n", GetKeys( mHashTable, &keys, &numKeys));
			int i;
			printf("Keys:\n");
			for(i=0; i<numKeys; i++){
				printf("%s\n", keys[i]);
				free(keys[i]);
			}
			free(keys);
		}else if( strcmp(input, "info") == 0 ){
			HashTableInfo info;
			GetHashTableInfo(mHashTable, &info);
			printf("Bucket Count: %u\n", info.bucketCount);
			printf("Load Factor: %f\n", info.loadFactor);
			printf("Use Factor: %f\n", info.useFactor);
			printf("Largest Bucket Size: %u\n", info.largestBucketSize);
			printf("Dynamic Behaviour: %d\n", info.dynamicBehaviour);
			printf("Expand Use Factor: %f\n", info.expandUseFactor);
			printf("Contract Use Factor: %f\n", info.contractUseFactor);
		}else{
			printf("Invalid\n");
		}
	}

	free(input);

	return 0;
}
