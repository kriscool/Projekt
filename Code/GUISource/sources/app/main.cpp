#include <QApplication>
#include "gui.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	GUI dialog;
	dialog.show();

	return app.exec();
}
