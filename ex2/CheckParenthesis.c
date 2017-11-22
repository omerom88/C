/*
 ============================================================================
 Name        : ex2.c
 Author      : omerom88
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 5000
#define FINISHED 0
#define COMMEND 4
#define CLOSER 1
#define DOUBLE 2
typedef struct Stack Stack;

/**
 * Stack structure for handle the number of openers and closures.
 */
struct Stack
{
	char     data[MAX];
	int      size;
};

/**
 * Initialized the stack.
 */
Stack stackInit()
{
	Stack StackNew;
	StackNew.size = FINISHED;
	return StackNew;
}

/**
 * Pop an item from the stack.
 */
char stackPop(Stack *stack)
{
	if (stack->size == FINISHED)
	{
		return 'E';
	}
	stack->size--;
	return stack->data[stack->size];
}

/**
 * Push an item from the stack.
 */
void stackPush(Stack *stack, char item)
{
	if (stack->size < MAX)
	{
		stack->data[stack->size++] = item;
	}
}

/**
 * Function that gets a file, open it and check if there is the same number of openers '('
 * and number of closures ')'.
 */
int main(int argc, char* argv[])
{
	Stack stack = stackInit();
	FILE* file = fopen(argv[1], "r");
	if(argc != COMMEND)
	{
		printf("please supply a file!\nusage: CheckParenthesis <filename>\n");
	}
	if (file == NULL)
	{
		printf("<filename>: no such file\n");
	}
	char check;
	int asciNum;
	while ((check = fgetc(file)) != EOF)
	{
		if (check == '<' || check == '{' || check == '[' || check == '(')
		{
			stackPush(&stack, check);
		}
		else if (check == '>' || check == '}' || check == ']' || check == ')')
		{
			if (check == ')')
			{
				asciNum = CLOSER;
			}
			else
			{
				asciNum = DOUBLE;
			}
			char top = stackPop(&stack);
			if (top != (check - asciNum))
			{
				printf("Bad structure\n");
				return FINISHED;
			}
		}
	}
	//check if there still parenthesis in the stack
	if (stack.size != FINISHED)
	{
		printf("Bad structure\n");
		return FINISHED;
	}
	else
	{
		printf("Ok\n");
	}
	return FINISHED;
}


