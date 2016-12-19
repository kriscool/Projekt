#include "gui.h"
#include "Header.h"
#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
GUI::GUI() {
	
	int macierzOUT[81];
	int grid[9][9];

	solve();

	for (int i = 0; i < 81; i++) {
		macierzOUT[i] = przekaz(i);
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			grid[i][j] = macierzOUT[i * 9 + j];
		}
	}

	createGridGroupBox(grid);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(gridGroupBox);
	setLayout(mainLayout);
}

void GUI::createGridGroupBox(int tab[SIZE][SIZE]) {
	gridGroupBox = new QGroupBox(tr("Sudoku matrix"));
	QGridLayout *layout = new QGridLayout;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			buttons[i][j] = new QPushButton(tr("%1").arg(tab[i][j]));
			buttons[i][j]->setFixedSize(50, 50);
			layout->addWidget(buttons[i][j], i, j);
			layout->setColumnStretch(i, 10);
			layout->setRowStretch(j, 10);
		}
	}
	gridGroupBox->setLayout(layout);
}
