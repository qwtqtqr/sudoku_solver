#include <stdio.h>
#include "sudoku.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

static FILE* Infile = NULL;
struct field* sudoku[9][9];


static int next(void)
{
	int c;
	c = fgetc(Infile);
	return c;
}


static int c_isDigit(int c)
{
	for (int i = 0; i < 10; i++)
	{
		int curDigit = '0' + i;
		if (c == curDigit)
		{
			return 1;
		}
	}
	return 0;
}

static int skip(void)
{
	int c;

	c = next();
	while (c_isDigit(c) == 0)
	{
		c = next();
	}
	return c;
}

static int getDigit(int c)
{
	return (c - '0');
}

static int nextNum()
{
	int c = skip();
	return getDigit(c);
}


void init_sudoku()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int fieldVal = nextNum();
			int init = 0;
			if (fieldVal > 0)
			{
				init = 1;
			}
			sudoku[j][i] = newField(fieldVal, init);
		}
	}
}

static void print_sudoku()
{
	printf("\n\n\n\n");
	printf("                  ");
	for (int c = 0; c < 24; c++)
	{
		printf("_");
		if (c == 23)
		{
			printf("\n");
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			
			struct field* curField = sudoku[j][i];

			if (j == 0)
			{
				printf("                  | %d", curField->fieldVal);
			}
			else if (j < 8)
			{
				if (j == 2 || j == 5)
				{
					printf(" %d |", curField->fieldVal);
				}
				else
				{
					printf(" %d", curField->fieldVal);
				}

			}

			if (j == 8)
			{
				printf(" %d|\n", curField->fieldVal);
				if (i == 2 || i == 5)
				{
					printf("                  ");
					for (int l = 0; l < 24; l++)
					{
						if (l == 0 || l == 8 || l == 16)
						{
							printf("|");
						}
						else if (l == 23)
						{
							printf("|\n");
						}
						else
						{
							printf("_");
						}
					}
				}
			}
		}
	}
	printf("                  ");
	for (int c = 0; c < 24; c++)
	{
		if (c == 23)
		{
			printf("|\n");
		}
		else if (c == 0)
		{
			printf("|");
		}
		else
		{
			printf("_");
		}
	}
	printf("\n\n\n\n");
}

static void checkErrors()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			struct field* curField = sudoku[j][i];

			if (curField->fieldVal > 0)
			{
				int error = numIsPossib(curField->fieldVal, j, i);
				if (error == 0)
				{
					printf("[ERROR] sudoku cannot be solved!\n");
					exit(1);
				}
			}
		}
	}
}

int main()
{

	char* fileName = "sudoku.txt";
	Infile = fopen(fileName, "r");

	if (Infile == NULL)
	{
		printf("[ERROR] could not open '%s'\n", fileName);
		exit(1);
	}

	init_sudoku();
	checkErrors();
	for (int i = 1; i <= 9; i++)
	{
		int retNum = solve_sudoku(0, 0, 1, i);
		if (retNum == 1)
		{
			break;
		}
		if (i == 9 && retNum == 0)
		{
			printf("[ERROR] sudoku cannot be solved!\n");
			exit(1);
		}
	}
	
	print_sudoku();

	return 0;
}