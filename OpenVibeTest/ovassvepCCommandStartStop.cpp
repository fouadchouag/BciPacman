#include "ovassvepCCommandStartStop.h"
#include "ovassvepCVRPNServer.h"
#include "SSVEP.h"
#include "CIndieLib_vc2008.h"

CCommandStartStop::CCommandStartStop(SSVEP * ssvep): ssvep(ssvep)
{
	m_poVRPNServer = CVRPNServer::getInstance(2222);
	m_poVRPNServer->addButton("SSVEP_VRPN_StartStop", 2);
}

CCommandStartStop::~CCommandStartStop()
{
	m_poVRPNServer->changeButtonState("SSVEP_VRPN_StartStop", 1, 1);
	m_poVRPNServer->processFrame();
}

void CCommandStartStop::processFrame()
{
	m_poVRPNServer->processFrame();
	if(ssvep->pim->OnKeyPress(IND_SPACE)){
			ssvep->puzzle->textTitle->SetText("Space");
		m_poVRPNServer->changeButtonState("SSVEP_VRPN_StartStop", 0, 1);
	}
	if(ssvep->pim->OnKeyRelease(IND_SPACE)){
		ssvep->puzzle->textTitle->SetText("");
		m_poVRPNServer->changeButtonState("SSVEP_VRPN_StartStop", 0, 0);
	}	
}
