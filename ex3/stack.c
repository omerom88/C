/**
*/
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

/**
*/
nodeStack* stackInit()
{
	nodeStack* stack = (nodeStack*)malloc(sizeof(nodeStack));
	if (stack == NULL)
	{
		return NULL;
	}
	stack->top = NULL;
	return stack;
}
/**
*/
int stackEmpty(nodeStack* stack)
{
	return stack->top == NULL;
}
/**
*/
void stackPush(nodeStack* stack, void* node)
{
	myStack* ptr = (myStack*)malloc(sizeof(myStack));
	if (ptr == NULL)
	{
		return;
	}

	ptr->node = node;
	ptr->next = stack->top;
	stack->top = ptr;
}

/**
*/
void* stackPop(nodeStack* stack)
{
	void* node;
	myStack* ptr;
	if (stack->top == NULL)
	{
		return NULL;
	}
	node = stack->top->node;
	ptr = stack->top;
	stack->top = ptr->next;
	free(ptr);
	return node;
}

