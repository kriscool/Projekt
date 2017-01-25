#ifndef FINAL_H
#define FINAL_H

#include <QtWidgets/QMainWindow>
#include "ui_final.h"

class Final : public QMainWindow
{
	Q_OBJECT

public:
	Final(QWidget *parent = 0);
	~Final();

private:
	Ui::FinalClass ui;
};

#endif // FINAL_H
