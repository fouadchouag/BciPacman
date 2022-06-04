#pragma once

#include <boost/thread.hpp>
#include <string>
#include <tobii/sdk/cpp/discovery/factory-info.hpp>
#include <tobii/sdk/cpp/discovery/eyetracker-info.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker-factory.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker.hpp>
using namespace tobii::sdk::cpp;

class EyeTrackerManager
{
private:
   EyeTrackerManager(void);
   static EyeTrackerManager * instance;
   tracking::eyetracker::pointer eyetracker;

public:
	static EyeTrackerManager * getInstance(){
		if(!instance){
			instance = new EyeTrackerManager();
		}
		return instance;
	}

	void setTracker(tracking::eyetracker::pointer et){
	  eyetracker=et;
	}

	tracking::eyetracker::pointer getTracker(){
	  return eyetracker;
	}

	~EyeTrackerManager(void);
};

