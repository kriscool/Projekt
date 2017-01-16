#include "gui.h"
#include <qlayout.h>
#include <qcoreapplication.h>
#include <qfiledialog.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <qimagereader.h>
#include "pictureview.h"
#include "sudokuWindow.h"

PictureView::PictureView()
{
	
	pictureViewShow();


}

PictureView::~PictureView()
{

}

void PictureView::pictureViewShow() {
	pictureShowBox = new QGroupBox(tr("Picture Show"));
	buttonShowBox = new QGroupBox(tr("Controls"));


	//pictureShowBox->setFixedSize(800, 350);
	buttonShowBox->setFixedSize(780, 55);

	this->setMaximumSize(800, 450);
	this->setMinimumSize(800, 450);

	pictureShowLayout = new QHBoxLayout;
	buttonShowLayout = new QHBoxLayout;
	mainlayout = new QGridLayout;
	
	label = new QLabel(tr(" sdsd "));

	buttonContinue = new QPushButton(tr("Continue"));
	//button->setFixedSize(150, 50);
	buttonBack = new QPushButton(tr("Back"));
	//button2->setFixedSize(150, 50);

	buttonShowLayout->addWidget(buttonContinue);
	buttonShowLayout->addWidget(buttonBack);

	pictureShowLayout->addWidget(label);

	pictureShowBox->setLayout(pictureShowLayout);
	buttonShowBox->setLayout(buttonShowLayout);
	mainlayout->addWidget(pictureShowBox, 0, 0);
	mainlayout->addWidget(buttonShowBox, 1, 0);
	setLayout(mainlayout);
	//pictureShowBox->setParent(this);
	loadFromFile();

	int tab[SIZE][SIZE] = {
		{ 0,1,2,3,4,5,6,7,8 },
		{ 0,1,2,3,4,5,6,7,8 },
		{ 0,1,2,3,4,5,6,7,8 },
		{ 0,1,2,3,4,5,6,7,8 },
		{ 0,1,2,3,4,5,6,7,8 },
		{ 0,1,2,3,4,5,6,7,8 },
		{ 0,1,2,3,4,5,6,7,8 },
		{ 0,1,2,3,4,5,6,7,8 },
		{ 0,1,2,3,4,5,6,7,8 } };

	int tabs[SIZE][SIZE] = {
		{ 9,1,2,3,4,5,6,7,8 },
		{ 9,1,2,3,4,5,6,7,8 },
		{ 9,1,2,3,4,5,6,7,8 },
		{ 9,1,2,3,4,5,6,7,8 },
		{ 9,1,2,3,4,5,6,7,8 },
		{ 9,1,2,3,4,5,6,7,8 },
		{ 9,1,2,3,4,5,6,7,8 },
		{ 9,1,2,3,4,5,6,7,8 },
		{ 9,1,2,3,4,5,6,7,8 } };

	Data *h = new Data();
	h->setSolved(tabs);
	h->setOrg(tab);

	connect(buttonBack, SIGNAL(released()), this, SLOT(backHandler()));
	connect(buttonContinue, &QPushButton::clicked, this, [=] {continueHandler(h); });



}

std::string PictureView::loadFromFile() {

	QString name = QFileDialog::getOpenFileName(this,
		tr("Open image"), "",
		tr("Image Files (*.png ; *.jpg);;All Files (*)"));
	openFile(name);
	return name.toStdString();
}

void PictureView::openFile(QString &path) {

	image = new QPixmap(path);
	int x = 250;
	int y = 200;
	this->label->setMaximumSize(x, y);
	this->label->setMinimumSize(x, y);
	//label2->setMaximumSize(x, y);
	//label2->setMinimumSize(x, y);


	label->setScaledContents(true);
	//	label2->setScaledContents(true);
	label->setPixmap(*(image));
	//label2->setPixmap(*(image));
}

void PictureView::continueHandler(Data *h) {

	sudokuWindow *w = new sudokuWindow(h);
	w->setModal(true);
	w->exec();
	this->close();
}

void PictureView::backHandler() {

	this->close();
}