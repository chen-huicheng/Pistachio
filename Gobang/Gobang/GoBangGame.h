#include "Game.h"
#include "Display.h"
#include "DisplayByCmd.h"
#include <vector>
#include <memory>
#include <time.h>
using namespace std;

#ifndef _ManMachineGame
#define _ManMachineGame	1
const int LENGTH = 19;
class GoBangGame :public Game {
public:
	virtual void run();
	bool judge(int player);
	GoBangGame();
	GoBangGame(int len);
	~GoBangGame() {
	}
private:
	void mode1();
	void mode2();
	void player();
	void machine();
	void congratulations(int player);
	void setPlayer();
	int setMode();
	void printAtXY(int x, int y, string str);
	void setCursorPosition(short int x, short int y);
	void change_player();
	int important();
	int game_player;
	shared_ptr<Display> display;
	int length;
	int Cx, Cy;
	vector<vector<int>> board;
	vector<vector<int>> importance;
};
#endif  /* _ManMachineGame */
//
//#ifndef _TwoPlayerGame
//#define _TwoPlayerGame	1
//class TwoPlayerGame :public Game {
//public:
//	virtual void run();
//	~TwoPlayerGame() {
//	};
//private:
//	Display *display;
//};
//
//#endif  /* _TwoPlayerGame */
