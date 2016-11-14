/*
 * SudokuMatrix.h
 *
 *  Created on: 14.11.2016
 *      Author: Admin
 */

#ifndef SUDOKUMATRIX_H_
#define SUDOKUMATRIX_H_

class SudokuMatrix {

public:
	int size;
	int matrix[9][9];

	SudokuMatrix();
	SudokuMatrix(int size);
	SudokuMatrix(int tab[9][9]);
	SudokuMatrix(int size, int tab[9][9]);
	virtual ~SudokuMatrix();
};

#endif /* SUDOKUMATRIX_H_ */
