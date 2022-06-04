#pragma once
#include <list>
#include "puzzle.h"
#include "ovaCAbstractVrpnPeripheral.h"
class GratzFeedback
{
private:

	Puzzle * puzzle;
	OpenViBEVRDemos::CAbstractVrpnPeripheral * vrpnPeripheral;
	std::ofstream myfile;

	double feedback;
	double lastFeedback;
	double maxFeedback;
	double minFeedback;
	std::list <double> analogHistory;

	int phase;
	int lastPhase;
	int phaseTime;

	int feedPositive;
	int feedNegative;

	bool rotated;

	int mark;
	int lastMark;

	bool showCross;
	bool showClue;
	bool showFeedback;
	enum
	{
		Phase_GetReady,
		Phase_Active,
		Phase_Rest,
	} EPhase;
	enum
	{
		Mark_Right,
		Mark_Left,
		Mark_None,
	} EMark;

public:
	GratzFeedback(Puzzle *p, OpenViBEVRDemos::CAbstractVrpnPeripheral * vrpnp);
	~GratzFeedback(void);
	void update(int time);
	double getFeedback(){
		return feedback;	
	}
	double getLastFeedback(){
		return lastFeedback;
	}
	double getMaxFeedback(){
		return maxFeedback;
	}
	double getMinFeedBack(){
		return minFeedback;
	}
	void setFeedback(double v){
		feedback = v;
	}
	void setLastFeedback(double v){
		lastFeedback = v;
	}
	void setMaxFeedback(double v){
		maxFeedback = v;
	}
	void setMinFeedback(double v){
		minFeedback = v;
	}
};

