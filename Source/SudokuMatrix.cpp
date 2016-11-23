/*
 * SudokuMatrix.cpp
 *
 *  Created on: 14.11.2016
 *      Author: Admin
 */

#include "SudokuMatrix.h"
#define SIZE 9

SudokuMatrix::SudokuMatrix() {
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			this->matrix[i][j] = 0;
		}
	}
}

SudokuMatrix::SudokuMatrix(int tab[9][9]){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			this->matrix[i][j] = tab[i][j];
		}
	}
}


