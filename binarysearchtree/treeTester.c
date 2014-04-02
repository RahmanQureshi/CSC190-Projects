#include <string.h>
#include "tree.h"

#define MAX_KEY_SIZE 100

int main()
{
	char* input = (char*) malloc(sizeof(char) * 100);
	treeNodePTR mNode = NULL;

	while(1){
		printf("Command: ");
		scanf("%s", input);
		if(!strcmp(input, "print")){
			if(mNode==NULL){
				printf("Cannot print an empty list!\n");
				continue;
			}
			printf("Order (1-PreOrder; 2-InOrder; 3-PostOrder): ");
			int choice;
			scanf("%d", &choice);
			if(choice==1){
				PrintPreOrder(mNode);
			}else if(choice==2){
				PrintInOrder(mNode);
			}else if(choice==3){
				PrintPostOrder(mNode);
			}else{
				printf("Invalid\n");
			}
		}else if(!strcmp(input, "insert")){
			printf("Key: ");
			char key[MAX_KEY_SIZE];
			scanf("%s", key);
			printf("Value: ");
			int* value = malloc(sizeof(int));
			scanf("%d", value);
			Insert(&mNode, key, (void*) value);
		}else if(!strcmp(input, "find")){
			printf("Key: ");
			char key[MAX_KEY_SIZE];
			scanf("%s", key);
			treeNodePTR temp = FindItem(mNode, key);
			if(temp==NULL){
				printf("Item not found - not in tree\n");
			}else{
				printf("Item found - address of item is [%p]\n", (void*)temp);
			}
		}else if(!strcmp(input, "delete")){
			printf("Key: ");
			char key[MAX_KEY_SIZE];
			scanf("%s", key);
			void* data;
			if(DeleteNode(&mNode, key, &data)){
				printf("Node not found - not deleted\n");
			}else{
				printf("Node deleted\n");
				free(data);
				data = NULL;
			}
		}else if(!strcmp(input, "quit")){
			break;
		}else{
			printf("Invalid\n");
		}
	}

	free(input);
}
