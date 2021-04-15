#include "DisplayByCmd.h"
using namespace std;

DisplayByCmd::DisplayByCmd(int len) :length(len), Cx(len / 2), Cy(len / 2) {
	Initialize();
}

void DisplayByCmd::put(int player){
	if(player==1)
	{
		printAtXY(Cx*4+2,Cy*2+1,"●");
	}
	else{
		printAtXY(Cx*4+2,Cy*2+1,"○");
	}
}
void DisplayByCmd::back() {
	printAtXY(Cx * 4 + 2, Cy * 2 + 1, "┼");
}
void DisplayByCmd::move(int x,int y) {
	printAtXY(Cx * 4, Cy * 2, " ");
	printAtXY(Cx * 4 + 4, Cy * 2 + 2, " ");
	printAtXY(Cx * 4, Cy * 2 + 2, " ");
	printAtXY(Cx * 4 + 4, Cy * 2, " ");
	Cx+=x;
	Cy+=y;
	if (Cx < 0)Cx = length - 1;//如果光标位置越界则移动到对侧
	if (Cy < 0)Cy = length - 1;
	if(Cx>length-1)Cx=0;
	if(Cy>length-1)Cy=0;
	printAtXY(Cx*4,Cy*2,getCurse(Cx,Cy));
	printAtXY(Cx*4+4,Cy*2+2,getCurse(Cx+1,Cy+1));
	printAtXY(Cx*4,Cy*2+2,getCurse(Cx,Cy+1));
	printAtXY(Cx*4+4,Cy*2,getCurse(Cx+1,Cy));
	cout<<" ["<<Cx<<","<<Cy<<"]";
}

void DisplayByCmd::printAtXY(int x,int y,string str){
	setCursorPosition(x,y);
    cout<<str;
    setCursorPosition(70,39); 

}
void DisplayByCmd::setCursorPosition(short int x,short int y){
	HANDLE hOut;
    COORD pos={x,y};
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,pos);
}
void DisplayByCmd::Initialize(){
	Cx=length/2;//重置光标到中央
	Cy=length/2;
}
void DisplayByCmd::show() {
	system("cls");
	int i,j;//循环变量
	int ln=0;
	Initialize();
	for(j=0; j<=length; j++) { //写入出交点左上角的字符，因为需要打印棋盘右下角，所以很以横纵各多一次循环
//		cout<<ln++;
		for(i=0; i<=length; i++) {
			cout<<getCurse(i,j);//写入左上角字符
			if(j==0||j==length) { //如果是棋上下盘边缘则没有连接的竖线，用空格填充位置
				if(i!=length)
					cout<<"  ";
			} else { //如果在棋盘中间则用竖线承接上下
				if(i==0||i==length-1)//左右边缘的竖线更粗
					cout<<"┃";
				else if(i!=length)//中间的竖线
					cout<<"│";
			}
		}
		if(j==length) { //如果是最后一次循环，则只需要处理边侧字符，交点要少一排
			break;
		}
		cout<<endl;//提行开始打印交点内容
		cout<<"  ";//用空位补齐位置
		for(i=0; i<length; i++) { //按横坐标循环正常的次数
			cout<<getStyle(i,j);//写入交点字符
			if(i!=length-1) { //如果不在最右侧则补充一个横线承接左右
				if(j==0||j==length-1) {
					cout<<"━";//上下边缘的横线更粗
				} else {
					cout<<"—";//中间的横线
				}
			}
		}
		cout<<endl;
	}
}
string DisplayByCmd::getCurse(int i,int j) { //获得指定坐标交点位置左上格的样式，通过制表符来模拟光标的显示
	if(i==Cx) {
		if(j==Cy)
			return "┏";
		else if (j==Cy+1)
			return "┗";
	} else if(i==Cx+1) {
		if(j==Cy)
			return "┓";
		else if (j==Cy+1)
			return "┛";
	}
	return "　";//如果不在光标附近则为空
}

string DisplayByCmd::getStyle(int i,int j) { //获得棋盘中指定坐标交点位置的字符，通过制表符拼成棋盘
	if(i==0&&j==0)//以下为边缘棋盘样式
		return "┏";
	else if(i==length-1&&j==0)
		return "┓";
	else if(i==length-1&&j==length-1)
		return "┛";
	else if(i==0&&j==length-1)
		return "┗";
	else if(i==0)
		return "┠";
	else if(i==length-1)
		return "┨";
	else if(j==0)
		return "┯";
	else if(j==length-1)
		return "┷";
	return "┼";//中间的空位
}

