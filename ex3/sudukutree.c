/**
*/
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sudukutree.h"

#define FINISH -1
/**
 * cellValidation - in charge of the cell content validation.
 */
int cellValidation (int num , Node* head , int r , int c);
/**
 * firstZero - scan the table for the first zero and returns it location.
 *
 */
void firstZero(Node* head, int * r, int * c);
/**
*/
int getChildren(void* node, void*** nodesArr)
{

	Node* head = (Node*)node;
	Node*** childList = (Node***)nodesArr;
	int* childs = (int*)malloc(sizeof(int) * head->tableSize);
	int i = 0, childrenCounter = 0;
	int r = 0;
	int c = 0;
	firstZero(head , &r , &c);
	if (r == FINISH && c == FINISH)
	{
		childList = NULL;
		return LEAF;
	}
	for (i = 1; i <= head->tableSize; i++)
	{
		if (cellValidation(i, head, r , c))
		{
			childs[childrenCounter] = i;
			childrenCounter++;
		}
	}
	*childList = (Node**)malloc(sizeof(Node*) * childrenCounter);
	for (i = 0; i < childrenCounter; i++)
	{
		(*childList)[i] = copyNode(head);
		(*childList)[i]->table[r][c] = childs[i];
		(*childList)[i]->value++;
	}
	*(nodesArr) = (void**)*childList;
	free(childs);
	return childrenCounter;
}
/**
*/
void firstZero(Node* head, int* r, int* c)
{
	int i = 0 , j = 0 ;
	for (i = 0; i < head->tableSize; i++)
	{
		for (j = 0; j < head->tableSize; j++)
		{
			if (head -> table[i][j] == 0 )
			{
				*r = i;
				*c = j;
				return;
			}
		}
	}
	*c = FINISH;
	*r = FINISH;
}
/**
*/

void* copyNode(void* src)
{
	Node* source = (Node*)src;
	Node* dest = (Node*)malloc(sizeof(Node));
	dest->tableSize = source->tableSize;
	dest -> value = source -> value;
	int r = 0;
	dest->table = (int **)malloc(sizeof(int*) *  dest->tableSize);

	for (r = 0; r < dest->tableSize; r++)
	{
		dest->table[r] = (int *)malloc(sizeof(int)*  dest->tableSize);
		memcpy(dest->table[r], source->table[r], sizeof(int) *(dest->tableSize));
	}
	return dest;
}
/**
*/

unsigned int getVal(void* node)
{
	Node* suduku = (Node*)node;
	return suduku -> value;
}
/**
*/

int cellValidation(int num, Node* head, int r, int c)
{
	int size;
	size = (int)sqrt(head->tableSize);
	int i = 0;
	int squreR = size * (r / size);
	int squreC = size * (c / size);
	int r1 = (r + (size - 1)) % size;
	int r2 = (r + (size + 1)) % size;
	int c1 = (c + (size - 1)) % size;
	int c2 = (c + (size + 1)) % size;
	for (i = 0; i < head->tableSize; i++)
	{
		if (head->table[i][c] == num)
		{
			return 0;
		}
		if (head->table[r][i] == num)
		{
			return 0;
		}
	}
	if (head->table[r1 + squreR][c1 + squreC] == num)
	{
		return 0;
	}
	if (head->table[r2 + squreR][c1 + squreC] == num)
	{
		return 0;
	}
	if (head->table[r1 + squreR][c2 + squreC] == num)
	{
		return 0;
	}
	if (head->table[r2 + squreR][c2 + squreC] == num)
	{
		return 0;
	}
	return 1;
}
/**
*/

void freeNode(void* node)
{
	Node* sudukuNode = (Node*)node;
	int i;
	for (i = 0; i < sudukuNode->tableSize; i++)
	{
		free(sudukuNode->table[i]);
	}
	free(sudukuNode->table);
	free(sudukuNode);

}