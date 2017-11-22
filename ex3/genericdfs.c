/**
*/
#include <stdio.h>
#include <stdlib.h>
#include "genericdfs.h"
#include "sudukutree.h"
#include "stack.h"


/**
*stackFree - Empty the stack and frees all it capacity.
*/

void stackFree(nodeStack** stack , freeNodeFunc freeNode);
/**
*getBest - This function returns the node with the highest value in the tree, using
* DFS algorithm.
*/

pNode getBest(pNode head, getNodeChildrenFunc getChildren,
			  getNodeValFunc getVal, freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best)
{

	pNode* genericArray;
	pNode theBest = copy(head);
	nodeStack* stack = stackInit();
	stackPush(stack, head);
	int children , i;
	while (!stackEmpty(stack))
	{
		pNode node = stackPop(stack);
		if (getVal(node) == best)
		{
			freeNode(theBest);
			stackFree(&stack , freeNode);
			return node;
		}
		else if (getVal(node) > getVal(theBest))
		{
			freeNode(theBest);
			theBest = copy(node);
		}
			children = getChildren(node, &genericArray );
			for (i = 0 ; i < children ; i++)
			{
				stackPush(stack , genericArray[i]);
			}
		freeNode(node);
		free(genericArray);
	}
	stackFree(&stack , freeNode);
	if (getVal(theBest) == 0)
	{
		return NULL;
	}
	return theBest;
}
/**
*/
void stackFree(nodeStack** stack , freeNodeFunc freeNode)
{
	while (!stackEmpty(*stack))
	{
		freeNode(stackPop(*stack));
	}
	free(*stack);
	*stack = NULL;
}

