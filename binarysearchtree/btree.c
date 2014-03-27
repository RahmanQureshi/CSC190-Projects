#include "btree.h"

int CreateBTreeNode(BTreeNode **nodeHandle, int key, int value);
void PrintNode(BTreeNode *node);

int main()
{
	BTreeNode *head = NULL;
	InsertBinarySearchTree(&head, 10, 10);
	InsertBinarySearchTree(&head, 11, 11);
	InsertBinarySearchTree(&head, 5, 5);
	PreOrderTraversal(head, PrintNode);
	return(0);
}

int InsertBinarySearchTree(BTreeNode **rootHandle, int key, int value)
{
	BTreeNode* root = *rootHandle;

	if(root!=NULL && key < (root->key)){
		return InsertBinarySearchTree(&(root->leftSubTree), key, value);
	}else if(root!=NULL && key >= (root->key) ){
		return InsertBinarySearchTree(&(root->rightSubTree), key, value);
	}else{
		BTreeNode *newNode;
		if(CreateBTreeNode(&newNode, key, value)){
			printf("Failed to allocate memory for a node");
			return -1;
		}
		newNode->leftSubTree = NULL;
		newNode->rightSubTree = NULL;
		*rootHandle = newNode;
	}

	return (0);
}

int PostOrderTraversal(BTreeNode* root, NodeProcessor process)
{
	if(root==NULL) return 0;
	PostOrderTraversal(root->leftSubTree, process);
	PostOrderTraversal(root->rightSubTree, process);
	process(root);
	return 0;
}

int PreOrderTraversal(BTreeNode* root, NodeProcessor process)
{
	if(root==NULL) return 0;
	process(root);
	PreOrderTraversal(root->leftSubTree, process);
	PreOrderTraversal(root->rightSubTree, process);
	return 0;
}

/*
* Private functions
*/
int CreateBTreeNode(BTreeNode **nodeHandle, int key, int value)
{
	BTreeNode* newNode = (BTreeNode*) malloc(sizeof(BTreeNode));
	if(newNode==NULL){
		return -1;
	}
	newNode->key = key;
	newNode->value = value;
	*nodeHandle = newNode;
	return 0;
}

void PrintNode(BTreeNode *node)
{
	printf("%d:%d\n", node->key, node->value);
}
