#include "SudokuMatrix.h"
#define SIZE 9

SudokuMatrix::SudokuMatrix() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			this->matrix[i][j] = 0;
		}
	}
}

SudokuMatrix::SudokuMatrix(int tab[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			this->matrix[i][j] = tab[i][j];
		}
	}
}