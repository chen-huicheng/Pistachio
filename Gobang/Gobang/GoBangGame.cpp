#include "GoBangGame.h"

void GoBangGame::run(int type) {
	while (1) {
		int mode = setMode();
		if (mode < 0)break;
		setPlayer();
		if (mode == 1) {
			mode1();
		}
		else
		{
			mode2();
		}
	}
	
}
bool GoBangGame::judge(int player) {
	int w = 1, x = 1, y = 1, z = 1, i;//�ۼƺ�����б��б�ĸ������������ͬ������Ŀ
	for (i = 1; i < 5; i++)
		if (Cy + i < length&&board[Cx][Cy + i] == player)w++;
		else break;//���¼��
	for (i = 1; i < 5; i++)
		if (Cy - i > 0 && board[Cx][Cy - i] == player)w++;
		else break;//���ϼ��
	if (w >= 5)return player;//�����ﵽ5�����жϵ�ǰ�������ΪӮ��
	for (i = 1; i < 5; i++)
		if (Cx + i < length&&board[Cx + i][Cy] == player)x++;
		else break;//���Ҽ��
	for (i = 1; i < 5; i++)
		if (Cx - i > 0 && board[Cx - i][Cy] == player)x++;
		else break;//������
	if (x >= 5)return player;//�����ﵽ5�����жϵ�ǰ�������ΪӮ��
	for (i = 1; i < 5; i++)
		if (Cx + i < length&&Cy + i < length&&board[Cx + i][Cy + i] == player)y++;
		else break;//�����¼��
	for (i = 1; i < 5; i++)
		if (Cx - i > 0 && Cy - i > 0 && board[Cx - i][Cy - i] == player)y++;
		else break;//�����ϼ��
	if (y >= 5)return player;//�����ﵽ5�����жϵ�ǰ�������ΪӮ��
	for (i = 1; i < 5; i++)
		if (Cx + i < length&&Cy - i>0 && board[Cx + i][Cy - i] == player)z++;
		else break;//�����ϼ��
	for (i = 1; i < 5; i++)
		if (Cx - i > 0 && Cy + i < length&&board[Cx - i][Cy + i] == player)z++;
		else break;//�����¼��
	if (z >= 5)return player;//�����ﵽ5�����жϵ�ǰ�������ΪӮ��
	return 0;
}

GoBangGame::GoBangGame():length(LENGTH), Cx(LENGTH / 2), Cy(LENGTH / 2), game_player(1),
						board(LENGTH, vector<int>(LENGTH, 0)), display(new DisplayByCmd(LENGTH)), importance(LENGTH+5, vector<int>(LENGTH+5, 0))
{
}

GoBangGame::GoBangGame(int len) : length(len), Cx(len / 2), Cy(len / 2), game_player(1),
								board(len,vector<int>(len,0)),display(new DisplayByCmd(len)), importance(len+5, vector<int>(len+5, 0))
{
}

void GoBangGame::mode1()
{
	display->show();
	while (1)
	{
		player();
		display->put(game_player);
		if (judge(game_player))
		{
			congratulations(game_player);
			break;
		}
		change_player();
	}
}

void GoBangGame::mode2()
{
	display->show();
	while (1)
	{
		player();
		display->put(game_player);
		if (judge(game_player))
		{
			congratulations(game_player);
			break;
		}
		machine();
		cout << game_player << endl;
		display->put(game_player);
		
		if (judge(game_player))
		{
			congratulations(game_player);
			break;
		}
		change_player();
	}
}

void GoBangGame::player()
{
	bool loop = true;
	while (loop) { //������µ��Ƿ������������������룬��һ��Ϊ0xE0��ʾ���µ��ǿ��Ƽ�
		int input = _getch();//��õڶ���������Ϣ
		int x = 0, y = 0;
		switch (input) { //�жϷ���������ƶ����λ��
		case 0x4B://
			x = -1;
			break;
		case 0x48:
			y = -1;
			break;
		case 0x4D:
			x = 1;
			break;
		case 0x50:
			y = 1;
			break;
		case 0x20:
			if (board[Cx][Cy] == 0)
			{
				loop = false;
				board[Cx][Cy] = game_player;
			}
			break;
		}
		Cx += x;
		Cy += y;
		if (Cx < 0)Cx = length - 1;//������λ��Խ�����ƶ����Բ�
		if (Cy < 0)Cy = length - 1;
		if (Cx > length - 1)Cx = 0;
		if (Cy > length - 1)Cy = 0;
		display->move(x, y);
	}
}

void GoBangGame::machine()
{
	int i, j;//ѭ������
  	int imp = 0, num = 0;
	vector<int> dj, di;
	important();//�ж���Ҫ��
	for (j = 0; j < length; j++)
	{
		for (i = 0; i < length; i++)
		{
			if (importance[i][j] > imp)
			{
				di.clear();
				dj.clear();
				imp = importance[i][j];
				di.push_back(i);
				dj.push_back(j);
			}
			if (importance[i][j] == imp)
			{
				di.push_back(i);
				dj.push_back(j);
			}
		}
	}
	change_player();
	important();
	for (j = 0; j < length; j++)
	{
		for (i = 0; i < length; i++)
		{
			if (importance[i][j] >= imp)
			{
				di.clear();
				dj.clear();
				imp = importance[i][j];
				di.push_back(i);
				dj.push_back(j);
			}
			if (importance[i][j] == imp)
			{
				di.push_back(i);
				dj.push_back(j);
			}
		}
	}
	srand(time(NULL));
	int ran = rand() % (num + 1);
	//	printf("%d",ran);
	//	system("PAUSE");
	board[di[ran]][dj[ran]] = game_player;
	int y = dj[ran]-Cy;
	int x = di[ran] - Cx;
	display->move(x, y);
	Cy = dj[ran];
	Cx = di[ran];
}

void GoBangGame::congratulations(int player)
{
	
	string name("����");
	if (player == 1)
		name = "����";
	printAtXY(35, 9, "��ϲ" + name+"\n");
	system("pause");
	system("cls");
}

void GoBangGame::setPlayer()
{
	printAtXY(length * 3 / 2, length / 2 - 1, " ** �������� ** ");
	printAtXY(length * 3 / 2, length / 2 + 1, "    ��������    ");
	int loop = true;
	while (loop) { //������µ��Ƿ������������������룬��һ��Ϊ0xE0��ʾ���µ��ǿ��Ƽ�
		int input = _getch();//��õڶ���������Ϣ
		switch (input) { //�жϷ���������ƶ����λ��
		case 0x48://
			game_player = 1;
			printAtXY(length * 3 / 2, length / 2 - 1, " ** �������� ** ");
			printAtXY(length * 3 / 2, length / 2 + 1, "    ��������    ");
			break;
		case 0x50:
			game_player = 2;
			printAtXY(length * 3 / 2, length / 2 - 1, "    ��������    ");
			printAtXY(length * 3 / 2, length / 2 + 1, " ** �������� ** ");
			break;
		case 0x20:
			loop = false;
			break;
		case 0x0D:
			loop = false;
			break;
		}
	}
}

int GoBangGame::setMode()
{
	printAtXY(length * 3 / 2, length / 2 - 1, " ** ˫�˶��� ** ");
	printAtXY(length * 3 / 2, length / 2 + 1, "    �˻�����    ");
	int loop = true;
	int model=1;
	while (loop) { //������µ��Ƿ������������������룬��һ��Ϊ0xE0��ʾ���µ��ǿ��Ƽ�
		int input = _getch();//��õڶ���������Ϣ
		switch (input) { //�жϷ���������ƶ����λ��
		case 0x48://
			model = 1;
			printAtXY(length * 3 / 2, length / 2 - 1, " ** ˫�˶��� ** ");
			printAtXY(length * 3 / 2, length / 2 + 1, "    �˻�����    ");
			break;
		case 0x50:
			model = 2;
			printAtXY(length * 3 / 2, length / 2 - 1, "    ˫�˶���    ");
			printAtXY(length * 3 / 2, length / 2 + 1, " ** �˻����� ** ");
			break;
		case 0x1B:
			model = -1;
			loop = false;
			break;
		case 0x0D:
			loop = false;
			break;
		}
	}
	return model;
}
void GoBangGame::printAtXY(int x, int y, string str) {
	setCursorPosition(x, y);
	cout << str;
	setCursorPosition(70, 39);
}
void GoBangGame::setCursorPosition(short int x, short int y) {
	HANDLE hOut;
	COORD pos = { x,y };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
void GoBangGame::change_player()
{
	game_player = 3 - game_player;
}
int GoBangGame::important()
{
	int i, j;
	for (j = 0; j < length; j++)//��������
	{
		for (i = 0; i < length; i++)
		{
			if (board[i][j] == 1 || board[i][j] == 2)
				importance[i][j] = 0;
			else {
				importance[i][j] = 0;
				int di, u = 0, d = 0, r = 0, l = 0, ru = 0, lu = 0, rd = 0, ld = 0;
				for (di = 1; di < 5; di++)
					if (j + di < length&&board[i][j + di] == game_player)
						d++;
					else
						break;//�в��䣬������
				if (board[i][j + di-1] != 3 - game_player)
					importance[i][j] += 3 * d;
				else
					importance[i][j] += d;
				for (di = 1; di < 5; di++)if (j - di > 0 && board[i][j - di] == game_player)u++; else break;//�в��䣬������
				if (board[i][j - di + 1] != 3 - game_player)
					importance[i][j] += 3 * u;
				else
					importance[i][j] += u;
				if (d + u >= 4)
				{
					importance[i][j] = 10;
					continue;
				}
				int temp = importance[i][j];
				importance[i][j] = 0;


				for (di = 1; di < 5; di++)if (j + di < length&&i + di < length&&board[i + di][j + di] == game_player)ld++; else break;//������
				if (board[i + di-1][j + di-1] != 3 - game_player)
					importance[i][j] += 3 * ld;
				else
					importance[i][j] += ld;
				for (di = 1; di < 5; di++)if (j - di > 0 && i - di > 0 && board[i - di][j - di] == game_player)ru++; else break;//������
				if (board[i - di+1][j - di+1] != 3 - game_player)
					importance[i][j] += 3 * ru;
				else
					importance[i][j] += ru;
				if (ld + ru >= 4)
				{
					importance[i][j] = 10;
					continue;
				}
				if (temp < importance[i][j])temp = importance[i][j];
				importance[i][j] = 0;


				for (di = 1; di < 5; di++)if (j - di > 0 && i + di < length&&board[i + di][j - di] == game_player)lu++; else break;//������
				if (board[i + di-1][j - di+1] != 3 - game_player)
					importance[i][j] += 3 * lu;
				else
					importance[i][j] += lu;
				for (di = 1; di < 5; di++)if (j + di < length&&i - di>0 && board[i - di][j + di] == game_player)rd++; else break;//������
				if (board[i - di+1][j + di-1] != 3 - game_player)
					importance[i][j] += 3 * rd;
				else
					importance[i][j] += rd;
				if (lu + rd >= 4)
				{
					importance[i][j] = 10;
					continue;
				}
				if (temp < importance[i][j])temp = importance[i][j];
				importance[i][j] = 0;


				if (temp < importance[i][j])temp = importance[i][j];
				importance[i][j] = 0;
				for (di = 1; di < 5; di++)if (i + di < length&&board[i + di][j] == game_player)l++; else break;//�в��䣬������
				if (board[i + di-1][j] != 3 - game_player)
					importance[i][j] += 3 * l;
				else
					importance[i][j] += l;
				for (di = 1; di < 5; di++)if (i - di > 0 && board[i - di][j] == game_player)r++; else break;//�в��䣬������
				if (board[i - di+1][j] != 3 - game_player)
					importance[i][j] += 3 * r;
				else
					importance[i][j] += r;
				if (l + r >= 4)
				{
					importance[i][j] = 10;
					continue;
				}
				int temp1 = 0;
				/*if (lu == 3 || (board[i + lu + 1][j - lu - 1] != 3 - game_player) && lu == 2)++temp1;
				if (u == 3 || (board[i][j - u - 1] != 3 - game_player) && u == 2)++temp1;
				if (ld == 3 || (board[i + ld + 1][j + ld + 1] != 3 - game_player) && ld == 2)++temp1;
				if (d == 3 || (board[i][j + d + 1] != 3 - game_player) && d == 2)++temp1;
				if (ru == 3 || (board[i - ru - 1][j - ru - 1] != 3 - game_player) && ru == 2)++temp1;
				if (rd == 3 || (board[i - rd - 1][j + rd + 1] != 3 - game_player) && rd == 2)++temp1;
				if (l == 3 || (board[i + l + 1][j] != 3 - game_player) && l == 2)++temp1;
				if (r == 3 || (board[i - r - 1][j] != 3 - game_player) && r == 2)++temp1;
				if (temp1 > 1)
					importance[i][j] = 9;*/
				if (temp > importance[i][j])temp = importance[i][j] = temp;
			}
		}
	}
	return 0;
}