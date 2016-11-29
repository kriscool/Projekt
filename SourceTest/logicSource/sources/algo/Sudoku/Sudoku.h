#include "../SudokuMatrix/SudokuMatrix.h"
#pragma once
#define SIZE 9

class Sudoku {
public:
	SudokuMatrix sudokuMat;
	bool solveSudoku(SudokuMatrix &sudokuMat);
	void printGrid(SudokuMatrix &sudokuMat);
	Sudoku(int tab[SIZE][SIZE]);
	Sudoku();

private:
	bool findUnassignedLocation(SudokuMatrix &sudokuMat, int &row, int &col);
	bool usedInRow(SudokuMatrix &sudokuMat, int row, int num);
	bool usedInCol(SudokuMatrix &sudokuMat, int col, int num);
	bool usedInBox(SudokuMatrix &sudokuMat, int boxStartRow, int boxStartCol, int num);
	bool isSafe(SudokuMatrix &sudokuMat, int row, int col, int num);
};