#pragma once
#include <boost/thread.hpp>
#include <string>

#include <tobii/sdk/cpp/mainloop.hpp>

class EyeTrackerMain
{
private:
	tobii::sdk::cpp::mainloop * mainLoop;
	boost::thread * analogClientThread;
	bool running;
public:
	EyeTrackerMain();
	~EyeTrackerMain(void);

	/*Thread handling methods*/
	//Callback
	void run();

	void start();
	void stop();
	void join();

	inline tobii::sdk::cpp::mainloop * getMainloop(){
	  return mainLoop;
	}
};

