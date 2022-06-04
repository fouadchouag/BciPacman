#pragma once

#include "ovassvepCRotateControl.h"
#include "ovassvepCCommandReceiveTarget.h"
#include "PuzzleInputManager.h"
#include "ovassvepCCommandStartStop.h"

typedef enum ssvep_target{
	LEFT_TARGET,
	RIGHT_TARGET,
	BLANK_TARGET
} ssvep_target_t;

class SSVEP
{
private:
	CRoatateControl * rotateControl;
	CCommandReceiveTarget * targetCommand;
	CCommandStartStop * startStopCommand;
	int frame;
	bool training;
	bool trainingStarted;
	bool flickering;

	void moveArrows();
	void restoreArrows();

public:
	int frequencyLeft;
	int frequencyRight;
	int refreshRate;
	int currentTime;
	ssvep_target_t currentTarget;
	Puzzle * puzzle;
	PuzzleInputManager * pim;

	void update(int time);
	void updateVRPN();
	void startTraining();
	void stopTraining();
	void startSSVEP();
	void stopSSVEP();
	void start();
	void stop();
	void startFlickering();
	void stopFlickering();
	void setTarget(ssvep_target_t target){
		currentTarget = target;
		//Code to move the target indicator
	}
	SSVEP(Puzzle * p, PuzzleInputManager * pim, bool training);
	~SSVEP(void);
};

