#pragma once
class GameState
{
private:
	int startTime;
public:
	GameState(void): startTime(-1){}
	virtual ~GameState(void){
	}
	virtual void update(int time)=0;
	virtual void start(int time){
		startTime = time;
	}
	virtual void stop(){
		startTime=-1;
	}
	virtual bool isStopped(){
		return !isStarted();
	}

	virtual bool isStarted(){
		return startTime!=-1;
	}

	virtual int getStartTime(){
		return startTime;
	}
};

