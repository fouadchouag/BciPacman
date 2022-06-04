#ifndef __OpenViBEApplication_CVRPNServer_H__
#define __OpenViBEApplication_CVRPNServer_H__


#include <map>
#include <vector>
#include <string>
#include <fstream>

class vrpn_Connection;
class vrpn_Button_Server;

	class CVRPNServer
	{
		public:
			static CVRPNServer* getInstance(int port);
			~CVRPNServer();
			void processFrame();

			void addButton(std::string sName, int iButtonCount);
			void changeButtonState(std::string sName, int iIndex, int iState);
			int getButtonState(std::string sName, int iIndex);

		private:
			std::ofstream myfile;
			static CVRPNServer* m_poVRPNServerInstance;
			int port;
			CVRPNServer(int port);

			vrpn_Connection* m_poConnection;
			std::map<std::string, vrpn_Button_Server*> m_oButtonServer;
			std::map<std::string, std::vector<int> > m_oButtonCache;

	};

#endif // __OpenViBEApplication_CVRPNServer_H__
