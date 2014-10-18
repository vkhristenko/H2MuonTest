#include "H2EventAction.hh"

#include <iostream>

using namespace std;

H2EventAction::H2EventAction()
{
	timer = new G4Timer();
}

H2EventAction::~H2EventAction()
{
	delete timer;
}

void H2EventAction::BeginOfEventAction(const G4Event* anEvent)
{
	G4cout << "### Starting Event: " << anEvent->GetEventID() << endl;
	timer->Start();
}

void H2EventAction::EndOfEventAction(const G4Event*)
{
	timer->Stop();
	G4cout << "### Event Duration: " << *timer << G4endl;
}
