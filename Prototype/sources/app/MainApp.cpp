#include "Sudoku1.h"
#include "SudokuMatrix.h"
#include "TrainAndTest.h"
#include "Sudoku.h"
#include "gui.h"
#include <iostream>
#include <QApplication>

#define SIZE 9
#define UNASSIGNED 0
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	ContourWithData cwd;
	Sudoku s;
	SudokuMatrix result;
	SudokuMatrix scanned;
	SudokuRead sr;

	sr.go();
	scanned = cwd.getScan();

	if (s.solveSudoku(scanned)) {
		result = s.getResult(scanned);
	}
	GUI dialog = GUI(scanned, result);

	dialog.show();

	return app.exec();
}