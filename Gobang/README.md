# 五子棋人机对弈
## 功能
> 人机对弈和双人对弈 


> * **[CODE](Gobang)**
> * 主要通过两个类来实现
> * 一个显示类 DisplayByCmd 将棋盘信息显示出来 继承自 Display
> * 一个游戏类 GobangGame 存储游戏信息以及调用Display显示信息 继承自 Game
> *
> 

## Display.h 
```
class Display {
public:
	virtual void show() { //显示棋盘
	}
	virtual void move(int x, int y) { //上下左右  -1 0   +1 0   0 -1   0 +1 
	}
	virtual void put(int player) { // player  0  黑  other 白
	} 
	virtual void back() { // 悔棋
	}
	virtual ~Display() = 0 
	{
	}
};
```


## Display.h 
```
class Game {
protected:
	shared_ptr<Display> display;  //Display 智能指针
public:
	virtual void run() {  //游戏运行主函数
	}
	virtual ~Game() = 0 {
	}
	
};
```
