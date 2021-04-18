#include<string>
#include "DisplayByCmd.h"
#include<stdlib.h>
#include<fstream>
#include<vector>
#include <algorithm>
#include <thread>
using namespace std;
const int cols = 210;
const int rows = 90;
int year, mon, day;
vector<vector<string>>word, number,char_imgs, background, birthday_img, iloveu, fire;

vector<int> nums;  // 随机显示使用
const vector<int> dir{ -1,0,1,0,-1,-1,1,1,-1 }; //方向
time_t start_time=0;//1604151000; 记录开始时间  存储的是从1900年到现在的秒数

int myrandom(int i) {  return std::rand() % i; } //生成随机数
int myrandom_day(int i) { srand((int)time(0)); return std::rand() % i; } //根据日期生成随机数
bool check(vector<string> char_img, int i, int j) { //判断 i j 
	int n = char_img.size();
	if (n == 0)return false;
	int m = char_img[0].size();
	if (i < 0 || i >= n || j < 0 || j >= m)return false;
	if (char_img[i][j] != ' ')return true;
	
	for (int i = 0; i < 8; i++)
	{
		int x = i + dir[i];
		int y = j + dir[i + 1];
		if (x < 0 || x >= n || y < 0 || y >= m)continue;
		if (char_img[x][y] != ' ')return true;
	}
	return false;
}
void display_rand(const vector<string> &char_img,vector<int> &nums) //按照随机方式 显示
{
	DisplayByCmd display;
	random_shuffle(nums.begin(), nums.end(), myrandom);  //打乱 nums
	//system("cls");
	for (auto n : nums) { // 按照打乱的顺序输出
		int row = n / cols;
		int col = n % cols;
		display.printAtRowCol(row, col, char_img[row][col]);
	}
	display.end_display();
}
void display_rand_xy(const vector<string> &char_img, int brow, int bcol,int k,bool notCheck=true)//在 特定位置 随机显示
{
	DisplayByCmd display;
	vector<int> nums;
	int r = min(rows, char_img.size());
	if (r < 0)return;
	int c = min(cols, char_img[0].size());
	for (int i = 0; i < r; i+=k) {
		for (int j = 0; j < c; j+=k) {
			nums.push_back(i * c + j);
		}
	}
	random_shuffle(nums.begin(), nums.end(), myrandom);
	for (auto n : nums) {
		int row = n / c;
		int col = n % c;
		if(notCheck||check(char_img,row,col))
			display.printAtRowCol(brow+row/k, bcol + col/k, char_img[row][col]);
	}
	Sleep(100);
	display.end_display();
}
void display_up(const vector<string> &char_img) //自下向上 显示
{
	DisplayByCmd display;
	system("cls");
	int k = rows - char_img.size();
	for (int i = char_img.size() - 1; i >= 0;i--) {
		display.printRow(i+k, char_img[i]);
	}
}
void display_at_xy(const vector<string> &char_img,int row,int col) //在 特定位置 显示
{
	DisplayByCmd display;
	for (int i = 0; i <char_img.size(); i++) {
		display.printAtRowCol(i+row,col, char_img[i]);
	}
}
void display_520(int i) {  //先显示字符图像，然后在图像下方显示  iloveu  字样
	display_rand(char_imgs[i], nums);
	Sleep(520);
	display_rand_xy(iloveu[0], 70, 27, 1);
	Sleep(5000);
}
void display_214() {   //情人节 显示效果：显示每副图像
	for (auto img: char_imgs) {
		display_rand(img, nums);
		Sleep(5000);
	}
}
void display_birthday(int age) { 
	int row = 10;
	display_rand(birthday_img[0], nums);   //显示 birthday 背景 birthday.txt中内容
	display_rand_xy(number[age / 10], 20, 80, 1); // 显示年龄
	display_rand_xy(number[age % 10], 20, 110, 1);
	Sleep(3000);
	display_rand_xy(fire[0], row +3, 85+2, 3);  // 显示小火苗
	display_rand_xy(fire[0], row +3, 115+2, 3);
	Sleep(500);
	display_rand_xy(fire[0], row +2, 85+1, 2);	// 显示中火苗
	display_rand_xy(fire[0], row +2, 115+1, 2);
	Sleep(500);
	display_rand_xy(fire[0], row, 85, 1);      // 显示大火苗
	display_rand_xy(fire[0], row, 115, 1);
	int k = 1;
	while (k <= 30) {					// 火苗摆动效果
		display_rand_xy(fire[k % 4], row, 85, 1);
		display_rand_xy(fire[(k + 1) % 4], row, 115, 1);
		display_rand_xy(number[age / 10], 20, 80, 1);
		display_rand_xy(number[age % 10], 20, 110, 1);
		k++;
		Sleep(333);
	}
}
void diaplay_day() { // 根据日期显示不同内容
	time_t t;
	struct tm *date = new tm;
	time(&t);
	localtime_s(date, &t);
	if (date->tm_mon == 1 && date->tm_mday == 14) {		 // 情人节
		display_214();
	}
	else if (date->tm_mon == 4 && date->tm_mday == 20) {	// 520
		int n = char_imgs.size();
		for (int i = 0; i < n; i++) {
			display_520(i);
		}
	}
	else if (date->tm_mon == mon && date->tm_mday == day) {	// 生日
		int age = date->tm_year + 1900 - year;
		display_birthday(age);
	}
	else    // 其它
	{
		int n = min(5, char_imgs.size());
		int pre = -1,idx=0;
		for (int i = 0; i < n; i++) {
			while ((idx = myrandom_day(char_imgs.size())) == pre);
			display_rand(char_imgs[idx], nums);
			Sleep(3000);
			pre = idx;
		}
	}
}
void set_background(string mode="up") {  // 设置背景  根据不同日期设置不同背景
	time_t t;
	struct tm *date = new tm;
	time(&t);
	localtime_s(date, &t);

	if (date->tm_mon == 1 && date->tm_mday == 14 && mode == "rand") {
		display_rand(background[1], nums);
	}
	else if (date->tm_mon == 4 && date->tm_mday == 20 && mode == "rand") {
		display_rand(background[3], nums);
	}
	else if (date->tm_mon == mon && date->tm_mday == day && mode == "rand") {
		display_rand(background[2], nums);
	}
	else if (date->tm_mon == 1 && date->tm_mday == 14) {
		display_up(background[1]);
	}
	else if (date->tm_mon == 4 && date->tm_mday == 20) {
		display_up(background[3]);
	}
	else if (date->tm_mon == mon && date->tm_mday == day) {
		display_up(background[2]);
	}
	else
	{
		int i = myrandom_day(3);
		if(mode=="rand")
			display_rand(background[0],nums);
		else display_up(background[0]);
	}
		
}
struct time_day
{
	int sec=-1;  /*秒，正常范围0-59*/
	int min=-1;  /*分钟，0-59*/
	int hour=-1; /*小时， 0-23*/
	int day=-1; /*日，0-forever*/
};
void todayhours(time_day *date_time, time_t t)
{
	date_time->day = t / 86400;
	t %= 86400;
	date_time->hour = t / 3600;
	t %= 3600;
	date_time->min = t / 60;
	t %= 60;
	date_time->sec = t;
}
void display_day_hours_min_random(time_day &pre_date_time, time_day *date_time) { // 显示相恋到现在的时间
	bool flag = false;
	int begin_row1 = 15;
	int begin_row2 = 30;
	if (pre_date_time.day != date_time->day) {
		if (pre_date_time.day != -1) {//date_time->day >= 105 && 
			system("cls");
			set_background();
		}
		pre_date_time.day = date_time->day;
		int day = pre_date_time.day;
		vector<int> days;
		while (day) {
			days.emplace_back(day % 10);
			day /= 10;
		}
		int len = days.size();
		len = (cols - (len) * 20-26) / 2;
		for (int i = days.size() - 1; i >= 0; i--, len += 20) {
			display_rand_xy(number[days[i]], begin_row1, len , 1);
		}
		display_rand_xy(word[0], begin_row1 , len, 1);
		flag = true;
	}
	if (flag || pre_date_time.hour != date_time->hour) {
		int pre = pre_date_time.hour;
		pre_date_time.hour = date_time->hour;
		int hour = pre_date_time.hour;
		if(flag || pre / 10 != hour / 10)
			display_rand_xy(number[hour / 10], begin_row2, 4, 1);
		if(flag || pre % 10 != hour % 10)
			display_rand_xy(number[hour % 10], begin_row2, 24, 1);
		if(flag)
			display_rand_xy(word[1], begin_row2, 44, 1);
	}
	if (flag || pre_date_time.min != date_time->min) {
		int pre = pre_date_time.min;
		pre_date_time.min = date_time->min;
		int min = pre_date_time.min;
		if(flag || pre / 10 != min / 10)
			display_rand_xy(number[min / 10], begin_row2, 72, 1);
		if(flag || pre % 10 != min % 10)
			display_rand_xy(number[min % 10], begin_row2, 92, 1);
		if(flag)
			display_rand_xy(word[2], begin_row2, 112, 1);

	}
	if (flag || pre_date_time.sec != date_time->sec) {
		int pre = pre_date_time.sec;
		pre_date_time.sec = date_time->sec;
		int sec = pre_date_time.sec;
		if (flag || pre / 10 != sec / 10)
			display_rand_xy(number[sec / 10], begin_row2, 140, 1);
		if (flag || pre % 10 != sec % 10)
			display_rand_xy(number[sec % 10], begin_row2, 160, 1);
		if (flag)
			display_rand_xy(word[3], begin_row2, 180, 1);
	}
}
void display_time()
{
	time_t t, pre_t=0;
	time_day *date_time = new time_day;
	time_day pre_date_time;
	struct tm *date = new tm;
	int sec = 11;
	thread th1(set_background,"rand");
	th1.join();
	time(&t);
	time_t init_t = t - start_time+2;
	todayhours(date_time, init_t);
	thread th2(display_day_hours_min_random, ref(pre_date_time), date_time);
	th2.join();
	while (sec)
	{
		time(&t);
		localtime_s(date, &t);
		t = t - start_time;
		if (t < init_t||(t<=pre_t&&pre_t)) {
			Sleep(100);
			continue;
		}
		if (date->tm_mon == 1 && date->tm_mday == 14) {
			sec--;
		}
		else if (date->tm_mon == mon && date->tm_mday == day) {
			sec--;
		}
		else if (date->tm_mon == 4 && date->tm_mday == 20) {
			sec--;
		}
		if (t < 0) {
			date_time->day = 0;
			date_time->hour = 0;
			date_time->min = 0;
			date_time->sec = 0;
		}
		else
			todayhours(date_time, t);    //VS2010中优化了localtime函数为localtime_s()函数 -> Security 
		if (date->tm_mon == 3 && date->tm_mday == 1) {
			//if(date_time->sec)
			do {
				int i = myrandom(5)-2;
				date_time->sec += i;
				date_time->sec = min(date_time->sec,59);
				date_time->sec = max(date_time->sec, 0);
			} while (date_time->sec == pre_date_time.sec);
		}
		display_day_hours_min_random(pre_date_time, date_time);
		pre_t = t;
	}
}
void display_time_sec(int sec=6)
{
	time_t t, pre_t = 0;
	time_day *date_time = new time_day;
	time_day pre_date_time;
	struct tm *date = new tm;
	thread th1(set_background, "rand");
	th1.join();
	time(&t);
	time_t init_t = t - start_time + 2;
	todayhours(date_time, init_t);
	thread th2(display_day_hours_min_random, ref(pre_date_time), date_time);
	th2.join();
	while (sec)
	{
		time(&t);
		localtime_s(date, &t);
		t = t - start_time;
		if ((t <= pre_t && pre_t)) {
			Sleep(100);
			continue;
		}
		if (t < init_t)continue;
		if (t < 0) {
			date_time->day = 0;
			date_time->hour = 0;
			date_time->min = 0;
			date_time->sec = 0;
		}
		else
			todayhours(date_time, t);    //VS2010中优化了localtime函数为localtime_s()函数 -> Security 
		display_day_hours_min_random(pre_date_time, date_time);
		pre_t = t;
		sec--;
	}
}
void display_main() {
	display_time_sec();
	while (true) {
		diaplay_day();
		display_time();
	}
}
int write_to_txt(const vector<vector<string>> &src,string filename) {
	ofstream outfile(filename,ios::out);
	if (!outfile) {
		cout << filename << " not found or not exist !!!" << endl;
		return -1;
	}
	for (auto one : src) {
		for (auto row : one) {
			outfile << row << endl;
		}
		outfile << endl;
	}
	return 0;
}
int read_from_txt(vector<vector<string>> &src, string filename) {
	ifstream infile(filename, ios::in);
	if (!infile) {
		cout << filename << " not found or not exist !!!" << endl;
		return -1;
	}
	string str;
	vector<string> tmp;
	while (!infile.eof()) {
		getline(infile, str);
		if (str.size() == 0) {
			if(tmp.size()>0)
				src.push_back(tmp);
			tmp.clear();
			continue;
		}
		tmp.push_back(str);
	}
	if (tmp.size() > 0) {
		src.push_back(tmp);
	}
	return 0;
}
int init(string birthday, string starttime) {
	time_t t;
	time(&t);

	int time = stoi(birthday);
	day = time % 100;
	mon = (time / 100) % 100 - 1;
	year = (time / 10000);

	struct tm *date = new tm;
	localtime_s(date, &t);
	int i = starttime.find(':');
	int startday = stoi(starttime.substr(0, i));
	int starttm = stoi(starttime.substr(i + 1));
	// 年月日
	date->tm_year = (startday / 10000)-1900;
	date->tm_mon = (startday / 100) % 100-1;
	date->tm_mday = startday % 100;
	// 时分秒
	date->tm_hour = starttm / 10000;
	date->tm_min = (starttm / 100) % 100;
	date->tm_sec = starttm % 100;
	start_time = mktime(date);
	if (start_time == -1) {
		cout << starttime << "格式错误" << endl;
	}
	if (t< start_time) {
		cout << starttime << "是将来的时间" << endl;
	}
	return 0;
}
int main() {
	string birthday = "19970615"; //格式  yyyymmdd 年月日
	string starttime = "20201031:213000";    //格式  yyyymmdd:hhmmss  年月日:时分秒

	// 从配置文件中读取信息
	ifstream infile("config.txt", ios::in);
	if (!infile) {
		cout << "config.txt not found or not exist !!!" << endl;
		system("pause");
		return -1;
	}
	string str;
	getline(infile, str);
	birthday = str.substr(str.find(':') + 1);
	getline(infile, str);
	starttime = str.substr(str.find(':') + 1);
	int ret = init(birthday,starttime);
	if (ret == -1) {
		system("pause");
		return -1;
	}
	// 从文件中读取 数据
	ret += read_from_txt(number, "resources/number.txt");
	ret += read_from_txt(word, "resources/word.txt");
	ret += read_from_txt(char_imgs, "resources/char_imgs.txt");
	ret += read_from_txt(background, "resources/background.txt");
	ret += read_from_txt(iloveu, "resources/iloveu.txt");
	ret += read_from_txt(birthday_img, "resources/birthday.txt");
	ret += read_from_txt(fire, "resources/fire.txt");
	if (ret) {
		system("pause");
		return -1;
	}

	system("title For you, my babe. chc 20210214");//设置标题
	system("mode con cols=211 lines=91");//设置窗口的宽度高度
	system("color F0");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			nums.push_back(i * 210 + j);
		}
	}
	for (int i = 0; i < 30; i++)
		random_shuffle(nums.begin(), nums.end(), myrandom);
	
	display_main();
	return 0;
}

/*
设想:
1: 字符动画
2：结束时展示在一起的时间   随时间改变   在一个 心形 中
4：跟时间一起的   可说明时间  从什么时候算起     20201031:213000 开启了我们
 */