#pragma once
#define SIZE 9
class Data {
public:
	Data();
	Data(int tabOrg[SIZE][SIZE], int tabSolved[SIZE][SIZE]);

	void setOrg(int tab [SIZE][SIZE]);
	void setSolved(int tab [SIZE][SIZE]);
	int getOrgVal(int i, int j);
	int getSolved(int i, int j);
	void setOrgVal(int i, int j, int val);
	void setSolvedVal(int i, int j, int val);
private:
	int org[SIZE][SIZE];
	int solved[SIZE][SIZE];
};