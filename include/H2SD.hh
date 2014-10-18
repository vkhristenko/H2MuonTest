#ifndef H2SD_H
#define H2SD_H 1

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "globals.hh"

#include <vector>
#include <string>
#include <math.h>

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TRandom.h"

#include "H2Defs.hh"

using namespace std;

//	Define the SD Class
//
class H2SD : public G4VSensitiveDetector
{
	public:
		H2SD(G4String, RunParams, H2Readout&);
		virtual ~H2SD();

		void Initialize(G4HCofThisEvent*);
		G4bool ProcessHits(G4Step*, G4TouchableHistory*);
		void EndOfEvent(G4HCofThisEvent*);
		
		TRandom rand;
		H2Readout ro;
		RunParams runParams;
};

#endif
