#include <QtWidgets>
#include <QDialog>

#define SIZE 9

class GUI : public QDialog
{
	Q_OBJECT

public:
	GUI();

private:
	void createGridGroupBox(int tab[SIZE][SIZE]);

	QGroupBox *gridGroupBox;
	QPushButton *buttons[SIZE][SIZE];

};

