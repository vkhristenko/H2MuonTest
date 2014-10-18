#ifndef H2DEFS_H
#define H2DEFS_H

#include "globals.hh"
#include <vector>
#include "TROOT.h"
#include "TFile.h"
#include "TApplication.h"
#include "TTree.h"
#include "TH2D.h"

using namespace std;

/*
 *	Run Parameters
 *
 */
typedef struct RunParams
{
	int isInteractive;
	int verbosity;
	int seed;
	int numEvents;
};

typedef struct H2Readout
{
	TH2D *hXY;
};

#endif
