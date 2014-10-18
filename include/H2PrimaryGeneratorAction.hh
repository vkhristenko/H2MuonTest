


#ifndef H2PRIMARYGENERATORACTION_H
#define H2PRIMARYGENERATORACTION_H 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"
#include "G4Event.hh"
#include "G4VPrimaryGenerator.hh"

#include "H2Defs.hh"

class H2PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		//	Constructor and Destructor
		H2PrimaryGeneratorAction(RunParams params, H2Readout &readout);
		virtual ~H2PrimaryGeneratorAction();

		//	Standard func	
		void GeneratePrimaries(G4Event *anEvent);

		//	To keep things simplier
		G4ParticleGun *particleGun;
		G4String primName;
		G4double primEnergy;
		G4ThreeVector primPos;
		G4ThreeVector primDir;
		G4int verbosityLevel;

		string inFileName;
		TFile *rootFile;
		TTree *rootTree;
		RunParams runParams;
		H2Readout ro;
};

#endif
