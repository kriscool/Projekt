#pragma once 

#include <QtWidgets/QMainWindow>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qgroupbox.h>
#include <qlayout.h>
#include <qdialog.h>
#include <qlabel.h>
#include <string>
#include "Data.h"
#include "sudokuWindow.h"

class PictureView : public QDialog
{
	Q_OBJECT

public:
	PictureView();
	void pictureViewShow();
	std::string loadFromFile();
	void openFile(QString &path);
	~PictureView();
	

	private slots:
	void continueHandler(Data *h);
	void backHandler();


private:



	QPushButton *buttonContinue;
	QPushButton *buttonBack;
	QGroupBox *pictureShowBox;
	QGroupBox *buttonShowBox;
	QGroupBox *groupBox2;


	
	QLabel *label;
	QLabel *label2;
	QImageReader *reader;
	QPixmap *image;
	QPixmap *imagewycinka;
	QHBoxLayout *pictureShowLayout;
	QHBoxLayout *buttonShowLayout;
	QGridLayout *mainlayout;


};

