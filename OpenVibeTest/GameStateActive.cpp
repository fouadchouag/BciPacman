#include "GameStateActive.h"
#include <iostream>

GameStateActive::GameStateActive(void) : GameState()
{	
  myfile=std::ofstream();
  myfile.open("gameState.txt");
}


GameStateActive::~GameStateActive(void)
{
	GameState::~GameState();
	myfile.close();
}

void GameStateActive::update(int time){
	if(getStartTime()+20 == time){
		stop();
		myfile << time << " -- Stop\n";
	} else {
		myfile << time << " -- Rolling\n";
	}
}

void GameStateActive::start(int time){
		GameState::start(time);
		myfile << time << " -- Start\n";
}