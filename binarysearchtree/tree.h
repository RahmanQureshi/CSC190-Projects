#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct treeNode* treeNodePTR;

struct treeNode
{
	char* key;
	void* value;
	int size;
	struct treeNode *right, *left;
};

typedef void (*NodeProcessor)(treeNodePTR node);

/*
* API
*/
int Insert(struct treeNode**, char*, void*);
int DeleteNode(struct treeNode**, char*, void**);
struct treeNode *FindItem(struct treeNode*, char*);
int PrintPreOrder(struct treeNode*);
int PrintInOrder(struct treeNode*);
int PrintPostOrder(struct treeNode*);

/*
* Personal functions (fit for public usage)
*/
int PostOrderTraversal(treeNodePTR root, NodeProcessor process);
int PreOrderTraversal(treeNodePTR root, NodeProcessor process);
int InOrderTraversal(treeNodePTR root, NodeProcessor process);


