#ifndef H2DETECTORCONSTRUCTION_H
#define H2DETECTORCONSTRUCTION_H 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include <vector>

#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4VSolid.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "H2Defs.hh"
#include "H2SD.hh"

using namespace CLHEP;

class H2DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		//	Constructor and Destructor
		H2DetectorConstruction(RunParams, H2Readout&);
		~H2DetectorConstruction(); 

		G4VPhysicalVolume* Construct();
		G4VPhysicalVolume* BuildGeometry();
		void BuildH2Setup();
		void UpdateGeometry();

		RunParams runParams;
		H2Readout ro;

		//	List of Materials/Elements
		//	mAl2O3 Index of 0 and mGaInP index of 8
		G4Element *eLu;
		G4Element *eY;
		G4Element *eSi;
		G4Element *eO;
		
		//	Materials
		//
		G4Material *mAir;
		G4Material *mFe;
		G4Material *mVacuum;
		G4Material *mAl2O3;
		G4Material *mBeO;
		G4Material *mMgO;
		G4Material *mTiO;
		G4Material *mCs3Sb;
		G4Material *mGaP;
		G4Material *mGaAsP;
		G4Material *mGaPCs;
		G4Material *mGaInP;
		G4Material *mW;
		G4Material *mLYSO;
		G4Material *mSiO2;

		//
		//	Volumes
		//

		//	World
		//	/
		G4Box *sWorld;
		G4LogicalVolume *lWorld;
		G4VPhysicalVolume *pWorld;

		//
		//	Iron Target
		//
		G4Box *sTarget;
		G4LogicalVolume *lTarget;
		G4VPhysicalVolume *pTarget;

		//
		//	My Sensitive Part
		//
		G4Box *sWC;
		G4LogicalVolume *lWC;
		G4VPhysicalVolume *pWC;

};
#endif











