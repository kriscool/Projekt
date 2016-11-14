/*
 * Sudoku.h
 *
 *  Created on: 06.11.2016
 *      Author: Admin
 */
#include "SudokuMatrix.h"
#include "conio.h"
#ifndef SUDOKU_H_
#define SUDOKU_H_
#define UNASSIGNED 0
#define SIZE 9


class Sudoku {
public:
	static SudokuMatrix sudokuMat;

	bool solveSudoku(SudokuMatrix* sudokuMat);
	void printGrid(SudokuMatrix* sudokuMat);
	Sudoku();
	virtual ~Sudoku();

private:
	bool findUnassignedLocation(SudokuMatrix* sudokuMat, int &row, int &col);
	bool usedInRow(SudokuMatrix* sudokuMat, int row, int num);
	bool usedInCol(SudokuMatrix* sudokuMat, int col, int num);
	bool usedInBox(SudokuMatrix* sudokuMat, int boxStartRow, int boxStartCol, int num);
	bool isSafe(SudokuMatrix* sudokuMat, int row, int col, int num);
};

#endif /* SUDOKU_H_ */
