#include "ovassvepCCommandStimulatorControl.h"
#include "SSVEP.h"

CCommandStimulatorControl::CCommandStimulatorControl(SSVEP * ssvep)
	: ICommandVRPNButton("SSVEP_VRPN_StimulatorControl", "localhost"), ssvep(ssvep)
{
}

void CCommandStimulatorControl::execute(int iButton, int iState)
{
	// only run the commands once, skip

	switch (iButton)
	{

		case 0:
			ssvep->startTraining();
			break;
			
		case 1:
			ssvep->stopTraining();
			break;
			
		case 2:
			//Start flickering
			break;
			
		case 3:
			//Stop flickering
			break;
			
		default:
			//Error, unknown command
			break;

	}

}
