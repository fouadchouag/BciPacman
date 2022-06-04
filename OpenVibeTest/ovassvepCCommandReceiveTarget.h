#ifndef __OpenViBEApplication_CCommandReceiveTarget_H__
#define __OpenViBEApplication_CCommandReceiveTarget_H__

#include "ovassvepICommandVRPNButton.h"

class SSVEP;

	class CCommandReceiveTarget : public ICommandVRPNButton
	{
		public:
			CCommandReceiveTarget(SSVEP * ssvep);
			~CCommandReceiveTarget() {};

			void execute(int iButton, int iState);
		private:
			SSVEP * ssvep;


	};


#endif // __OpenViBEApplication_CCommandReceiveTarget_H__
