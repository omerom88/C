/*
 * count.c
 *
 *  Created on: Nov 5, 2014
 *      Author: omerom88
 */

#include <stdio.h>

#define GAP  32
#define T 1
#define F 0
/**
 * Program that counting words lines and chars in the input.
 */

int main()
{
	unsigned int chars = 0, words = 0, lines = 1;
	unsigned int CharOrGap = T;
	//wordOrGap - parameter that tells us if we standing on a gap
	//or on a char.
	char input;
	while((input = getchar()) != EOF)
	{
		chars++;
		if(input == GAP || input == '\n')
		{
			if(CharOrGap == F)
			{
				words++;
			}
			CharOrGap = T;
		}
		else
		{
			CharOrGap = F;
		}
		if(input == '\n')
		{
			lines++;
		}

	}
	if(! CharOrGap)
	{
		words++;
	}
	printf("\n %d , %d , %d", chars, words, lines);
	return 0;
}


