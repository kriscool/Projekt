#include <QtWidgets>
#include <QDialog>
#include "SudokuMatrix.h"

#define SIZE 9

class GUI : public QDialog
{
	Q_OBJECT;

public:
	GUI(SudokuMatrix scanned, SudokuMatrix result);

private:
	void createGridGroupBox(SudokuMatrix scanned, SudokuMatrix result);
	void handleButton(int i, int j, int x);
	QGroupBox *gridGroupBox;
	QPushButton *buttons[SIZE][SIZE];
};

