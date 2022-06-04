#pragma once
#include "gamestate.h"
#include <fstream>
class GameStateActive :
	public GameState
{
public:
	std::ofstream myfile;
	GameStateActive(void);
	~GameStateActive(void);
	void update(int time);
	void start(int time);
};

