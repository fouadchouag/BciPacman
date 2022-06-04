#include "ovassvepCVRPNServer.h"

#include <vrpn_Connection.h>
#include <vrpn_Button.h>

CVRPNServer* CVRPNServer::m_poVRPNServerInstance = NULL;


CVRPNServer::CVRPNServer(int port) : port(port)
{
	//int l_iPort = (OpenViBE::int32)(m_poApplication->getConfigurationManager()->expandAsInteger("${VRPN_ExternalServerPort}"));

	//m_poApplication->getLogManager() << LogLevel_Debug << "VRPN SERVER PORT :" << l_iPort << "\n";
	m_poConnection = vrpn_create_server_connection(port);
	myfile = std::ofstream();
	myfile.open("ssvep_server.txt");
	myfile << "Init server!\n";
	myfile.flush();
}

CVRPNServer* CVRPNServer::getInstance(int port)
{
	if (m_poVRPNServerInstance == NULL)
	{
		m_poVRPNServerInstance = new CVRPNServer(port);
	}

	return m_poVRPNServerInstance;
}

void CVRPNServer::addButton(std::string sName, int iButtonCount)
{
	myfile << "Adding button!\n";
	myfile.flush();
	m_oButtonServer.insert(std::pair<std::string, vrpn_Button_Server*>(sName.c_str(), new vrpn_Button_Server(sName.c_str(), m_poConnection, iButtonCount)));
	m_oButtonCache[sName.c_str()].clear();
	m_oButtonCache[sName.c_str()].resize(iButtonCount);
}

void CVRPNServer::processFrame()
{
	for (std::map<std::string, vrpn_Button_Server*>::iterator it = m_oButtonServer.begin(); it != m_oButtonServer.end(); ++it)
	{
		myfile << "Update button!\n";
		myfile.flush();
		it->second->mainloop();
	}

	m_poConnection->mainloop();
}

void CVRPNServer::changeButtonState(std::string sName, int iIndex, int iState)
{
	m_oButtonServer[sName]->set_button(iIndex, iState);
	m_oButtonCache[sName][iIndex] = iState;
}

int CVRPNServer::getButtonState(std::string sName, int iIndex)
{
	return m_oButtonCache[sName][iIndex];
}
