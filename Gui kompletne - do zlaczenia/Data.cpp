#include <Data.h>
Data::Data() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			org[i][j] = 0;
			solved[i][j] = 0;
		}
	}
}

Data::Data(int tabOrg[SIZE][SIZE], int tabSolved[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			org[i][j] = tabOrg[i][j];
			solved[i][j] = tabSolved[i][j];
		}
	}
}

int Data::getOrgVal(int i, int j) {
	return org[i][j];
}
int Data::getSolved(int i, int j) {
	return solved[i][j];
}

void Data::setSolved(int tab[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			solved[i][j] = tab[i][j];
		}
	}
}

void Data::setOrg(int tab[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			org[i][j] = tab[i][j];
		}
	}
}

void Data::setSolvedVal(int i, int j, int val) {
	solved[i][j] = val;
}

void Data::setOrgVal(int i, int j, int val) {
	org[i][j] = val;
}
