#ifndef __OpenViBEApplication_CCommandStartStop_H__
#define __OpenViBEApplication_CCommandStartStop_H__



	class CVRPNServer;
	class SSVEP;
	class CCommandStartStop
	{
		public:
			CCommandStartStop(SSVEP * ssvep);
			~CCommandStartStop();

			void processFrame();

		private:
			CVRPNServer* m_poVRPNServer;
			SSVEP * ssvep;
	};


#endif // __OpenViBEApplication_CCommandStartStop_H__
