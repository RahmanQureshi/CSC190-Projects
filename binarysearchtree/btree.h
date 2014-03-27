#include <stdlib.h>
#include <stdio.h>

typedef struct BTreeNodeStruct BTreeNode;

struct BTreeNodeStruct {
	int key;
	int value;
	BTreeNode* leftSubTree;
	BTreeNode* rightSubTree;
};

typedef void (*NodeProcessor)(BTreeNode* node);

int InsertBinarySearchTree(BTreeNode **rootHandle, int key, int value);

int CreateBTreeNode(BTreeNode **nodeHandle, int key, int value);

/*
* Runs PostOrderTraversal on the left subtree, then right subtree, then process on root
*/
int PostOrderTraversal(BTreeNode* root, NodeProcessor process);

int PreOrderTraversal(BTreeNode* root, NodeProcessor process);
