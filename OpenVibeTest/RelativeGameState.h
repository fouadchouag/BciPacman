#pragma once
#include "gamestate.h"
class RelativeGameState :
	public GameState
{
private:
	GameState * nextState;
public:
	RelativeGameState(void);
	~RelativeGameState(void);
};

