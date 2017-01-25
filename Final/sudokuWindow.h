#pragma once
#include "Data.h"
#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qtextedit.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#define SIZE 9

class sudokuWindow : public QDialog
{
	Q_OBJECT

public:
	sudokuWindow(Data *d);
	~sudokuWindow();
	Data *h;
private:
	
	void handleHint(int i, int j);
	void handleQuit();
	void prepareWindow();
	void handleSolve();
	void handleText(int i, int j);
	
	
	QGroupBox *sudokuBoxes[SIZE][SIZE];
	QHBoxLayout *sudokuLayouts[SIZE][SIZE];
	QTextEdit *fields[SIZE][SIZE];
	QPushButton *buttons[SIZE][SIZE];
	QLabel *imageOrgLabel;
	QLabel *imagePosLabel;
	QGroupBox *imageBar;
	QGroupBox *sudokuBox;
	QGroupBox *buttonBox;
	QVBoxLayout *buttonsLayout;
	QGridLayout *mainLayout;
	QGridLayout *sudokuLayout;
	QPushButton *solveButton;
	QPushButton *quitButton;

};
