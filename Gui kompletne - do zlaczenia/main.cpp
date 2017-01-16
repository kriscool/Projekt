#include "gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	gui w;
	w.show();
	return app.exec();
}
