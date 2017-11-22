/**
*/
#ifndef STACK_H_
#define STACK_H_
/**
*mystack - A generic stack
*/
typedef struct myStack
{
	void* node;
	struct myStack* next;
} myStack;

/**
*nodeStack - A stack for my nodes.
*/
struct nodeStack
{
	myStack* top;
};

typedef struct nodeStack nodeStack;

/**
*newStack - creates a new stack.
*/

nodeStack* stackInit();
/**
*stackPush - gets a node and stack and pushes the node in the top of the stack.
*/

void stackPush(nodeStack* stack, void* node);
/**
*stackPop - gets a stack pops the top and return the node that came out.
*
*/
void* stackPop(nodeStack* stack);
/**
*stackEmpty - gets a stack and head the top to null.
*/
int stackEmpty(nodeStack* stack);


#endif /* STACK_H_ */
