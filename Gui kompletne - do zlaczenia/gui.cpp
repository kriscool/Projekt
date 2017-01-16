#include "gui.h"
#include <qlayout.h>
#include <qcoreapplication.h>
#include <qfiledialog.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <qimagereader.h>
#include "pictureview.h"

gui::gui()
{
	guishow();
	
	

}

gui::~gui()
{

}

void gui::guishow() {
	groupBox = new QGroupBox(tr("SUDOKU"));
	
	groupBox->setFixedSize(800, 450);

	this->setMaximumSize(800, 450);
	this->setMinimumSize(800, 450);

	layout = new QHBoxLayout;

	buttonNextWindow = new QPushButton(tr("Play"));
	buttonNextWindow->setFixedSize(150, 50);
	buttonClose = new QPushButton(tr("Exit"));
	buttonClose->setFixedSize(150, 50);
	layout->addWidget(buttonNextWindow);
	layout->addWidget(buttonClose);

	groupBox->setLayout(layout);

	groupBox->setParent(this);
	connect(buttonClose, SIGNAL(released()), this, SLOT(handleClose()));
	connect(buttonNextWindow, SIGNAL(released()), this, SLOT(handleNextWindow()));
}



void gui::nextWindow() {
	
	
	PictureView pv;
	pv.setModal(true);
	pv.exec();

	
	
	
}
void gui::handleClose() {
	close();
}

void gui::handleNextWindow() {
	nextWindow();
}