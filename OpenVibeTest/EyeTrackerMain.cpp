#include "EyeTrackerMain.h"
#include <iostream>


void EyeTrackerMain::run(){
	mainLoop->run();
}

void EyeTrackerMain::start(){
	running = true;
	if(analogClientThread != NULL){
		delete analogClientThread;
	}
	analogClientThread = new boost::thread(&EyeTrackerMain::run, this);
}

void EyeTrackerMain::stop(){
	mainLoop->quit();
	running = false;
}

void EyeTrackerMain::join(){
	if(running){
		analogClientThread->join();
	}
}

EyeTrackerMain::EyeTrackerMain()
{
	this->running = false;
	analogClientThread = NULL;
	mainLoop = new tobii::sdk::cpp::mainloop();
}


EyeTrackerMain::~EyeTrackerMain(void)
{
	if(analogClientThread != NULL){
		delete analogClientThread;
	}
	delete mainLoop;
	std::cout << "Deleting Client" << std::endl;
}
