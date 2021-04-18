#include<iostream>
#include <conio.h>
#include<cstdio>
#include<ctime>
#include<windows.h>
using namespace std;

class DisplayByCmd {
public:
	void printAtRowCol(int row, int col, const char c);
	void printAtRowCol(int row, int col, const string str);
	void printRow(int row, const string str);
	void end_display() {
		No_Cursor();
	}
private:
	void No_Cursor();
	void setCursorPosition(short int row, short int col);
};

void DisplayByCmd::printAtRowCol(int row, int col, const char c) {
	setCursorPosition(col, row);
	cout << c;
}
void DisplayByCmd::printAtRowCol(int row, int col, const string str)
{
	setCursorPosition(col, row);
	cout << str;
	No_Cursor();
}
void DisplayByCmd::printRow(int row, const string str)
{
	setCursorPosition(0, row);
	cout << str;
	No_Cursor();
}
void DisplayByCmd::No_Cursor()
{
	setCursorPosition(0, 91);
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = false;
	SetConsoleCursorInfo(hOut, &cci);

}
void DisplayByCmd::setCursorPosition(short int x, short int y) {
	HANDLE hOut;
	COORD pos = { x,y };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
#pragma once
