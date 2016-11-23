/*
 * SudokuMatrix.h
 *
 *  Created on: 14.11.2016
 *      Author: Admin
 */

#pragma once
#define SIZE 9

class SudokuMatrix {

public:
	int matrix[SIZE][SIZE];

	SudokuMatrix();
	SudokuMatrix(int tab[SIZE][SIZE]);
};

