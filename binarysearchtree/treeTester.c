#include <string.h>
#include "tree.h"

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
			printf("Item: ");
			int item;
			scanf("%d", &item);
			Insert(&mNode, item);
		}else if(!strcmp(input, "find")){
			printf("Item: ");
			int item;
			scanf("%d", &item);
			treeNodePTR temp = FindItem(mNode, item);
			if(temp==NULL){
				printf("Item not found - not in tree\n");
			}else{
				printf("Item found - address of item is [%p]\n", (void*)temp);
			}
		}else if(!strcmp(input, "delete")){
			printf("Item: ");
			int item;
			scanf("%d", &item);
			if(DeleteNode(&mNode, item)){
				printf("Node not found - not deleted\n");
			}else{
				printf("Node deleted\n");
			}
		}else if(!strcmp(input, "quit")){
			break;
		}else{
			printf("Invalid\n");
		}
	}

	free(input);
}