#include "Header.h"
#include <iostream>

using namespace std;

int main()
{
	int macierzIN[81];
	int macierzIN2[9][9];
	int macierzOUT[81];
	zapis();
	for (int i = 1; i <82; i++) {
			macierzIN[i-1] = push(i);
			cout << macierzIN[i-1] << " ";
			if (i % 9 == 0) {
				cout << "\n";
			}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			macierzIN2[i][j] = macierzIN[i * 9 + j];
		}
	}
	solve(macierzIN2);
	getchar();

	return 0;
}