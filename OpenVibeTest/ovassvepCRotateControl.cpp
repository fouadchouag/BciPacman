#include "ovassvepCRotateControl.h"
#include "SSVEP.h"

CRoatateControl::CRoatateControl(Puzzle * p, SSVEP * ssvep)
	: ICommandVRPNButton("SSVEP_VRPN_ShipControl","localhost"), ssvep(ssvep)
{ 
	this->puzzle = p;
	lastRotate = 0;
}

void CRoatateControl::execute(int iButton, int iState)
{
	if(ssvep->currentTime-lastRotate>1){
	switch (iButton)
	{
		case 0:
			break;
		case 1:
			lastRotate = ssvep->currentTime;
			puzzle->rotateLeft(puzzle->selectedTile);
			break;
		case 2:
			lastRotate = ssvep->currentTime;
			puzzle->rotateRight(puzzle->selectedTile);
			break;
	}
	}
}
