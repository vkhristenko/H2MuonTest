#ifndef H2EVENTACTION_H
#define H2EVENTACTION_H 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4Timer.hh"

class H2EventAction : public G4UserEventAction
{
	public:
		H2EventAction();
		~H2EventAction();

		void BeginOfEventAction(const G4Event*);
		void EndOfEventAction(const G4Event*);

		G4Timer *timer;
};

#endif
