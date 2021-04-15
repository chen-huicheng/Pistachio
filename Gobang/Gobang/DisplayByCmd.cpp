#include "DisplayByCmd.h"
using namespace std;

DisplayByCmd::DisplayByCmd(int len) :length(len), Cx(len / 2), Cy(len / 2) {
	Initialize();
}

void DisplayByCmd::put(int player){
	if(player==1)
	{
		printAtXY(Cx*4+2,Cy*2+1,"��");
	}
	else{
		printAtXY(Cx*4+2,Cy*2+1,"��");
	}
}
void DisplayByCmd::back() {
	printAtXY(Cx * 4 + 2, Cy * 2 + 1, "��");
}
void DisplayByCmd::move(int x,int y) {
	printAtXY(Cx * 4, Cy * 2, " ");
	printAtXY(Cx * 4 + 4, Cy * 2 + 2, " ");
	printAtXY(Cx * 4, Cy * 2 + 2, " ");
	printAtXY(Cx * 4 + 4, Cy * 2, " ");
	Cx+=x;
	Cy+=y;
	if (Cx < 0)Cx = length - 1;//������λ��Խ�����ƶ����Բ�
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
	Cx=length/2;//���ù�굽����
	Cy=length/2;
}
void DisplayByCmd::show() {
	system("cls");
	int i,j;//ѭ������
	int ln=0;
	Initialize();
	for(j=0; j<=length; j++) { //д����������Ͻǵ��ַ�����Ϊ��Ҫ��ӡ�������½ǣ����Ժ��Ժ��ݸ���һ��ѭ��
//		cout<<ln++;
		for(i=0; i<=length; i++) {
			cout<<getCurse(i,j);//д�����Ͻ��ַ�
			if(j==0||j==length) { //������������̱�Ե��û�����ӵ����ߣ��ÿո����λ��
				if(i!=length)
					cout<<"  ";
			} else { //����������м��������߳н�����
				if(i==0||i==length-1)//���ұ�Ե�����߸���
					cout<<"��";
				else if(i!=length)//�м������
					cout<<"��";
			}
		}
		if(j==length) { //��������һ��ѭ������ֻ��Ҫ����߲��ַ�������Ҫ��һ��
			break;
		}
		cout<<endl;//���п�ʼ��ӡ��������
		cout<<"  ";//�ÿ�λ����λ��
		for(i=0; i<length; i++) { //��������ѭ�������Ĵ���
			cout<<getStyle(i,j);//д�뽻���ַ�
			if(i!=length-1) { //����������Ҳ��򲹳�һ�����߳н�����
				if(j==0||j==length-1) {
					cout<<"��";//���±�Ե�ĺ��߸���
				} else {
					cout<<"��";//�м�ĺ���
				}
			}
		}
		cout<<endl;
	}
}
string DisplayByCmd::getCurse(int i,int j) { //���ָ�����꽻��λ�����ϸ����ʽ��ͨ���Ʊ����ģ�������ʾ
	if(i==Cx) {
		if(j==Cy)
			return "��";
		else if (j==Cy+1)
			return "��";
	} else if(i==Cx+1) {
		if(j==Cy)
			return "��";
		else if (j==Cy+1)
			return "��";
	}
	return "��";//������ڹ�긽����Ϊ��
}

string DisplayByCmd::getStyle(int i,int j) { //���������ָ�����꽻��λ�õ��ַ���ͨ���Ʊ��ƴ������
	if(i==0&&j==0)//����Ϊ��Ե������ʽ
		return "��";
	else if(i==length-1&&j==0)
		return "��";
	else if(i==length-1&&j==length-1)
		return "��";
	else if(i==0&&j==length-1)
		return "��";
	else if(i==0)
		return "��";
	else if(i==length-1)
		return "��";
	else if(j==0)
		return "��";
	else if(j==length-1)
		return "��";
	return "��";//�м�Ŀ�λ
}

