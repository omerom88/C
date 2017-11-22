/*
 * waredb.c
 *
 *  Created on: Nov 12, 2014
 *      Author: omerom88
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAX 20
#define ARRY_NUM_ELEM 5
#define COMMEND 4
#define END_YEAR 12
#define NAME_LENGTH 21
#define BARKOD_LENGTH 4
#define ARRY_MAX 1000
#define NEW_ARRY_MAX 2000
#define TRUE 1
#define FALSE 0
#define EXIT 0
#define GO_OUT -1
#define ACURRATE 0.001
#define LIM_ACURRATE 0.002
#define END_LIST 9999

typedef struct Product Product;
/**
 * Structure for product. include the fields name,quantity,bar-code,month and a year.
 */
struct Product
{
	char    name[NAME_LENGTH];
	float     quantity;
	int		barkod;
	int	 	month;
	int	 	year;
};

typedef struct Sent Sent;
/**
 * Structure for Set. include the fields quantity and a bar-code.
 */
struct Sent
{
	float     quantity;
	int		barkod;
};

void sortArry(Product* productList, int listSize);
int compar(Product first, Product second);
int deleteItem(int counter, Product* productList, int numOfProduct);

/**
 * Function that build an array for 'Sent' structure. Checking validation and create a 'barkod'
 * and the 'quantity' fields.
 */
int createSentArray(FILE* file, Sent* sentList)

{
	int input, counter = FALSE;
	while(TRUE)
	{
		input = fscanf(file, "%d\t%f\n", & sentList[counter].barkod, & sentList[counter].quantity);
		if(sentList[counter].quantity < FALSE)
		{
			return GO_OUT;
		}
		if(sentList[counter].barkod < FALSE || sentList[counter].barkod > END_LIST)
		{
			return GO_OUT;
		}
		if(input == EOF || input == EXIT)
		{
			return counter;
		}
		counter++;
	}
	return EXIT;
}

/**
 * Function that gets a file and a product structure and open the file to the right parameters,
 * Check the validation of them and update every product.
 */
int openFileToProduct(FILE* file, Product* productList)
{

	int input, counter = FALSE;
	while (TRUE)
	{
		input = fscanf(file, "%20[^\t]\t%d\t%f\t%d-%d\n", productList[counter].name, &productList\
				[counter].barkod, &productList[counter].quantity, &productList[counter].year, \
				&productList[counter].month);
		if(input == EOF)
		{
			return counter;
		}
		if(productList[counter].barkod < FALSE || productList[counter].barkod > END_LIST)
		{
			return GO_OUT;
		}
		counter++;
	}
	return EXIT;
}

/**
 * Function for delete an item from the product list. The function put the item in the last place
 * on the list, and then collapse the list by one - means, delete the item from the list.
 */
int deleteItem(int counter, Product* productList, int numOfProduct)
{
	productList[counter].barkod = END_LIST;
	sortArry(productList, numOfProduct);
	numOfProduct--;
	return numOfProduct;
}

/**
 * Compare function, that gets two product and check who has the biggest bar-code,date and name.
 * Was built to help the sort function and to decide between two products who's first in the list.
 */
int compar(Product first, Product second)
{
	if (first.barkod == second.barkod)
	{
		if (first.year == second.year)
		{
			if(first.month == second.month)
			{
				if(!strcmp(first.name, second.name))
				{
					return EXIT;
				}
				else
				{
					return GO_OUT;
				}
			}
			else
			{
				return (first.month - second.month);
			}
		}
		else
		{
			return(first.year - second.year);
		}
	}
	else
	{
		return(first.barkod - second.barkod);
	}
}

/**
 * Function that gets a file and a list of products, check the validation of the file and write
 * on the file for updating.
 */
int writeProductToFile(Product* productList, int listSize, char* openFile)
{
	FILE* file = fopen(openFile, "w");
	if (file == NULL)
	{
		printf("%s: Permission denied\n", openFile);
		return TRUE;
	}
	int counter;
	for(counter = FALSE; counter < listSize; counter++)
	{
		fprintf(file, "%s\t%d\t%.3f\t%d-%d\n", productList[counter].name,
				productList[counter].barkod, productList[counter].quantity, productList[counter]\
				.year, productList[counter].month);
	}
	return EXIT;
}

/**
 * Sort function. sort a list of product using the famous bubbleSort with a function compar that i
 * wrote.
 */
void sortArry(Product* productList, int listSize)
{
	int first, seconde, comperator;
	Product swap;
	for (first = FALSE ; first < ( listSize - TRUE ); ++first)
	{
		for (seconde = FALSE ; seconde < listSize - first - TRUE; ++seconde)
		{
			//calling compar for deciding how to sort.
			comperator = compar(productList[seconde], productList[seconde + TRUE]);
			if (comperator > FALSE)
			{
				swap = productList[seconde + TRUE];
				productList[seconde + TRUE] = productList[seconde];
				productList[seconde] = swap;
			}
			else if (comperator == FALSE)
			{
				productList[seconde + TRUE].quantity += productList[seconde].quantity;
				listSize = deleteItem(seconde, productList, listSize);
			}
		}
	}
}

/**
 * Function that backup the original list in case we don't have enough products.
 */
void beckupList(Product* firstList, Product* secondList, int numOfProduct)
{
	int i;
	for(i = FALSE; i < numOfProduct; i++)
	{
		firstList[i] = secondList[i];
	}
}

/**
 * Function that control the sending in case we have two different products with the same bar-code.
 */
int addingProduct(Product* productList, int counter, Sent* sentList, Product* backUp, \
				  int numOfProduct, int sentCounter)
{
	if(productList[counter].barkod == productList[counter + TRUE].barkod)
	{
		sentList[sentCounter].quantity -= productList[counter].quantity;
		productList[counter].quantity = FALSE;
		counter++;
	}
	else
	{
		printf("not enough items in warehouse\n");
		beckupList(productList, backUp, numOfProduct);
		exit(EXIT_FAILURE);
	}
	return counter;
}

/**
 * Function for sent application. Gets a list of product that in the garage, and a list of product
 * who need to be sent. Update the original list if there enough products in the garage.
 */
void sent(Product* productList, int numOfProduct, Sent* sentList, int numOfProductSent)
{
	int sentCounter = FALSE, counter = FALSE;
	float temp;
	Product backUp[NEW_ARRY_MAX];
	beckupList(backUp, productList, numOfProduct);
	while(sentCounter < numOfProductSent)
	{
		if(sentList[sentCounter].barkod < productList[counter].barkod)
		{
			sentCounter++;
			continue;
		}

		if(sentList[sentCounter].barkod == productList[counter].barkod)
		{
			temp = sentList[sentCounter].quantity;
			while(temp > ACURRATE)
			{
				temp = sentList[sentCounter].quantity;
				temp -= productList[counter].quantity;
				//accurate till 3 numbers after the dot
				if(temp > ACURRATE)
				{
					counter = addingProduct(productList, counter, sentList, backUp, numOfProduct, sentCounter);
				}
				else
				{
					productList[counter].quantity -= sentList[sentCounter].quantity;
					counter++;
					break;
				}
			}
			sentCounter++;
		}
		else
		{
			counter++;
		}
	}
}

/**
 * Function for received application. Gets a list of product that in the garage, and a list of
 * new product that received. Combine the two lists into one, and return the number of product
 * in the new list.
 */
int received(Product* productList, int numOfProduct, Product* productListRec, int numOfProductRec)
{
	Product finalList[NEW_ARRY_MAX];
	int first = FALSE, seconde = FALSE, counter, comperator;
	for(counter = FALSE ; counter < numOfProduct + numOfProductRec && !(first == numOfProduct && \
			seconde == numOfProductRec); counter++ )
	{
		//if one of the list are finished, add all the rest of the second one
		if(first == numOfProduct)
		{
			finalList[counter] = productListRec[seconde];
			seconde++;
			continue;
		}
		else if (seconde == numOfProductRec)
		{
			finalList[counter] = productList[first];
			first++;
			continue;
		}
		else
		{
			comperator = compar(productListRec[seconde], productList[first]);
			if(comperator < FALSE)
			{
				finalList[counter] = productListRec[seconde];
				seconde++;
			}
			else
			{
				finalList[counter] = productList[first];
				first++;
				if(! comperator)
				{
					finalList[counter].quantity += productListRec[seconde].quantity;
					seconde++;
				}
			}
		}
	}
	//loop for updating the original list
	for(first = FALSE; first < counter; first++)
	{
		productList[first] = finalList[first];
	}
	return first;
}

/**
 * Function for clean application. Gets a list of product that in the garage, and a date.
 * The function delete all the product that older than that date, and return the update of the
 * list of product that in the garage.
 */
int clean(int month, int year, Product* productList, int numOfProduct)
{
	int ignorYear = TRUE, ignorMonth = TRUE, temp, counter = FALSE;
	if (year == FALSE)
	{
		ignorYear = FALSE;
	}
	if (month == FALSE)
	{
		ignorMonth = FALSE;
	}
	for(temp = FALSE; temp < numOfProduct; temp++)
	{
		if(productList[temp].quantity <= LIM_ACURRATE)
		{
			productList[temp].barkod = END_LIST;
			counter++;
		}
		if (ignorYear)
		{
			if (productList[temp].year < year)
			{
				productList[temp].barkod = END_LIST;
				counter++;
			}
			else if (productList[temp].year == year && productList[temp].month < month && \
					 ignorMonth)
			{
				productList[temp].barkod = END_LIST;
				counter++;
			}
		}
	}
	sortArry(productList, numOfProduct);
	numOfProduct -= counter;
	return numOfProduct;
}

/**
 * Main function for the program. Check validation of the input, build the array to send to the
 *  different function, sort the list, call the right function for 'clean'
 *  'received' or 'sent' and in the end write the update on the file.
 */
int main(int argc, char* argv[])
{
	if(!(strcmp(argv[2], "sent") || strcmp(argv[2], "received") || strcmp(argv[2], "clean")) || \
	   argc!= COMMEND)
	{
		printf("USAGE: waredb <db file> <command> <command arg file>\n");
		return EXIT;
	}
	int numOfProduct, numOfProductRec;
	FILE* file = fopen(argv[1], "r");
	if(file == NULL)
	{
		if((!strcmp(argv[2], "sent") || !strcmp(argv[2], "received") ))
		{
			FILE* chek = fopen(argv[3], "r");
			if(chek == NULL)
			{
				printf("%s", argv[1]);
				return EXIT;
			}
		}
		printf("%s: no such file\n", argv[1]);
		return EXIT;
	}
	Product productList[NEW_ARRY_MAX];
	numOfProduct = openFileToProduct(file, productList);
	fclose(file);
	if(numOfProduct == GO_OUT)
	{
		printf("unknown file format\n");
		return EXIT;
	}
	sortArry(productList, numOfProduct);
	if(!strcmp(argv[2], "clean"))
	{
		//split the input for year and month
		int year, month;
		sscanf(argv[3], "%d-%d", &year, &month);
		if(month < FALSE || month > END_YEAR || year < FALSE)
		{
			printf("USAGE: waredb <db file> <command> <command arg file>\n");
			return EXIT_FAILURE;
		}
		numOfProduct = clean(month, year, productList, numOfProduct);
	}
	else if(!strcmp(argv[2], "received") || (!strcmp(argv[2], "sent")))
	{
		FILE* secondFile = fopen(argv[3], "r");
		if(secondFile == NULL)
		{
			printf("%s: no such file\n", argv[1]);
			return EXIT_FAILURE;
		}
		if(!strcmp(argv[2], "received"))
		{
			Product newProductList[NEW_ARRY_MAX];
			numOfProductRec = openFileToProduct(secondFile, newProductList);
			if(numOfProductRec == GO_OUT)
			{
				printf("unknown file format\n");
				return EXIT_FAILURE;
			}
			sortArry(newProductList, numOfProductRec);
			numOfProduct = received(productList, numOfProduct , newProductList , numOfProductRec);
		}
		else if (!strcmp(argv[2], "sent"))
		{
			Sent sentList[NEW_ARRY_MAX];
			numOfProductRec = createSentArray(secondFile, sentList);
			if(numOfProductRec == GO_OUT)
			{
				printf("unknown file format\n");
				return EXIT_FAILURE;
			}
			sent( productList, numOfProduct, sentList, numOfProductRec);
			numOfProduct = clean(FALSE, FALSE, productList, numOfProduct);
		}
	}
	//write back on the file the new update of the list
	return (writeProductToFile(productList, numOfProduct, argv[1]));
}
