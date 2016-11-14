/*
 * Sudoku.cpp
 *
 *  Created on: 06.11.2016
 *      Author: Admin
 */

#include "Sudoku.h"
#include "SudokuMatrix.h"
#include <iostream>
using namespace std;


Sudoku::Sudoku() {
	// TODO Auto-generated constructor stub

}

Sudoku::~Sudoku() {
	// TODO Auto-generated destructor stub
}



bool Sudoku::solveSudoku(SudokuMatrix* sudokuMat){
	int row, col;
	if (!findUnassignedLocation(sudokuMat, row, col))
		return true;
	for (int num = 1; num <= 9; num++)
	{
		if (isSafe(sudokuMat, row, col, num))
		{
			sudokuMat->matrix[row][col] = num;
			if (solveSudoku(sudokuMat))
				return true;
			sudokuMat->matrix[row][col] = UNASSIGNED;
		}
	}
	return false;
}

bool Sudoku::findUnassignedLocation(SudokuMatrix* sudokuMat, int &row, int &col){
	for (row = 0; row < sudokuMat->size; row++)
		for (col = 0; col < sudokuMat->size; col++)
			if (sudokuMat->matrix[row][col] == UNASSIGNED)
				return true;
	return false;
}

bool Sudoku::usedInRow(SudokuMatrix* sudokuMat, int row, int num){
	for (int col = 0; col < sudokuMat->size; col++)
		if (sudokuMat->matrix[row][col] == num)
			return true;
	return false;
}
bool Sudoku::usedInCol(SudokuMatrix* sudokuMat, int col, int num){
	for (int row = 0; row < sudokuMat->size; row++)
		if (sudokuMat->matrix[row][col] == num)
			return true;
	return false;
}
bool Sudoku::usedInBox(SudokuMatrix* sudokuMat, int boxStartRow, int boxStartCol, int num){
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (sudokuMat->matrix[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}
bool Sudoku::isSafe(SudokuMatrix *sudokuMat, int row, int col, int num){
	return !usedInRow(sudokuMat, row, num) && !usedInCol(sudokuMat, col, num) &&
		!usedInBox(sudokuMat, row - row % 3, col - col % 3, num);
}

void Sudoku::printGrid(SudokuMatrix* sudokuMat){
	int col, row;
	for ( row = 0; row < sudokuMat->size; row++) {
		for (col = 0; col < sudokuMat->size; col++) {
			if (col == 3 || col == 6) {
				std::cout << "   ";
			}
			cout << sudokuMat->matrix[row][col] << "  ";
		}
		if (row == 2 || row == 5) {
			cout << endl;
		}
		cout << endl;
	}
}

int main(){
	int size = 9;
	int grid[9][9] = {
		{ 3, 0, 0, 2, 4, 0, 0, 6, 0 },
		{ 0, 4, 0, 0, 0, 0, 0, 5, 3 },
		{ 1, 8, 9, 6, 3, 5, 4, 0, 0 },
		{ 0, 0, 0, 0, 8, 0, 2, 0, 0 },
		{ 0, 0, 7, 4, 9, 6, 8, 0, 1 },
		{ 8, 9, 3, 1, 5, 0, 6, 0, 4 },
		{ 0, 0, 1, 9, 2, 0, 5, 0, 0 },
		{ 2, 0, 0, 3, 0, 0, 7, 4, 0 },
		{ 9, 6, 0, 5, 0, 0, 3, 0, 2 }
		};

	SudokuMatrix mat (size, grid);
	SudokuMatrix* pmat;
	pmat = &mat;
	Sudoku su;

		if (su.solveSudoku(pmat)) {
			su.printGrid(pmat);
			std::cout << " Good " << endl;
		}
		else
			std::cout << "No solution exists" << endl;
		std::cin.get();
		return 0;
}
