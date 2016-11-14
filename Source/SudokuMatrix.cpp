/*
 * SudokuMatrix.cpp
 *
 *  Created on: 14.11.2016
 *      Author: Admin
 */

#include "SudokuMatrix.h"

SudokuMatrix::SudokuMatrix() {
	// TODO Auto-generated constructor stub
	this->size = 9;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			this->matrix[i][j] = 0;
		}
	}
}

SudokuMatrix::SudokuMatrix(int size){
	this->size = size;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			this->matrix[i][j] = 0;
		}
	}
}

SudokuMatrix::SudokuMatrix(int tab[9][9]){
	this->size = 9;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			this->matrix[i][j] = tab[i][j];
		}
	}
}

SudokuMatrix::SudokuMatrix(int size, int tab[9][9]){
	this->size = size;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			this->matrix[i][j] = tab[i][j];
		}
	}
}

SudokuMatrix::~SudokuMatrix() {
	// TODO Auto-generated destructor stub

}

