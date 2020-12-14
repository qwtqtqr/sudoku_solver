#include "sudoku.h"


struct field* newField(int fieldVal, int init)
{
	struct field* Field = malloc(sizeof(struct field));
	Field->fieldVal = fieldVal;
	Field->init = init;
	return Field;
}


int numIsPossib(int num, int j, int i)
{
	struct field* curField = sudoku[j][i];
	int offset_i = 0; 
	int offset_j = 0;
	if (i < 3)
	{
		offset_i = 0;
	}
	else if (i >= 3 && i < 6)
	{
		offset_i = 3;
	}
	else if (i >= 6 && i < 9)
	{
		offset_i = 6;
	}

	if (j < 3)
	{
		offset_j = 0;
	}
	else if (j >= 3 && j < 6)
	{
		offset_j = 3;
	}
	else if (j >= 6 && j < 9)
	{
		offset_j = 6;
	}

	for (int c = 0; c < 9; c++)
	{
		struct field* j_field = sudoku[j][c];  // col
		struct field* i_field = sudoku[c][i];   // row
		struct field* rect_field = sudoku[offset_j][offset_i];

		if (c < 3)
		{
			rect_field = sudoku[offset_j][offset_i + c];
		}
		else if (c >= 3 && c < 6)
		{
			rect_field = sudoku[offset_j + 1][offset_i + (c - 3)];
		}
		else if (c >= 6 && c < 9)
		{
			rect_field = sudoku[offset_j + 2][offset_i + (c - 6)];
		}

		if (((j_field->fieldVal) == num && j_field != curField )  ||  ((i_field->fieldVal) == num && i_field != curField)  ||  ((rect_field->fieldVal) == num && rect_field != curField))
		{
			return 0;
		}
	}
	return 1;
}



int solve_sudoku(int i, int j, int location, int num)
{
	int i_cpy = i;
	int j_cpy = j;
	int location_cpy = location;
	int num_cpy = num;

	struct field* curField = sudoku[j_cpy][i_cpy];
	while (curField->init == 1)
	{
		if (location_cpy == SUDOKU_SIZE)
		{
			return 1;
		}
		j_cpy++;
		if (j_cpy > 8)
		{
			i_cpy++;
			j_cpy = 0;
		}
		curField = sudoku[j_cpy][i_cpy];
		location_cpy++;
	}


	int possib = numIsPossib(num_cpy, j_cpy, i_cpy);
	int nextJ = j_cpy + 1;
	int nextI = i_cpy;
	if (nextJ > 8)
	{
		nextJ = 0;
		nextI++;
	}
	if (possib == 0)
	{
		return 0;
	}

	int solved = 0;
	if (possib == 1)
	{
		sudoku[j_cpy][i_cpy]->fieldVal = num_cpy;
		if (location_cpy == SUDOKU_SIZE)
		{
			sudoku[j_cpy][i_cpy]->fieldVal = num_cpy;
			return 1;
		}

		for (int c = 1; c <= 9; c++)
		{
			solved = solve_sudoku(nextI, nextJ, location_cpy + 1, c);
			if (solved == 1)
			{
				break;
			}
		}
	}
	if (solved == 0)
	{
		sudoku[j_cpy][i_cpy]->fieldVal = 0;
	}
	return solved;
}