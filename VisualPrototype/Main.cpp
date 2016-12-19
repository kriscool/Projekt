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
			wypelnij(macierzIN[i - 1]);
			cout << macierzIN[i-1] << " ";
			if (i % 9 == 0) {
				cout << "\n";
			}
	}

	solve();
	
	getchar();

	return 0;
}