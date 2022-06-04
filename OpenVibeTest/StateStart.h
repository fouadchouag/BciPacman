#pragma once
#include "GameState.h"
class StateStart
{
private:
	GameState * state;
	int offset;
public:

	StateStart(GameState * s, int off): state(s), offset(off){}
	inline GameState * getState(){
		return state;
	}
	inline int getOffset(){
	  return offset;
	}
};

