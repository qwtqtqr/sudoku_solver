#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SUDOKU_SIZE 81


struct field
{
	int fieldVal;
	int init;
};

extern struct field* sudoku[9][9];

int solve_sudoku(int i, int j, int location, int num);
struct field* newField(int fieldVal, int init);
int numIsPossib(int num, int j, int i);

#endif