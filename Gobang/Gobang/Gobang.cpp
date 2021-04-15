#include <iostream>
#include "Game.h"
#include "GoBangGame.h"
#include <memory.h>
#include <memory>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	system("title 简易五子棋人机对弈 ——cheng");//设置标题
	system("mode con cols=85 lines=43");//设置窗口的宽度高度
	system("color E0");
	shared_ptr<Game> game(new GoBangGame());
	game->run();
	system("cls");
	system("pause");
 	return 0;
}