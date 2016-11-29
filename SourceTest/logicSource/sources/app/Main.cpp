#include "../algo/Sudoku/Sudoku.h"
#include "../algo/SudokuMatrix/SudokuMatrix.h"
#include <iostream>
#define SIZE 9
#define UNASSIGNED 0

int main() {
	int grid[SIZE][SIZE] = {
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

	Sudoku su(grid);

	if (su.solveSudoku(su.sudokuMat)) {
		su.printGrid(su.sudokuMat);
		std::cout << " Good " << std::endl;
	}
	else
		std::cout << "No solution exists" << std::endl;
	std::cin.get();
	return 0;
}