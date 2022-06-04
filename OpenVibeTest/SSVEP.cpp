#include "SSVEP.h"

void SSVEP::update(int time){
	currentTime = time;

	if(frame>=refreshRate){
		frame=0;
	}
	if(flickering){
		if(frame%(refreshRate/frequencyLeft)==0){
			puzzle->leftArrow->SetShow(true);
		} else {
			puzzle->leftArrow->SetShow(false);
		}
		if(frame%(refreshRate/frequencyRight)==0){
			puzzle->rightArrow->SetShow(true);
		} else {
			puzzle->rightArrow->SetShow(false);
		}
	}
	frame++;
	updateVRPN();
}

void SSVEP::updateVRPN(){
	if(!training){
		rotateControl->processFrame();
	} else {
		if(trainingStarted){
			targetCommand->processFrame();
		}
		startStopCommand->processFrame();
	}
}


SSVEP::SSVEP(Puzzle * p, PuzzleInputManager * pim,bool training): pim(pim), puzzle(p), frame(0), training(training)
{
	rotateControl = new CRoatateControl(p,this);
	targetCommand = new CCommandReceiveTarget(this);
	startStopCommand = new CCommandStartStop(this);
	frequencyLeft = 20;
	frequencyRight= 15;
	refreshRate = 60;
	flickering = false;
}


SSVEP::~SSVEP(void)
{
}

void SSVEP::startTraining(){
	trainingStarted = true;
	moveArrows();
}
void SSVEP::stopTraining(){
	trainingStarted = false;
	restoreArrows();
}
void SSVEP::startSSVEP(){
	training = false;
	moveArrows();
	puzzle->leftArrow->SetShow(false);
	puzzle->rightArrow->SetShow(false);
	puzzle->feedbackLeft->SetShow(false);
	puzzle->feedbackRight->SetShow(false);
}
void SSVEP::stopSSVEP(){
	restoreArrows();
	puzzle->leftArrow->SetShow(false);
	puzzle->rightArrow->SetShow(false);
}

void SSVEP::startFlickering(){
	flickering = true;
	puzzle->leftArrow->SetShow(false);
	puzzle->rightArrow->SetShow(false);
}
void SSVEP::stopFlickering(){
	flickering = false;
	puzzle->leftArrow->SetShow(false);
	puzzle->rightArrow->SetShow(false);
}

void SSVEP::moveArrows(){
	puzzle->leftArrow->SetPosition(puzzle->leftArrow->GetPosX()-puzzle->tileWidth/2,puzzle->leftArrow->GetPosY(),puzzle->leftArrow->GetPosZ());
	puzzle->rightArrow->SetPosition(puzzle->rightArrow->GetPosX()+puzzle->tileWidth/2,puzzle->rightArrow->GetPosY(),puzzle->rightArrow->GetPosZ());
}

void SSVEP::restoreArrows(){
	puzzle->leftArrow->SetPosition(puzzle->leftArrow->GetPosX()+puzzle->tileWidth/2,puzzle->leftArrow->GetPosY(),puzzle->leftArrow->GetPosZ());
	puzzle->rightArrow->SetPosition(puzzle->rightArrow->GetPosX()-puzzle->tileWidth/2,puzzle->rightArrow->GetPosY(),puzzle->rightArrow->GetPosZ());
}

void SSVEP::start(){
	if(training){
		puzzle->feedbackLeft->SetShow(false);
		puzzle->feedbackRight->SetShow(false);
		puzzle->hideTiles();
	} else {
		startFlickering();
		startSSVEP();
	}
}

void SSVEP::stop(){
	if(training){
		puzzle->showTiles();
	} else {
		stopFlickering();
		stopSSVEP();
	}
}