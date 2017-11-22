/**
*/
#include <stdio.h>
#include <stdlib.h>
#include "genericdfs.h"
#include "sudukutree.h"

#define VALID_LEN 2
#define MAX_SIZE 11
#define INVALID_FILE ":not a valid suduku file\n"

/**
*printNode - prints first the tableSize and then the table.
*/
void printNode(Node* suduku);

/**
*the main  
*/

int main( int argc, char* argv[])
{
	FILE* file;
	Node* suduku = (Node*)malloc(sizeof(Node));
	int i, tableSize;
	if (argc != VALID_LEN)
	{
		printf("please supply a file!");
		printf("usage: sudukusolver<filename>");
		return 1;
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("%s%s", argv[1] , "no such file\n");
		return 1;
	}
	fscanf(file, "%d\n", &suduku->tableSize);
	for (i = 1; i < MAX_SIZE; i++)
	{
		if (i*i == suduku->tableSize)
		{
			tableSize = TRUE;
			break;
		}
	}
	if (!tableSize)
	{
		printf("%s%s", argv[1] , INVALID_FILE);
		return 1;
	}
	suduku -> value = 0;
	suduku->table = (int**)malloc(sizeof(int*) * suduku->tableSize);
	int r , c , valid;
	for (r = 0; r <suduku->tableSize; r++)
	{
		suduku->table[r] = (int*)malloc(sizeof(int) * suduku->tableSize);
		for (c = 0; c < suduku->tableSize; c++)
		{
			if (c == suduku->tableSize - 1)
			{
				valid = fscanf(file , "%d\n" , &suduku -> table[r][c]);
				if ((suduku -> table[r][c]) != 0)
				{
					suduku -> value ++;
				}
			}
			else
			{
				valid = fscanf(file , "%d " , &suduku -> table[r][c]);
				if ((suduku -> table[r][c]) != 0)
				{
					suduku -> value ++;
				}
			}
			if (suduku->table[r][c] > suduku->tableSize ||
				suduku -> table[r][c] < 0 || valid == 0)
			{
				printf("%s%s", argv[1] , INVALID_FILE);
				return 1;
			}
		}
	}
	unsigned int best = suduku->tableSize * suduku->tableSize;
	Node* theBest = (Node*)getBest(suduku, getChildren, getVal, freeNode, copyNode, best);
	if (theBest->value != best)
	{
		printf("no solution!\n");
	}
	else
	{
		printNode(theBest);
	}
	freeNode(theBest);
	fclose(file);
	return 0;
}
/**
*/

void printNode(Node* suduku)
{
	if (suduku == NULL)
	{
		return;
	}
	int i = 0 , j = 0;
	printf("%d\n", suduku->tableSize);
	for (i = 0; i < suduku->tableSize; i++)
	{
		for (j = 0; j < suduku->tableSize; j++)
		{
			if (j == suduku->tableSize - 1)
			{
				printf("%d", suduku -> table[i][j]);
			}
			else
			{
				printf("%d ", suduku -> table[i][j]);
			}
		}
	printf("\n");
	}
}
