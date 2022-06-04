#include "ovassvepCCommandReceiveTarget.h"

#include "SSVEP.h"

CCommandReceiveTarget::CCommandReceiveTarget(SSVEP* ssvep) 
	: ICommandVRPNButton("SSVEP_VRPN_Target","localhost"), ssvep(ssvep)
{
}

void CCommandReceiveTarget::execute(int iButton, int iState)
{
	if(iButton == 1){
		ssvep->setTarget(LEFT_TARGET);
	} else if(iButton == 2){
		ssvep->setTarget(RIGHT_TARGET);
	}
}
