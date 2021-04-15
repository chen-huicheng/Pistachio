#include<vector>
#include<string>
#include<iostream>
#include <conio.h>
#include<windows.h>
#include "Display.h"
using namespace std;

#ifndef __DISPLAY_BY_CMD
#define __DISPLAY_BY_CMD

class DisplayByCmd :public Display {
public:
	DisplayByCmd(int len);
	virtual void show();
	virtual void move(int x, int y);//ÉÏÏÂ×óÓÒ  -1 0   +1 0   0 -1   0 +1 
	virtual void put(int player);// player  1  ºÚ  2 °×
	virtual void back();
private:
	void printAtXY(int x, int y, string str);
	void setCursorPosition(short int x, short int y);
	string getCurse(int i, int j);
	string getStyle(int i, int j);
	void Initialize();
	int length;
	int Cx, Cy;
};
#endif // !__DISPLAY_BY_CMD

