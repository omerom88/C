/*
 * shift.c
 *
 *  Created on: Nov 5, 2014
 *      Author: omerom88
 */

#include <stdio.h>

#define A 65
#define Z 90
#define LOWER_A 97
#define LOWER_Z 122
#define CYC_NUMBER 10
#define CYC_AB 26
#define NINE 57
#define ZERO 48
char encrypt(int shift, char chr);
char decrypt(int shift, char chr);

/**
 * The main tells the user to enter 3 things: the char he would like to move,
 * where he wants to move the char - up or down, and how much he wants to move
 * it on the asci table.
 *
 */

int main()
{
	unsigned int move = 26;
	char  encOrDec = 'n', chr ;
	while(move > (CYC_AB - 1))
	{
		printf("please enter the shift:\n");
		scanf(" %u", &move);
	}
	while((encOrDec != 'e') && (encOrDec) != 'd')
	{
		printf("would you like to encrypt (e) or decrypt (d)?\n");
		scanf(" %c", &encOrDec);
	}

	getchar();
	while((chr = getchar()) != EOF)
	{

		if(encOrDec == 'e')
		{
			chr = encrypt(move, chr);
		}
		else
		{
			chr = decrypt(move, chr);
		}
		printf("%c", chr);
	}
	return 0;
}

/**
 *encrypt - get a char and a int as input and move the char up in the alpha-bet as far as the int define.
 *
 */
char encrypt(int shift, char chr)
{
	//checks if the movement is relevant.
	unsigned int chrValue;
	chrValue = chr;
	if(! isalnum(chr))
	{
		return chr;
	}
	//set the loop in upper-case
	if((chrValue >= A) && (chrValue <= Z))
	{
		if(chrValue + shift > Z)
		{
			shift -= CYC_AB;
		}
	}
	//set the loop in lower-case
	else if((chrValue >= LOWER_A) && (chrValue <= LOWER_Z))
	{
		if(chrValue + shift > LOWER_Z)
		{
			shift -= CYC_AB;
		}
	}
	//set the loop in digits.
	else
	{
		if(chrValue + shift > NINE)
		{
			shift = shift % CYC_NUMBER;
		}
	}
	return chrValue += shift;
}

/**
 *decrypt - get a char and a int as input and move the char down in the alpha-bet as far as the int define.
 *
 */
char decrypt(int shift, char chr)
{
	unsigned int charVal;
	charVal = chr;
	//checks if the movement is relevant.
	if(! isalnum(chr))
	{
		return chr;
	}
	//set the loop in upper-case
	if(charVal >= A && charVal <= Z)
	{
		if(charVal - shift < A)
		{
			shift -= CYC_AB;
		}
	}
	//set the loop in lower-case
	else if(charVal >= LOWER_A && charVal <= LOWER_Z)
	{
		if(charVal - shift < LOWER_A)
		{
			shift -= CYC_AB;
		}
	}
	//set the loop in digits.
	else
	{
		if(charVal - shift < ZERO)
		{
			shift = shift % CYC_NUMBER;
			if(charVal - shift < ZERO)
			{
				charVal += CYC_NUMBER;
			}
		}
	}
	return charVal -= shift;
}
