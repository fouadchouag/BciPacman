#ifndef __OpenViBEApplication_CCommandStimulatorControl_H__
#define __OpenViBEApplication_CCommandStimulatorControl_H__

#include "ovassvepICommandVRPNButton.h"

class SSVEP;
	class CCommandStimulatorControl : public ICommandVRPNButton
	{
		public:
			CCommandStimulatorControl(SSVEP * ssvep);
			~CCommandStimulatorControl() {};
			void execute(int iButton, int iState);
		private:
			SSVEP * ssvep;
	};


#endif // __OpenViBEApplication_CCommandStimulatorControl_H__
