#ifndef PLAYER_H
#define PLAYER_H
#include "IChessPlayer.h"
//selectpiece(), selectmove()

class Player : public IChessPlayer{
	public:
	
	Player();
	
	void on_CellSelected(int row, int col, int button);
	
	virtual void on_TimerEvent();
	
	
	~Player();
	
	private:
	
};

#endif

