#pragma once 

#include <QtWidgets/QMainWindow>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qgroupbox.h>
#include <qlayout.h>
#include <qdialog.h>
#include <qlabel.h>
#include <string>


class gui : public QDialog
{
	Q_OBJECT

public:
	gui();
	void guishow();
	void nextWindow();
	~gui();
	

private slots:
	void handleClose();
	void handleNextWindow();


private:


	QPushButton *buttonNextWindow;
	QPushButton *buttonClose;
	QGroupBox *groupBox;
	QGroupBox *mainBox;
	QGroupBox *groupBox2;


	QVBoxLayout *vlayout;
	QLabel *label;
	QLabel *label2;
	QImageReader *reader;
	QPixmap *image;
	QHBoxLayout *layout;
	QGridLayout *mainlayout;


};

