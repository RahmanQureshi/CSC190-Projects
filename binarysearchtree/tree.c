#include "tree.h"

void PrintNode(treeNodePTR node);
int getMaxNodeHandle(treeNodePTR* rootHandle, treeNodePTR** handlehandle);
int getMinNodeHandle(treeNodePTR* rootHandle, treeNodePTR** handlehandle);

static treeNodePTR NewTreeNode(int value)
{
	treeNodePTR newNode = (treeNodePTR) malloc(sizeof(struct treeNode));
	if(newNode==NULL){
		return NULL;
	}
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = value;

	return newNode;
}

void Insert(treeNodePTR* rootHandle, int key)
{
	treeNodePTR root = *rootHandle;

	if(root!=NULL && key < (root->data)){
		Insert(&(root->left), key);
	}else if(root!=NULL && key >= (root->data) ){
		Insert(&(root->right), key);
	}else{
		treeNodePTR newNode = NewTreeNode(key);
		if(newNode==NULL){
			printf("Could not allocate memory for node\n");
		}
		*rootHandle = newNode;
	}
}

int DeleteNode(struct treeNode** rootHandle, int key)
{
	// Find the node
	treeNodePTR root = *rootHandle;

	if(root==NULL){
		return -1;
	}else if( key<(root->data)){
		return DeleteNode( &(root->left) , key);
	}else if( key>(root->data) ) {
		return DeleteNode(&(root->right), key);
	}

	// If found, replace root with the node with max of left if it exists, or min of right 
	if( ! (root->left==NULL) ){
		treeNodePTR *replace; // handle to the node's address as it appears in the tree
		getMaxNodeHandle(&(root->left), &replace); //Guaranteed to get at least one node
		root->data = (*replace)->data;
		DeleteNode(replace, (*replace)->data);
		return 0;
	}else if( !(root->right==NULL) ){
		treeNodePTR* replace = NULL;
		getMinNodeHandle(&(root->right), &replace);
		root->data = (*replace)->data;
		DeleteNode(replace, (*replace)->data);
		return 0;
	}else if(root->data==key){
		free(root);
		*rootHandle = NULL;
		return 0;
	}
	return -1;
}

struct treeNode *FindItem(struct treeNode* root, int value)
{
	if(root==NULL) return NULL;
	if( (root->data)==value){
		return root;
	}
	if( value<(root->data) ){
		return FindItem(root->left, value);
	}else{
		return FindItem(root->right, value);
	}
}

int PrintPreOrder(struct treeNode* root)
{
	if(root==NULL) return -1;
	return PreOrderTraversal(root, PrintNode);
}

int PrintInOrder(struct treeNode* root)
{
	if(root==NULL) return -1;
	return InOrderTraversal(root, PrintNode);
}

int PrintPostOrder(struct treeNode* root)
{
	if(root==NULL) return -1;
	return PostOrderTraversal(root, PrintNode);
}

/*
* Generic Helper functions/Personal Functions
*/
int PostOrderTraversal(treeNodePTR root, NodeProcessor process)
{
	if(root==NULL) return 0;
	PostOrderTraversal(root->left, process);
	PostOrderTraversal(root->right, process);
	process(root);
	return 0;
}

int PreOrderTraversal(treeNodePTR root, NodeProcessor process)
{
	if(root==NULL) return 0;
	process(root);
	PreOrderTraversal(root->left, process);
	PreOrderTraversal(root->right, process);
	return 0;
}

int InOrderTraversal(treeNodePTR root, NodeProcessor process)
{
	if(root==NULL) return 0;
	InOrderTraversal(root->left, process);
	process(root);
	InOrderTraversal(root->right, process);
	return 0;
}

int getMaxNodeHandle(treeNodePTR* rootHandle, treeNodePTR** handlehandle)
{
	// Just go right until you hit null
	if(rootHandle==NULL || *rootHandle==NULL){ // Returns null if the tree is empty
		*handlehandle = NULL;
		return -1;
	}
	treeNodePTR root = *rootHandle;
	if( (root->right)==NULL ){
		*handlehandle = rootHandle;
		return 0;
	}else{
		return getMaxNodeHandle(&(root->right), handlehandle);
	}
}

int getMinNodeHandle(treeNodePTR* rootHandle, treeNodePTR** handlehandle)
{
	// Just go right until you hit null
	if(rootHandle==NULL || *rootHandle==NULL){ // Returns null if the tree is empty
		*handlehandle = NULL;
		return -1;
	}
	treeNodePTR root = *rootHandle;
	if( (root->left)==NULL ){
		*handlehandle = rootHandle;
		return 0;
	}else{
		return getMaxNodeHandle(&(root->left), handlehandle);
	}
}

void PrintNode(treeNodePTR node)
{
	printf("Key:%d\n", node->data);
}
