#include "H2SD.hh"
#include "G4UnitsTable.hh"
#include "G4TrackStatus.hh"
#include "G4VProcess.hh"

#include <iostream>

using namespace std;
using namespace CLHEP;

//	Constructor
//
H2SD::H2SD(G4String name, RunParams inData, H2Readout &readout)
	: G4VSensitiveDetector(name),
	runParams(inData)
{
	//opTree->Branch("op_pe", pe, "pe[10]/D");
	//
	rand.SetSeed(runParams.seed);	
	ro = readout;
}

//	Destructor
//
H2SD::~H2SD()
{

}

//	Initialize
//
void H2SD::Initialize(G4HCofThisEvent*)
{
}

//	Process Hits
//
G4bool H2SD::ProcessHits(G4Step *aStep, G4TouchableHistory*)
{

	G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();
	double x = pos.x()/mm;
	double y = pos.y()/mm;
	ro.hXY->Fill(x, y);

	return true;
}

//	Finalize the event
//
void H2SD::EndOfEvent(G4HCofThisEvent*)
{ 
}
