#include "ovassvepICommandVRPNButton.h"

#include <vrpn_Connection.h>
#include <vrpn_Button.h>
#include <string>



namespace
{
	void VRPN_CALLBACK ssvep_vrpn_callback_button(void *command, vrpn_BUTTONCB button)
	{
		((ICommandVRPNButton*)command)->execute(button.button, button.state);
	}
}


ICommandVRPNButton::ICommandVRPNButton(std::string name , std::string host)
	: ICommand()
{
	char l_sButtonName[1024];


	sprintf(l_sButtonName, "%s@%s",name.c_str() , host.c_str());
	m_poVRPNButton = new vrpn_Button_Remote( l_sButtonName );
	m_poVRPNButton->register_change_handler( (void*)this, ssvep_vrpn_callback_button);
}

ICommandVRPNButton::~ICommandVRPNButton()
{
	delete m_poVRPNButton;
}

void ICommandVRPNButton::processFrame()
{
	m_poVRPNButton->mainloop();
}
