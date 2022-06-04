#include "GratzFeedback.h"
#include <cmath>
#include <iostream>
#include <sstream>

static const float g_fEpsilon=1E-5f;
static const int HISTORY_SIZE = 5;

GratzFeedback::GratzFeedback(Puzzle *p, OpenViBEVRDemos::CAbstractVrpnPeripheral * vrpnp)
	: puzzle(p), vrpnPeripheral(vrpnp)
{
		// The current and previous phases
	phase=Phase_Rest;
	lastPhase=Phase_Rest;

	// Feedback from analog VRPN server
	feedback=0;
	lastFeedback=0;
	maxFeedback=0;
	minFeedback=0;

	mark = Mark_None;
	lastMark = Mark_None;
	showCross = false;
	showClue = false;
	showFeedback = false;
	phaseTime = 0;

	feedNegative=0;
	feedPositive=0;
	rotated=true;

	myfile.open("Graz.txt");
	myfile << "Hey Graz!\n";
	myfile.flush();
}


GratzFeedback::~GratzFeedback(void)
{
}

void GratzFeedback::update(int time){
	while(!vrpnPeripheral->m_vButton.empty())
	{
		std::pair < int, int >& l_rVrpnButtonState=vrpnPeripheral->m_vButton.front();

		if(l_rVrpnButtonState.second)
		{
			switch(l_rVrpnButtonState.first)
			{
				case 0:
					phase=Phase_GetReady;
					phaseTime = time;
					showCross = true;
					showClue = false;
					showFeedback = false;
					break;

				case 1:
					phase=Phase_Active;
					phaseTime = time;
					showCross = true;
					showClue = false;
					showFeedback = true;
					feedNegative=0;
					feedPositive=0;
					showFeedback = false;
					rotated=false;
					break;

				case 2:
					phase=Phase_Rest;
					phaseTime = time;
					showCross = false;
					showClue = false;

					break;
				//------------Instructions ---------------
				case 3:
					mark=Mark_Left;
					showClue = true;
					//m_iTrialLeftCount++;
					break;

				case 4:
					mark=Mark_Right;
					showClue = true;
					//m_iTrialRightCount++;
					break;

				case 5:
					mark=Mark_None;
					break;

				default:
					break;
			}
		}

		vrpnPeripheral->m_vButton.pop_front();
	}

	if(!vrpnPeripheral->m_vAnalog.empty())
	{
		std::list < double >& l_rVrpnAnalogState=vrpnPeripheral->m_vAnalog.front();

		//we take the last value from the server
		double l_dAnalog=*(l_rVrpnAnalogState.begin());

		//we updtae the max and min values
		// A. VLG : we should compute the min/max only in the ACTIVE phase
		// but if so, the first feedback value is infinite, resulting in a strange ball placement in the first active phase.
		if(phase == Phase_Active || phase == Phase_GetReady)
		{
			if(l_dAnalog>maxFeedback) maxFeedback=l_dAnalog;
			if(l_dAnalog<minFeedback) minFeedback=l_dAnalog;
		}
		
		//maximum of the absolute values
		
		double l_dAbsoluteMinMax=max(abs(maxFeedback), abs(minFeedback));

		//we update the history, keeping only the last HISTORY_SIZE values
		analogHistory.push_back(l_dAnalog);
		if(analogHistory.size() > HISTORY_SIZE)
		{
			analogHistory.pop_front();
		}

		// we compute the mean value of the analog history
		double l_dAnalogMean=0;
		std::list < double >::const_iterator i;
		for(i=analogHistory.begin(); i!=analogHistory.end(); i++)
		{
			l_dAnalogMean+=*i;
		}
		l_dAnalogMean/=analogHistory.size();

		// and we divide it by the absolute max value, to get a value between 0 and 1
		l_dAnalogMean/=(l_dAbsoluteMinMax?l_dAbsoluteMinMax:g_fEpsilon);

		// we update the feedback value that will be used to move the ball
		lastFeedback = feedback;
		feedback=l_dAnalogMean;

		vrpnPeripheral->m_vAnalog.pop_front();
	}


	std::list < double >::const_iterator ii;
				
	// update for each phase change
	if(phase!=lastPhase)
	{
		switch(phase)
		{
			case Phase_Rest:
				//TODO: PHASE REST DISPLAY UPDATE
				puzzle->getTextTitle()->SetText("REST PHASE");
				break;
			case Phase_GetReady:
				puzzle->getTextTitle()->SetText("GET READY");
				//TODO: Phase Get Ready Display Update

				break;

			
			case Phase_Active:
				//TODO: Phase Active DSIPLAY Update
				puzzle->getTextTitle()->SetText("NOW!");
				/*std::cout<<"Current analog history : ";
				for(ii=m_vAnalogHistory.begin(); ii!=m_vAnalogHistory.end(); ii++)
				{
					std::cout << (*ii) << " ";
				}
				std::cout << std::endl;*/

				break;
		}
	}

	
	// update for each phase (loop)
	switch(phase)
	{
		case Phase_Rest:
			if(!rotated){
			  if(feedNegative>feedPositive){
				   puzzle->rotateLeft(puzzle->selectedTile);

			  } else {
				  puzzle->rotateRight(puzzle->selectedTile);
			  }
			  rotated=true;
			}
			break;

		case Phase_GetReady:
			if(mark!=Mark_None){
				puzzle->getTextTitle()->SetText("");
			}
			puzzle->rightArrow->SetShow(showClue ? (mark == Mark_Right) : false);
			puzzle->leftArrow->SetShow(showClue ? (mark == Mark_Left) : false);
			break;

		case Phase_Active:
			puzzle->rightArrow->SetShow(false);
			puzzle->leftArrow->SetShow(false);
			/*if(mark==Mark_Left && m_fBallPosition==-GOAL_DISTANCE && !m_bGoalMarkedAtThisPhase) { m_iGoalScore++; m_bGoalMarkedAtThisPhase=true; }
			if(mark==Mark_Right&& m_fBallPosition== GOAL_DISTANCE && !m_bGoalMarkedAtThisPhase) { m_iGoalScore++; m_bGoalMarkedAtThisPhase=true; }*/
			if(mark==Mark_Left && feedback<0) { feedNegative++;}
			if(mark==Mark_Right&& feedback>0) { feedPositive++;}

			break;
	}


	double feedbackScale = feedback;
	if(feedbackScale <= 0 && feedbackScale > -g_fEpsilon) feedbackScale=-g_fEpsilon;
	if(feedbackScale >= 0 && feedbackScale <  g_fEpsilon) feedbackScale= g_fEpsilon;

	// -------------------------------------------------------------------------------
	// Object displacement stuffs
	//BALL FEEDBACK
	if(phase==Phase_Active)
	{
		
	}

	// GRAZ FEEDBACK
	if(phase==Phase_Active)
	{
		//l_poFeedbackNode->setVisible(true);
		//myfile << feedback << std::endl;
		myfile << feedback*200 << std::endl;
		myfile.flush();
		if(feedback>0){
			puzzle->feedbackLeft->SetShow(false);
			puzzle->feedbackRight->SetShow(true);
			puzzle->feedbackRight->SetRegion(0,0,feedback*200,puzzle->feedbackRight->GetSurface()->GetHeight());
		} else {
			puzzle->feedbackRight->SetShow(false);
			puzzle->feedbackLeft->SetShow(true);
			puzzle->feedbackLeft->SetPosition(200-abs(feedback*200),puzzle->feedbackLeft->GetPosY(),puzzle->feedbackLeft->GetPosZ());
			puzzle->feedbackLeft->SetRegion(0,0,abs(feedback*200),puzzle->feedbackLeft->GetSurface()->GetHeight());	
			myfile << abs(feedback*200) <<std::endl;
		}
		
		//l_poFeedbackNode->setScale(0.25f,0.25f,_abs_(l_dFeedbackScale));
		//l_poFeedbackNode->setPosition(3.499f,0.20f,-l_dFeedbackScale/2.f);
	}
	else
	{
		puzzle->feedbackRight->SetShow(false);
		puzzle->feedbackLeft->SetShow(false);
		//l_poFeedbackNode->setVisible(false);
	}
	

	

	// -------------------------------------------------------------------------------
	// End of computation

	lastFeedback=feedback;
	lastPhase=phase;
	lastMark=mark;

}
