#ifndef H2RUNACTION_H
#define H2RUNACTION_H 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"
#include "G4Timer.hh"

class H2RunAction : public G4UserRunAction
{
	public:
		H2RunAction();
		~H2RunAction();

		void BeginOfRunAction(const G4Run* aRun);
		void EndOfRunAction(const G4Run* aRun);

		G4Timer *timer;
};

#endif
