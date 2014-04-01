#include <stdlib.h>
#include <stdio.h>

typedef struct treeNode* treeNodePTR;

struct treeNode
{
	int data;
	struct treeNode *right, *left;
};

typedef void (*NodeProcessor)(treeNodePTR node);

/*
* API
*/
void Insert(struct treeNode**, int);
int DeleteNode(struct treeNode**, int);
struct treeNode *FindItem(struct treeNode*, int);
int PrintPreOrder(struct treeNode*);
int PrintInOrder(struct treeNode*);
int PrintPostOrder(struct treeNode*);


/*
* Personal functions (fit for public usage)
*/
int PostOrderTraversal(treeNodePTR root, NodeProcessor process);
int PreOrderTraversal(treeNodePTR root, NodeProcessor process);
int InOrderTraversal(treeNodePTR root, NodeProcessor process);


