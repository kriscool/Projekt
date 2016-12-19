#include "gui.h"
#include <QtWidgets/QApplication>
#include "Header.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{	
	int macierzIN[81];
	int macierzIN2[9][9];
	int macierzOUT[81];
	int macierzOUT2[9][9];
	zapis();
	for (int i = 1; i <82; i++) {
		macierzIN[i - 1] = push(i);
		wypelnij(macierzIN[i - 1]);
		cout << macierzIN[i - 1] << " ";
		if (i % 9 == 0) {
			cout << "\n";
		}
	}

	solve();

	for (int i = 0; i < 81; i++) {
		macierzOUT[i] = przekaz(i);
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			macierzOUT2[i][j] = macierzOUT[i * 9 + j];
		}
	}

	QApplication app(argc, argv);
	GUI dialog;
	dialog.show();

	return app.exec();
}
