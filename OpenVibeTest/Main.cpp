#include <iostream>


#include <vrpn_Button.h>
#include <vrpn_Analog.h>

#include <tobii/sdk/cpp/init.hpp>
#include <tobii/sdk/cpp/discovery/eyetracker-browser.hpp>
#include <tobii/sdk/cpp/tracking/eyetracker-factory.hpp>
#include <tobii/sdk/cpp/tracking/gaze-data-item.hpp>
#include <tobii/sdk/cpp/tracking/types.hpp>

//#include "VRPNAnalogClient.h"
#include "CIndieLib_vc2008.h"
#include "PuzzleInputManager.h"
#include "GameStateManager.h"
#include "GameStateActive.h"
#include "GratzFeedback.h"
#include "ovaCAbstractVrpnPeripheral.h"

//#include "EyeTrackerMain.h" 
//#include "EyeTrackerManager.h"
#include <boost/bind/bind.hpp>
#include "SSVEP.h"

using namespace tobii::sdk::cpp;

//discovery::eyetracker_browser * browser;
//EyeTrackerMain * etm;
Puzzle * puzzle;

void gaze_data_event(tracking::gaze_data_item::pointer gdi){
	tracking::point_2d le = gdi->left_gaze_point_2d;
	tracking::point_2d re = gdi->left_gaze_point_2d;

	float x = (le.x + re.x)/2;
	float y = (le.y + re.y)/2;
	x*=400;
	y*=400;
	puzzle->selectTile(puzzle->getTileIndex((int)x,(int)y));
}

void browse_event(discovery::eyetracker_browser::event_type et, discovery::eyetracker_info::pointer infopt){
	if(infopt->get_given_name()=="tobii1"){
		discovery::factory_info fi = discovery::factory_info(*infopt);
		//EyeTrackerManager::getInstance()->setTracker(tracking::create_eyetracker(fi,*(etm->getMainloop())));
		//EyeTrackerManager::getInstance()->getTracker()->add_gaze_data_received_listener(boost::bind(gaze_data_event,_1));
		//browser->stop();
	}
}


int IndieLib()		
{
	// ----- IndieLib intialization -----

	CIndieLib *mI = CIndieLib::Instance();
	tobii::sdk::cpp::init_library();

	puzzle = new Puzzle(mI);
	PuzzleInputManager * pim = new PuzzleInputManager(puzzle);
	GameStateManager * gm = new GameStateManager();

	//GameStateActive * gsa1 = new GameStateActive(); 
	//GameStateActive * gsa2 = new GameStateActive(); 
	//gm->registerState(gsa1, 5);
	//gm->registerState(gsa2, -1);


	//etm = new EyeTrackerMain();

	//browser = new discovery::eyetracker_browser(*(etm->getMainloop()));
	//discovery::eyetracker_browser::connection eventSubscription = browser->add_browser_event_listener(boost::bind(browse_event,_1,_2));

	if (!mI->Init (pim)) return 0;									

	//VRPNAnalogClient * analogClient = new VRPNAnalogClient("openvibe_vrpn_analog@localhost");
	OpenViBEVRDemos::CAbstractVrpnPeripheral * vrpnPeripheral = new OpenViBEVRDemos::CAbstractVrpnPeripheral("openvibe-vrpn@localhost"); 

	vrpnPeripheral->init();
	GratzFeedback * gf = new GratzFeedback(puzzle, vrpnPeripheral);

	gm->start();
	//etm->start();
	//browser->start();

	puzzle->initGame();

	SSVEP * ssvep = new SSVEP(puzzle,pim,false);
	ssvep->start();
	
	puzzle->running = true;
	// ----- Main Loop -----
	int selectedIndex = -1;
	int frame=0;
	while (!mI->Input->OnKeyPress (IND_ESCAPE) && !mI->Input->Quit() && puzzle->running==true)
	{
		vrpnPeripheral->loop();
		//gf->update(gm->getTimeInSec());
		ssvep->update(gm->getTimeInSec());
		gm->update();
		pim->Update();
		mI->Render->BeginScene ();
		//mI->Render->
		mI->Entity2dManager->RenderEntities2d ();
		//puzzle->getTextTitle()->SetText(mI->Render->GetFpsString());
		mI->Render->EndScene ();	
		if(puzzle->checkWin()){
			puzzle->getTextTitle()->SetText("Victory!");
			puzzle->running = false;
		}

	}
	//etm->stop();
	//etm->join();
	//delete etm;

	ssvep->stop();
	gm->stop();
	mI->End ();

	//delete gm;
	delete mI;
	delete pim;
	//delete gsa1;
	//delete gsa2;
	delete gf;
	return 0;
}
