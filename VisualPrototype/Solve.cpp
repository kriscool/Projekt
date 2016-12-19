#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Header.h"
using namespace std;
#define UNASSIGNED 0
#define N 9
int grid[9][9];
int gridTemp[81];
bool FindUnassignedLocation(int grid[N][N], int &row, int &col);
bool isSafe(int grid[N][N], int row, int col, int num);

/* assign values to all unassigned locations for Sudoku solution
*/
bool SolveSudoku(int grid[N][N])
{
	int row, col;
	if (!FindUnassignedLocation(grid, row, col))
		return true;
	for (int num = 1; num <= 9; num++)
	{
		if (isSafe(grid, row, col, num))
		{
			grid[row][col] = num;
			if (SolveSudoku(grid))
				return true;
			grid[row][col] = UNASSIGNED;
		}
	}
	return false;
}

/* Searches the grid to find an entry that is still unassigned. */
bool FindUnassignedLocation(int grid[N][N], int &row, int &col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}

/* Returns whether any assigned entry n the specified row matches
the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

/* Returns whether any assigned entry in the specified column matches
the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches
the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}

/* Returns whether it will be legal to assign num to the given row,col location.
*/
bool isSafe(int grid[N][N], int row, int col, int num)
{
	return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
		!UsedInBox(grid, row - row % 3, col - col % 3, num);
}

void printGrid(int grid[N][N])
{
	int col, row;
	for (row = 0; row < N; row++) {
		for (col = 0; col < N; col++) {
			if (col == 3 || col == 6) {
				cout << "   ";
			}
			cout << grid[row][col] << "  ";
		}
		if (row == 2 || row == 5) {
			cout << endl;
		}
		cout << endl;
	}
}

int i = 0;

void wypelnij(int a) {
	gridTemp[i] = a;
	i++;
}

void rozpisz() {
	for (int w = 0; w < 9; w++) {
		for (int k = 0; k < 9; k++) {
			grid[w][k] = gridTemp[w * 9 + k];
		}
	}
}


void rozbij() {
	for (int w = 0; w < 9; w++) {
		for (int k = 0; k < 9; k++) {
			gridTemp[w * 9 + k] = grid[w][k];
		}
	}
}

void solve()
{

	rozpisz();
	if (SolveSudoku(grid) == true) {
		rozbij();
		cout << " Good " << endl;
	}
	else
		cout << "No solution exists" << endl;
	cin.get();
}





int przekaz(int index) {
	int des = gridTemp[index];
	return des;
}