#include "tree.h"

/* Private functions */

void PrintNode(treeNodePTR node);
int getMaxNodeHandle(treeNodePTR* rootHandle, treeNodePTR** handlehandle);
int getMinNodeHandle(treeNodePTR* rootHandle, treeNodePTR** handlehandle);
int StringToAscii(char*);


/* Function Implementations */

static treeNodePTR NewTreeNode(char* key, void* data)
{
	treeNodePTR newNode = (treeNodePTR) malloc(sizeof(struct treeNode));
	if(newNode==NULL){
		return NULL;
	}

	// Copy the key
	char* mKey = malloc(sizeof(char)*strlen(key) + 1);
	strcpy(mKey, key);
	newNode->key = mKey;

	// Copy the pointer to data
	newNode->value = data;

	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

void Insert(treeNodePTR* rootHandle, char* key, void* value)
{
	treeNodePTR root = *rootHandle;

	if( root!=NULL && StringToAscii(key) < StringToAscii(root->key) ){
		Insert(&(root->left), key, value);
	}else if( root!=NULL && StringToAscii(key) >= StringToAscii(root->key) ){ // If equal, always go right
		Insert(&(root->right), key, value);
	}else{
		treeNodePTR newNode = NewTreeNode(key, value);
		if(newNode==NULL){
			printf("Could not allocate memory for node\n");
		}
		*rootHandle = newNode;
	}
}

int DeleteNode(struct treeNode** rootHandle, char* key, void** dataHandle)
{
	// Find the node
	treeNodePTR root = *rootHandle;

	if(root==NULL){
		*dataHandle = NULL;
		return -1;
	}else if( StringToAscii(key) < StringToAscii(root->key) ){
		return DeleteNode( &(root->left), key, dataHandle);
	}else if( StringToAscii(key) > StringToAscii(root->key) ) {
		return DeleteNode(&(root->right), key, dataHandle);
	}

	// Will progress down if the node exists and the keys are equal
	*dataHandle = root->value;

	// Replace root with the node with max of left if it exists, or min of right 
	if( ! (root->left==NULL) ){
		treeNodePTR *replace; // Get replacement node
		getMaxNodeHandle(&(root->left), &replace);
		// Swap keys, bring data up
		char* temp = root->key;
		root->key = (*replace)->key; // Replace the key and data
		root->value = (*replace)->value;
		(*replace)->key = temp;
		void* dummy;
		DeleteNode(replace, (*replace)->key, &dummy);
		return 0;
	}else if( !(root->right==NULL) ){
		treeNodePTR* replace;
		getMinNodeHandle(&(root->right), &replace);
		char* temp = root->key;
		root->key = (*replace)->key; // Replace the key and data
		root->value = (*replace)->value;
		(*replace)->key = temp;
		void* dummy;
		DeleteNode(replace, (*replace)->key, &dummy);
		return 0;
	}else if( strcmp(root->key, key)==0 ){
		free(root->key);
		free(root);
		*rootHandle = NULL;
		return 0;
	}
	return -1;
}

struct treeNode *FindItem(struct treeNode* root, char* key)
{
	if(root==NULL) return NULL;

	if( strcmp(root->key, key)==0 ){
		return root;
	}

	if( StringToAscii(key)<StringToAscii(root->key) ){
		return FindItem(root->left, key);
	}else{ // If Ascii values equal but strings not the same, go right
		return FindItem(root->right, key);
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

int StringToAscii(char* key)
{
	int total = 0;
	int size = (int) strlen(key);
	for(int i=0; i<size; i++){
		total = total + (int)key[i];
	}
	return total;
}

void PrintNode(treeNodePTR node)
{
	char* key = node->key;
	int* val = (int*) node->value;
	printf("Key:%s Value:%d\n", key, *val);
}
