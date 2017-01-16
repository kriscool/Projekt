#include "sudokuWindow.h"

sudokuWindow::sudokuWindow(Data *d)
{
	
	h = new Data();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			h->setSolvedVal(i,j, d->getSolved(i, j));
			h->setOrgVal(i, j, d->getOrgVal(i, j));
		}
	}

	prepareWindow();

}

sudokuWindow::~sudokuWindow()
{

}

void sudokuWindow::prepareWindow() {

	mainLayout = new QGridLayout();
	sudokuLayout = new QGridLayout();
	buttonsLayout = new QVBoxLayout();

	buttonBox = new QGroupBox(tr("Controls"));
	sudokuBox = new QGroupBox(tr("Sudoku"));
	imageBar = new QGroupBox(tr("Image view"));

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int x = h->getOrgVal(i,j);
			sudokuBoxes[i][j] = new QGroupBox();
			sudokuLayouts[i][j] = new QHBoxLayout();
			buttons[i][j] = new QPushButton("Hint");
			fields[i][j] = new QTextEdit();
			if (x != 0) {
				QString n = QString::number(x);
				fields[i][j]->setText(n);
				fields[i][j]->setStyleSheet("QTextEdit { background-color: rgb(0, 255, 0) }");
				fields[i][j]->setReadOnly(true);
				buttons[i][j]->setDisabled(true);
			}
			else {

			}
			fields[i][j]->setMaximumSize(40, 25);
			fields[i][j]->setFontWeight(5);
			sudokuLayouts[i][j]->addWidget(fields[i][j]);
			sudokuLayouts[i][j]->addWidget(buttons[i][j]);
			sudokuBoxes[i][j]->setLayout(sudokuLayouts[i][j]);
			connect(buttons[i][j], &QPushButton::clicked, this, [=] {handleHint(i, j); });
			connect(fields[i][j], &QTextEdit::textChanged, this, [=] {handleText(i,j); });
			sudokuLayout->addWidget(sudokuBoxes[i][j], i, j);
		}
	}
	
	

	quitButton = new QPushButton("Quit");
	solveButton = new QPushButton("Solve");
	connect(quitButton, &QPushButton::clicked, this, &sudokuWindow::handleQuit);
	connect(solveButton, &QPushButton::clicked, this, &sudokuWindow::handleSolve);
	buttonsLayout->addWidget(quitButton);
	buttonsLayout->addWidget(solveButton);

	sudokuBox->setLayout(sudokuLayout);
	buttonBox->setLayout(buttonsLayout);
	mainLayout->addWidget(sudokuBox, 0, 0);
	mainLayout->addWidget(buttonBox, 1, 0);
	this->setLayout(mainLayout);

	
}

void sudokuWindow::handleHint(int i, int j) {
	QString str = QString::number(h->getSolved(i,j));
	fields[i][j]->setText(str);
	buttons[i][j]->setDisabled(true);
}



void sudokuWindow::handleSolve() {
	for (int i=0; i < SIZE; i++) {
		for (int j=0; j < SIZE; j++) {
			QString str = QString::number(h->getSolved(i, j));
			fields[i][j]->setText(str);
			buttons[i][j]->setDisabled(true);
		}
	}
}

void sudokuWindow::handleQuit() {
	this->close();
}

void sudokuWindow::handleText(int i, int j) {
	char *p;
	std::string src = fields[i][j]->toPlainText().toStdString();
	int fieldInt = std::strtol(src.c_str(), &p, 10);
	if (*p || src == ""){
		
	}
	else {
		int fieldInt = stoi(fields[i][j]->toPlainText().toStdString());
		int solvedInt = h->getSolved(i, j);
		if (fieldInt != solvedInt) {
			fields[i][j]->setStyleSheet("QTextEdit { background-color: rgb(255, 0, 0) }");
		}
		else {
			fields[i][j]->setStyleSheet("QTextEdit { background-color: rgb(0, 255, 0) }");
			fields[i][j]->setReadOnly(true);
		}
	}
	
}
