#include "linkedList.h"
#include "string.h"

int main()
{
	LinkedListPTR mLinkedList;
	CreateLinkedList(&mLinkedList);

	char* input = malloc(sizeof(char)*20);

	while(1)
	{
		printf("Command: ");
		scanf("%s", input);

		if(!strcmp(input, "insert")){

			printf("Item: ");
			int *i = malloc(sizeof(int));
			scanf("%d", i);
			AppendLinkedList(mLinkedList, (void*)i );

		}else if(!strcmp(input, "print")){

			PrintLinkedList(mLinkedList);

		}else if(!strcmp(input, "find")){

			int *i = malloc(sizeof(int));
			NodePTR mNode;
			printf("Item: ");
			scanf("%d", i);
			FindNode(mLinkedList, &mNode, (void*) i );
			free(i);
			if(mNode==NULL){
				printf("Item not found - not in list\n");
			}else{
				printf("Item found - address of item is: [%p]\n", (void*)mNode);
			}

		}else if(!strcmp(input, "delete")){

			printf("Item: ");
			int i;
			scanf("%d", &i);
			if(DeleteNode(mLinkedList, (void*)&i) == FOUND){
				printf("Node Deleted\n");
			}else{
				printf("Node Not Found\n");
			}

		}else if(!strcmp(input, "quit")){
			break;
		}else{

			printf("Command not recognized\n");

		}
	}

	DestroyNodesAndDataLinkedList(mLinkedList);
	DestroyLinkedList(&mLinkedList);
	free(input);

	return 0;
}
