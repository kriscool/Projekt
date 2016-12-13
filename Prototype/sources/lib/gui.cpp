#include "gui.h"

GUI::GUI(SudokuMatrix scanned, SudokuMatrix result){

	createGridGroupBox(scanned, result);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(gridGroupBox);
	setLayout(mainLayout);
}

void GUI::createGridGroupBox(SudokuMatrix scanned, SudokuMatrix result){
	gridGroupBox = new QGroupBox(tr("Sudoku matrix"));
	QGridLayout *layout = new QGridLayout;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			buttons[i][j] = new QPushButton(tr("%1").arg(scanned.matrix[i][j]));
			buttons[i][j]->setFixedSize(50,50);
			connect(buttons[i][j], SIGNAL(released()), this, SLOT(handleButton(i,j,result.matrix[i][j])));
			layout->addWidget(buttons[i][j], i, j);
			layout->setColumnStretch(i, 10);
			layout->setRowStretch(j, 10);
		}
	}
	gridGroupBox->setLayout(layout);
}

void GUI::handleButton(int i, int j, int x) {
	buttons[i][j]->setText(QString(x));
}