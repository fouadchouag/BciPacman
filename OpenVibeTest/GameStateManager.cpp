#include "GameStateManager.h"


GameStateManager::GameStateManager(void)
{
	states = new std::list<StateStart *>();
	activeStates = new std::list<StateStart *>;
	timer = new IND_Timer();
	myfile = std::ofstream();
	myfile.open("stateManager.txt");
	myfile << "Hello No!\n";
	myfile.flush();
}

GameStateManager::~GameStateManager(void)
{
	list<StateStart *>::iterator it;
	for ( it=states->begin() ; it != states->end(); it++ ){
		StateStart * ss = states->front();
		//delete ss->getState();
		delete ss;
		states->pop_front();
	}
	delete states;
	activeStates->clear();
	delete activeStates;
	myfile.flush();
	myfile.close();
}

void GameStateManager::start(){
	timer->Start();
	startTime = getTimeInSec();
	latestActivatedState = states->end();
	startNextState();
	myfile << "Starting game state manager!\n";
	myfile.flush();
}

void GameStateManager::stop(){
	timer->Stop();
		list<StateStart *>::iterator it;
		for ( it=activeStates->begin() ; it != activeStates->end(); it++ ){
			(*it)->getState()->stop();
		}
}

void GameStateManager::startNextState(){
	if(states->size() > 0){
		if(latestActivatedState!=states->end()){
			latestActivatedState++;
		}
		if(latestActivatedState==states->end()){
			activeStates->push_back(states->front());
			states->front()->getState()->start(getTimeInSec());	
			latestActivatedState = states->begin();
		} else {
			activeStates->push_back(*latestActivatedState);
			(*latestActivatedState)->getState()->start(getTimeInSec());	
		}
	}
}

void GameStateManager::update(){
	list<StateStart *>::iterator it;
	myfile << "Update at " << getTimeInSec() << std::endl;
	for ( it=activeStates->begin() ; it != activeStates->end(); it++ ){
		StateStart * ss = *it;
		if(!ss->getState()->isStarted()){
			myfile << "Stopped active state" <<std::endl;
			if(ss->getOffset()==-1){
				myfile << "Starting next" <<std::endl;
				startNextState();
			}
			myfile << "Removing finished state" <<std::endl;
			activeStates->erase(it++);
		} else {
			if(ss->getOffset()!=-1 && (ss)->getState()->getStartTime()+ss->getOffset() < getTimeInSec()){
				startNextState();
			}
			ss->getState()->update(getTimeInSec());
		}
	}
	if(states->size() == 0 && activeStates->size()==0){
		stop();
	}
}

void GameStateManager::registerState(GameState * gs, int offset){
	myfile << "Registering state with offset " << offset << std::endl;
	states->push_back(new StateStart(gs,offset));
}