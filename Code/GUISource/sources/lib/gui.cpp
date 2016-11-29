#include "gui.h"

GUI::GUI(){

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

	createGridGroupBox(grid);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(gridGroupBox);
	setLayout(mainLayout);
}

void GUI::createGridGroupBox(int tab[SIZE][SIZE]){
	gridGroupBox = new QGroupBox(tr("Sudoku matrix"));
	QGridLayout *layout = new QGridLayout;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			buttons[i][j] = new QPushButton(tr("%1").arg(tab[i][j]));
			buttons[i][j]->setFixedSize(50,50);
			layout->addWidget(buttons[i][j], i, j);
			layout->setColumnStretch(i, 10);
			layout->setRowStretch(j, 10);
		}
	}
	gridGroupBox->setLayout(layout);
}
