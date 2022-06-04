#ifndef __OpenViBEApplication_CCommandShipControl_H__
#define __OpenViBEApplication_CCommandShipControl_H__

#include "ovassvepICommandVRPNButton.h"
#include "puzzle.h"

	class SSVEP;
	class CRoatateControl : public ICommandVRPNButton
	{
		public:
			CRoatateControl(Puzzle * p, SSVEP * ssvep);
			~CRoatateControl() {};
			void execute(int iButton, int iState);
		private:
			int lastRotate;
			Puzzle * puzzle;
			SSVEP * ssvep;
	};



#endif // __OpenViBEApplication_CCommandShipControl_H__
