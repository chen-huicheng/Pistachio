#ifndef __DISPLAY
#define __DISPLAY

class Display {
public:
	virtual void show() { //ÏÔÊ¾ÆåÅÌ
	}
	virtual void move(int x, int y) { //ÉÏÏÂ×óÓÒ  -1 0   +1 0   0 -1   0 +1 
	}
	virtual void put(int player) { // player  0  ºÚ  other °×
	} 
	virtual void back() { // »ÚÆå
	}
	virtual ~Display() = 0 
	{
	}
};
#endif // !__DISPLAY

