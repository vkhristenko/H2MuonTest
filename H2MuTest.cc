/*
 *	H2ashlik Simulation
 *	Author: VK
 *	Date: 05/19/204
 *	Description:
 *
 * */


#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "Randomize.hh"

#include "QBBC.hh"
//#include "QGSP.hh"

#include "H2DetectorConstruction.hh"
#include "H2PrimaryGeneratorAction.hh"
#include "H2EventAction.hh"
#include "H2RunAction.hh"
#include "H2Defs.hh"
#include "H2PhysicsList.hh"
#include "H2SteppingAction.hh"

#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"

#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"

using namespace std;
using namespace CLHEP;

/*
 *	Main Function:
 *	Input Format:
 *		
 *
 */
int main(int argc, char** argv)
{
	//	Parse all the input
	//
	RunParams runParams;
	runParams.isInteractive = atoi(argv[1]);
	runParams.numEvents = 1000;
	runParams.seed = 1;
	runParams.verbosity = 0;

	if (!runParams.isInteractive)
	{
		runParams.numEvents = atoi(argv[2]);
		runParams.seed = atoi(argv[3]);
		runParams.verbosity = atoi(argv[4]);
	}

	//	Initialize Random Number Generator
	//
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
//	CLHEP::HepRandom::setTheSeed(time(NULL));
	CLHEP::HepRandom::setTheSeed(runParams.seed);
	CLHEP::HepRandom::showEngineStatus();

	//	Initialize ROOT Output
	//
	char rootOutFileName[200];
	sprintf(rootOutFileName, "H2WCTest_%d_%d.root",
			runParams.seed, runParams.numEvents);
	TFile *rootOutFile = new TFile(rootOutFileName, "RECREATE");
	H2Readout ro;
	ro.hXY = new TH2D("XY", "XY", 200, -100, 100, 200, -100, 100);

	//	Initialize G4 Classes
	//
	G4RunManager *runManager = new G4RunManager;
	H2DetectorConstruction *detector = 
		new H2DetectorConstruction(runParams, ro);
	runManager->SetUserInitialization(detector);
	
	G4PhysListFactory factory;
	G4VModularPhysicsList *phys = factory.GetReferencePhysList("FTFP_BERT");
//	phys->RegisterPhysics(new H2PhysicsList);
//	H2PhysicsList *phys = new H2PhysicsList();
	runManager->SetUserInitialization(phys);

	H2PrimaryGeneratorAction *primAction = 
		new H2PrimaryGeneratorAction(runParams, ro);
	runManager->SetUserAction(primAction);

	// optional user action Classes
	//
	H2EventAction *eventAction = new H2EventAction();
	H2RunAction *runAction = new H2RunAction();
	H2SteppingAction *steppingAction = new H2SteppingAction(runParams);
	runManager->SetUserAction(runAction);
	runManager->SetUserAction(eventAction);
	runManager->SetUserAction(steppingAction);

	// Init G4 Kernel
	//
	runManager->Initialize();
	G4UImanager *UI = G4UImanager::GetUIpointer();

	if (runParams.isInteractive)
	{
		G4VisManager *visManager = 0;
		#ifdef G4VIS_USE
			//	Visualization
			//
			visManager = new G4VisExecutive;
			visManager->Initialize();
		#endif

		#ifdef G4UI_USE
			G4UIExecutive *ui = new G4UIExecutive(argc, argv);
			ui->SessionStart();
			delete ui;
		#endif
	}
	else
	{
		char cmd[200];
		sprintf(cmd, "/run/beamOn %d", runParams.numEvents);
		UI->ApplyCommand(cmd);
	}

	//	Finalize
	//
	delete runManager;
	rootOutFile->Print();
	rootOutFile->Write();
	rootOutFile->Close();

	return 0;
} 
