#include "Display.h"
#include "DisplayByCmd.h"
#include <memory>
#ifndef _GAME
#define _GAME 1
class Game {
protected:
	shared_ptr<Display> display;
public:
	virtual void run() {  //��Ϸ����������
	}
	virtual ~Game() = 0 {
	}
	
};

#endif  /* _GAME */

