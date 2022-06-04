#pragma once
#include <map>
#include <list>
#include "GameState.h"
#include "CIndieLib_vc2008.h"
#include "StateStart.h"

class GameStateManager
{
private:
	std::ofstream myfile;
	std::list<StateStart *> * states;
	std::list<StateStart *> * activeStates;
	std::list<StateStart *>::iterator latestActivatedState;
	int startTime;
	IND_Timer * timer;
	void startNextState();
public:
	GameStateManager(void);
	~GameStateManager(void);
	void start();
	void update();
	void stop();
	void registerState(GameState * gs, int offset);
	inline int getTimeInSec(){
		return (int) (timer->GetTicks() / 1000.0f);
	}
};

