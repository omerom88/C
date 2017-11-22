/**
*/
#ifndef SUDUKUTREE_H_
#define SUDUKUTREE_H_

#define LEAF 0
#define TRUE 1

/**
*the Node struct.
*has 3 data members - table, tabletableSize and value. 
*/
typedef struct
{
	int** table;
	int tableSize;
	unsigned int value;

} Node;
/**
*copy - A function that does a deep copy of a node.
*/
void* copyNode(void* node);
/**
*freeNode - A function that frees a node from memory. This function will be called for each
* node returned by getChildren..
*/
void freeNode(void* node);
/**
*getVal A function that gets a node and returns its value, as int.
*/
unsigned int getVal(void* node);
/**
*getChildren A function that gets a node and a pointer to an pNodeArray of nodes.
* The function allocates memory for an pNodeArray of all the children of the node, populate it,
* and returns it using the second parameter. The returned value is the number of children.
*/
int getChildren(void* head, void*** children);



#endif /* SUDUKUTREE_H_ */
