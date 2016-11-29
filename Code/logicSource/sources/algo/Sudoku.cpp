#include "Sudoku.h"
#include "SudokuMatrix.h"
#include <iostream>
#define SIZE 9
#define UNASSIGNED 0

Sudoku::Sudoku() {
	this->sudokuMat = SudokuMatrix();
}

Sudoku::Sudoku(int tab[SIZE][SIZE]) {
	this->sudokuMat = SudokuMatrix(tab);
}


bool Sudoku::solveSudoku(SudokuMatrix &sudokuMat) {
	int row, col;
	if (!findUnassignedLocation(sudokuMat, row, col))
		return true;
	for (int num = 1; num <= 9; num++)
	{
		if (isSafe(sudokuMat, row, col, num))
		{
			sudokuMat.matrix[row][col] = num;
			if (solveSudoku(sudokuMat))
				return true;
			sudokuMat.matrix[row][col] = UNASSIGNED;
		}
	}
	return false;
}

bool Sudoku::findUnassignedLocation(SudokuMatrix &sudokuMat, int &row, int &col) {
	for (row = 0; row < SIZE; row++)
		for (col = 0; col < SIZE; col++)
			if (sudokuMat.matrix[row][col] == UNASSIGNED)
				return true;
	return false;
}

bool Sudoku::usedInRow(SudokuMatrix &sudokuMat, int row, int num) {
	for (int col = 0; col <SIZE; col++)
		if (sudokuMat.matrix[row][col] == num)
			return true;
	return false;
}
bool Sudoku::usedInCol(SudokuMatrix &sudokuMat, int col, int num) {
	for (int row = 0; row < SIZE; row++)
		if (sudokuMat.matrix[row][col] == num)
			return true;
	return false;
}
bool Sudoku::usedInBox(SudokuMatrix &sudokuMat, int boxStartRow, int boxStartCol, int num) {
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (sudokuMat.matrix[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}
bool Sudoku::isSafe(SudokuMatrix &sudokuMat, int row, int col, int num) {
	return !usedInRow(sudokuMat, row, num) && !usedInCol(sudokuMat, col, num) &&
		!usedInBox(sudokuMat, row - row % 3, col - col % 3, num);
}

void Sudoku::printGrid(SudokuMatrix &sudokuMat) {
	int col, row;
	for (row = 0; row < SIZE; row++) {
		for (col = 0; col < SIZE; col++) {
			if (col == 3 || col == 6) {
				std::cout << "   ";
			}
			std::cout << sudokuMat.matrix[row][col] << "  ";
		}
		if (row == 2 || row == 5) {
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}