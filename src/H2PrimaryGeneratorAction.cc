#include "H2PrimaryGeneratorAction.hh"

#include <iostream>

#include "G4HEPEvtInterface.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "CLHEP/Random/RandFlat.h"
#include "G4RunManager.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"

using namespace CLHEP;
using namespace std;

const int numEnergies = 8;
G4double primEnergies[numEnergies] = {
	1.*GeV, 2.*GeV, 4.*GeV, 8.*GeV, 16.*GeV, 32.*GeV, 50.*GeV, 60.*GeV
};

vector<double> *wcX;
vector<double> *wcY;

//	Constructor
//
H2PrimaryGeneratorAction::H2PrimaryGeneratorAction(RunParams params,
		H2Readout &readout)
	: runParams(params),
	ro(readout)
{
	//	Define a generator
	//
	primEnergy = 120.*GeV;
	primName = "mu-";
	particleGun = new G4ParticleGun(1);
	particleGun->SetParticleEnergy(primEnergy);
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle(primName);
	particleGun->SetParticleDefinition(particle);

	inFileName = string(
			"/home/vitya/Projects/Simulations/H2MuTest/H2MuTest/data/HTBProcessed_007507.root");
	rootFile = new TFile(inFileName.c_str());
	rootFile->cd("WCData");
	rootTree = (TTree*)gDirectory->Get("Events");
	cout << "### Total Events in Tree: " << rootTree->GetEntries() << endl;
	rootTree->SetBranchAddress("xC", &(wcX));
	rootTree->SetBranchAddress("yC", &(wcY));

	primPos = G4ThreeVector(0, 0, -0.49*m);
	primDir = G4ThreeVector(0.*m, 0.*m, 1.0*m);
	particleGun->SetParticlePosition(primPos);
	particleGun->SetParticleMomentumDirection(primDir);
	particleGun->SetParticleEnergy(primEnergy);
}

//	Destructor
//
H2PrimaryGeneratorAction::~H2PrimaryGeneratorAction()
{
	delete particleGun;
}

//	Generate Primary Event
//
void H2PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
	//	All gun's settings have been set up in Constructor
	//
	
	int event = anEvent->GetEventID();

	bool q = true;
//	if (event > rootTree->GetEntries())
//		q = true;

	rootTree->GetEntry(event);
	G4double primX = 0.*mm;
	G4double primY = 0.*mm;
	G4double primZ = -49.*cm;
	if (wcX->size()==0 || wcY->size()==0 || q)
	{	
		G4double primX = 0.*mm;
		G4double primY = 0.*mm;
	}
	else
	{
		primX = wcX->at(0)*mm;
		primY = wcY->at(0)*mm;
	}

	primPos = G4ThreeVector(primX, primY, primZ);
	particleGun->SetParticlePosition(primPos);
	
	cout << particleGun->GetParticleEnergy()/GeV << endl; 
	cout << particleGun->GetParticlePosition()/cm << endl;
	particleGun->GeneratePrimaryVertex(anEvent);
}
